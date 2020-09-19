/* Run command: clear && g++ *.cpp -o snake.out  */

#include <iostream>
#include "utilities.h"
#include <cstring>
#include <unistd.h>
#include "Snake.h"
#include "map.h"
#include "input.h"
#include <signal.h>


bool running = true;

Snake snake;

int testY = 0;

void cleanup () {
    // Kill the music program
    system("2>/dev/null 1>&2 killall canberra-gtk-play");

    printf("\nThe game has closed.\n");
}

void sigintHandler(int sig_num) { 
    // Reset handler to catch SIGINT next time. 
    signal(SIGINT, sigintHandler); 
    running = false;
} 

int main() {

    // Catching ^C
    signal(SIGINT, sigintHandler); 

    // Starting to play music
    system("bash -c \"canberra-gtk-play -V 0.1 -l 20 -f ./01-rondo_a_capriccio_in_g_op_129.ogg\" &"); 

    seedRandom();
  
    // Set input nonBlocking
    int fd = fileno(stdin);
    char buf[1];
    bool done = false;
    setNonBlocking(fd);

    // Creating a random spawn with at least 6 tile buffer on every side
    snake.initSnake(random(6, ARRAY_SIZE(map) - 6), random(6, ARRAY_SIZE(map) - 6));
    
    // Game Loop
    while (running) {
        keyInput(); 

        // Clears the terminal
        clearScreen();

        // Creates the solid map of "." periods
        initMap();

        // Displays the snake's head
        snake.display();

        printMap();

        printStat();

        // Sleep for 50 milliseconds
        usleep(100 * 1000);

        

        snake.score += 0.5;
        
        if (!snake.isAlive) {
            printf("You died.");
            running = false;            
        }

    }
    
    // Clean up any parts of the program before it closes
    cleanup();
    
    return 0;
}

