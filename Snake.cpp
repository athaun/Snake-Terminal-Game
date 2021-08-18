#include <iostream>
#include "map.h"
#include "Snake.h"
#include "utilities.h"
#include "audio.h"

// Figures out which character to display for the head based on the direction of travel
void Snake::findMove () {
    switch (direction) 
    {
        case UP:
            headCharacter = bold + green + "^" + reset;
            move(0, -1); // Moving up on the Y axis
            break;
        case DOWN:
            headCharacter = bold + green + "v" + reset;
            move(0, 1); // Moving down on the Y axis  
            break;
        case RIGHT:
            headCharacter = bold + green + ">" + reset;
            move(1, 0); // Moving right on the X axis   
            break;
        case LEFT:
            headCharacter = bold + green + "<" + reset;
            move(-1, 0); // Moving left on the X axis  
            break;
    }
}

void Snake::initSnake (int x, int y) {
    for (int i = 0; i < snakeLength; i ++) {
        segments[i].first = x;
        segments[i].second = y + i; // Increase the y position of each subsequent segment
    }
}

// Displays the head
void Snake::display () {

    this->findMove();
    this->death();
    this->collectFood();

    for (int i = 0; i < snakeLength; i ++) {
        if (i == 0) {
            setTile(segments[i].first, segments[i].second, headCharacter);
        } else {
            setTile(segments[i].first, segments[i].second, bold + green + "#" + reset);
        }
    }
}

void Snake::move (int xDir, int yDir) {
    int x = segments[0].first + xDir;
    int y = segments[0].second + yDir;

    for (int i = snakeLength - 1; i >= 1; i --) {
        segments[i].first = segments[i - 1].first;
        segments[i].second = segments[i - 1].second;
    }
    segments[0].first = x;
    segments[0].second = y;
}

void Snake::collectFood () {
    for (int i = 0; i < ARRAY_SIZE(food); i ++) {
        if (segments[0].first == food[i].first && segments[0].second == food[i].second) {
            playSound(0, 0.01); // Plays an eat sound affect
            snakeLength += segmentGrowth;
            score += scoreGrowth;
            setTile(food[i].first, food[i].second, "`"); // Set the tile back to a `
            int rx = random(0, ARRAY_SIZE(map)); // Create new random positions for the food
            int ry = random(0, ARRAY_SIZE(map[0]));
            food[i].first = rx; // Set them
            food[i].second = ry;
            // setTile(rx, ry, '&'); // Change the tile at the new positions to &
        }
    }
}


 void Snake::death () {
    if ((segments[0].first < 0) || 
    (segments[0].first >= ARRAY_SIZE(map)) || 
    (segments[0].second < 0) || 
    (segments[0].second >= ARRAY_SIZE(map[0]))) {
        isAlive = false;
    }     

    for (int i = 1; i < snakeLength; i ++) {
        // If head X and Y == any other segments X and Y
        if ((segments[0].first == segments[i].first) && (segments[0].second == segments[i].second)) {
            isAlive = false;
        }
    }
 }
