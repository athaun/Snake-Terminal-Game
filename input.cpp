#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "Main.h"
#include <iostream>
#include "input.h"

void setNonBlocking(int fd) {
    int flags  = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    flags = fcntl(fd, F_SETFL, flags);
}

void keyInput () {    

    // Set terminal to raw mode.  Will detect user input
    system("stty raw"); 
    int character = getchar();

    //character=character-32;

    while (character > 0) {
        
        switch (character) 
        {
            case 'w':
                if (snake.direction != DOWN) {
                    snake.direction = UP;
                }
                break;

            case 's':
                if (snake.direction != UP) {
                    snake.direction = DOWN;      
                }
                break;

            case 'd':
                 if (snake.direction != LEFT) {
                    snake.direction = RIGHT;      
                 }
                break;

            case 'a':
                if (snake.direction != RIGHT) {
                    snake.direction = LEFT;        
                }
                break;

            case 'q':
                running = false;
                break;    

            default:
                // Do nothing
                break;    
        }
        character = getchar();
    }
    // Reset terminal to normal "cooked" mode 
    system("stty cooked");
}