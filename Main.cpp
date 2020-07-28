/* Run command: clear && g++ Main.cpp utilities.cpp -o p.out */

#include <iostream>
#include "utilities.h"
#include <cstring>
#include <unistd.h>
#include "Snake.h"
#include "map.h"
#include "input.h"

using namespace std;

bool running = true;

Snake snake;

int testY = 0;

int main() {

    seedRandom();
  
    // Set input nonBlocking
    int fd = fileno(stdin);
    char buf[1];
    bool done = false;
    setNonBlocking(fd);

    // Creating a random spawn with at least 5 tile buffer on every side
    snake.initSnake(random(5, ARRAY_SIZE(map) - 5), random(5, ARRAY_SIZE(map) - 5));
    
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

    printf("\nThe game has closed.\n");

    return 0;
}