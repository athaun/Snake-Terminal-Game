#include <unistd.h>
#include <iostream>
#include "utilities.h"
#include <cstring>
#include "map.h"
#include "Snake.h"
#include "Main.h"

using namespace std;

char map [mapSize][mapSize];

string statsPanel = "Hello";

std::pair <int, int> food [amountOfFood];

void setTile (int x, int y, char c) {
    if (x < mapSize && y < mapSize) {
        map[x][y] = c;
    }
}

bool foodTilesCreated = false;

void initMap () {
    if (!foodTilesCreated) {
        for (int i = 0; i < ARRAY_SIZE(food); i ++) {
            int rx = random(0, ARRAY_SIZE(map)); // Create new random positions for the food
            int ry = random(0, ARRAY_SIZE(map[0]));
            food[i].first = rx; // Set them
            food[i].second = ry;            
        }
        foodTilesCreated = true;
    }
    for (int y = 0; y < ARRAY_SIZE(map[0]); y ++) {
        for (int x = 0; x < ARRAY_SIZE(map); x ++) {
            setTile(x, y, '`');
        }
    }
    for (int i = 0; i < ARRAY_SIZE(food); i ++) {
        setTile(food[i].first, food[i].second, '&'); // Change the tile at the food positions to &
    }
}

void clearScreen () {
    printf("\033c"); // Clears the screen to make way for a new frame
}

void printMap () {
    // Loops through the 2D array map, n prints the character contained at that index
    for (int y = 0; y < ARRAY_SIZE(map[0]); y ++) {
        for (int x = 0; x < ARRAY_SIZE(map); x ++) {
            printf("%c ", map[x][y]);
        }
        printf("\n");
    }
}

void printStat () {
    printf("\n%s \n", statsPanel.c_str());
    printf("Press \"q\" to quit.\n");
    printf("You have a score of: %d \n\n", (int)snake.score);
}
