/* Run command: g++ *.cpp -o snake.out && ./snake.out */

#include <iostream>
#include "utilities.h"
#include <cstring>
#include <unistd.h>
#include "Snake.h"
#include "map.h"
#include "input.h"
#include "network.h"
#include "networkTypes.h"

using namespace std;

bool devTesting = true;
bool running = true;
bool ready = false;
int server_port = 25565;
std::string server_ip = "minecraft.athaun.tech";
std::string buffer;

Snake snake;
Snake otherSnake;
Network network;

int testY = 0;

int main() {


    /*
    if user enters value 1, then they become a server. Else if, they enter a value of 2, then they become a client 
    */
    while (!ready) {
        printf("Please select either server or client by typing either \"1\" or \"2\"\nType \"i\" to edit the IP address of the host or \"p\" to select the port\nCurrent address: %s:%d\n[1] Server\n[2] Client\n>>> ", server_ip.c_str(), server_port);

        int character = getchar();
        if (character == '1') {        
            printf("\nYou has now become a server");
            network.isServer = true;
            ready = true;
        } else if (character == '2') {
            printf("\nYou has now become a client");
            network.isServer = false;
            ready = true;
        } else if (character == 'i') {
            printf("\nInput the server IP address: ");
            std::getline(std::cin, buffer); // Pipping the unwanted RETURN line to a dummy variable
            std::getline(std::cin, server_ip);
            cout << "IP address set to: " + server_ip << endl;
        } else if (character == 'p') {
            printf("\nInput the server port: ");
            std::getline(std::cin, buffer); // Pipping the unwanted RETURN line to a dummy variable
            std::getline(std::cin, buffer);
            server_port = strtol(buffer.c_str(), NULL, 0); // Setting the input string to an int, then to server_port
            cout << "Port set to: " + server_port << endl;
        }
    }

    network.init();

    seedRandom();
  
    // Set input nonBlocking
    int fd = fileno(stdin);
    char buf[1];
    bool done = false;
    setNonBlocking(fd);

    // Creating a random spawn with at least 5 tile buffer on every side
    snake.initSnake(random(5, ARRAY_SIZE(map) - 5), random(5, ARRAY_SIZE(map) - 5));
    otherSnake.initSnake(random(5, ARRAY_SIZE(map) - 5), random(5, ARRAY_SIZE(map) - 5));
    
    
    // Game Loop
    while (running) {
         
        network.update();

        keyInput(); 

        // Clears the terminal
        clearScreen();

        // Creates the solid map of "." periods
        initMap();

        // Displays the snake's head
        snake.display();
        otherSnake.display();
        
        printMap();

        printStat();

        // Sleep for 50 milliseconds
        usleep(100 * 1000);
        
        if (!snake.isAlive) {
            printf("You died.");
            running = false;
        }

    }

    printf("\nThe game has closed.\n");

    return 0;
}