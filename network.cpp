#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string>
#include <netdb.h>
#include "networkTypes.h"
#include "network.h"
#include "Main.h"
#include "map.h"

/** 
 * Start:
 * one class, that choses if it is a Client or server:
 * 
   Data:
    serverClient: Client

 * Methods:
     init (bool server)
     getGameData()
     setGameData()
     tickUpdate() sends/receives (update game data)
     
 * Init()
 * if Server:
 * Initialize server
 * 
 * if Client:
 * initialize client
 * send beacon to server ()
 * search for server, if found, connect to server
*/

int socket_get_address(struct sockaddr_in *socket_address, char const *hostname, int portnum) { 
    struct hostent *hp;

    if ((hp = gethostbyname(hostname)) == NULL) {
        return(-1);
    }

    memset(socket_address, '\0', sizeof(struct sockaddr_in));

    memcpy(&(socket_address->sin_addr), hp->h_addr, hp->h_length);     
    socket_address->sin_family = AF_INET;
    socket_address->sin_family = hp->h_addrtype;
    socket_address->sin_port = htons(portnum);

    return(0);
}

GAME_DATA Network::getGameData () {
    return this->game_data;
}

void Network::setGameData (GAME_DATA data) {
    this->game_data = data;
}

int sockfd;
GAME_DATA game_data;
GAME_DATA other_game_data;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

void Network::init () {
    if (this->isServer) {
        
        printf("Server\n");

        // Creating socket file descriptor
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&server_address, '\0', sizeof(server_address));
        memset(&client_address, '\0', sizeof(client_address));

        // Filling server information
        server_address.sin_family = AF_INET; // IPv4
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(server_port);

        // Bind the socket with the server address
        if (bind(sockfd, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        // Set nonblocking
        fcntl(sockfd, F_SETFL, O_NONBLOCK);
    } else {

        printf("Client\n");

        // Creating socket file descriptor
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
    }
}

// Sending the game data to the other player
void setLocalGameData () {
    game_data.type = SERVER_UPDATE; // Feature not used
    game_data.snake.position.x = snake.segments[0].first;
    game_data.snake.position.y = snake.segments[0].second;
    memcpy(game_data.snake.segments, snake.segments, sizeof(game_data.snake.segments)); // Copying the entire local snake segments array to game_data
    game_data.snake.direction = snake.direction;    
    game_data.snake.length = snake.snakeLength;
    game_data.snake.isAlive = snake.isAlive;
    game_data.snake.score = snake.score;

    if (network.isServer) {
        memcpy(game_data.food, food, sizeof(game_data.food));
        game_data.clientSnake.length = otherSnake.snakeLength;
        game_data.clientSnake.score = otherSnake.score;
        // spamLog(std::to_string(otherSnake.score));
    }
}

// Setting the received game data to otherSnake
void setFromOtherGameData () {
    otherSnake.segments[0].first = other_game_data.snake.position.x;
    otherSnake.segments[0].second = other_game_data.snake.position.y;
    memcpy(otherSnake.segments, other_game_data.snake.segments, sizeof(otherSnake.segments));
    otherSnake.direction = other_game_data.snake.direction;
    // otherSnake.snakeLength = other_game_data.snake.length;
    otherSnake.isAlive = other_game_data.snake.isAlive;
    // otherSnake.score = other_game_data.snake.score;
    
    if (!network.isServer) {
        memcpy(food, other_game_data.food, sizeof(food));
        snake.snakeLength = other_game_data.clientSnake.length;
        snake.score = other_game_data.clientSnake.score;
        // spamLog(std::to_string(snake.score));
    }
}

void networkClient () {
    memset(&server_address, '\0', sizeof(server_address));
    memset(&game_data, '\0', sizeof(game_data));

    // Filling server information
    if (socket_get_address(&server_address, server_ip.c_str(), server_port) != -1)
    {
        int bytes_read = 1;
        unsigned int length;

        fcntl(sockfd, F_SETFL, O_NONBLOCK);

        setLocalGameData();   

        int send = sendto(sockfd, &game_data, sizeof(game_data), MSG_CONFIRM, (const struct sockaddr *) &server_address, sizeof(server_address));
        usleep(1000);

        setFromOtherGameData();

        // Gets the latest message from the server
        while (bytes_read > 0)
        {
            struct sockaddr_in tmp_address;
            bytes_read = recvfrom(sockfd, &other_game_data, sizeof(other_game_data), MSG_WAITALL, (struct sockaddr *) &tmp_address, &length); 
        }
        
        if (bytes_read == -1 && errno != EAGAIN) {
            perror("Socket read error");
        }
    } else {
        printf("Error lookup up host\n");
    }

    // TODO: either let the OS close the socket, or else utilize a destroyer to call close(sockfd);
}

void networkServer () {
    // Initialize game data
    memset(&game_data, '\0', sizeof(game_data));
    setLocalGameData();

    int bytes_read;
    unsigned int length;

    length = sizeof(client_address); // Length is value/result
    
    bytes_read = recvfrom(sockfd, &other_game_data, sizeof(other_game_data), MSG_WAITALL, ( struct sockaddr *) &client_address, &length);

    // If the client has sent a message, respond.
    if (bytes_read > 0) {

        setFromOtherGameData();

        // Send local snake data to client
        sendto(sockfd, &game_data, sizeof(game_data), MSG_CONFIRM, (const struct sockaddr *) &client_address, length);        
    }
}

void Network::update () {
    if (this->isServer) {
        networkServer();
    } else {
        networkClient();
    }
}