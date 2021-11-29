#include <unistd.h>
#include <iostream>
#include "utilities.h"
#include <cstring>
#include "map.h"
#include "Snake.h"
#include "Main.h"

using namespace std;

std::string yellow = "\e[1;33m";
std::string green = "\033[0;32m";
std::string white = "\e[0;97m";
std::string bold = "\e[1m";
std::string reset = "\e[0m";
std::string lightgray = "\e[0;37m";

std::string map [mapSize][mapSize];

std::pair <int, int> food [amountOfFood];

string printout;

void setTile (int x, int y, std::string c) {
    if (x < mapSize && y < mapSize) {
        map[x][y] = c;
    }
}

bool foodTilesCreated = false;
void initMap () {
    if (!foodTilesCreated && network.isServer) {
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
            if (x % 4 == 0 && y % 4 == 0) {
                setTile(x, y, "`");
            } else {
                setTile(x, y, " ");
            }
        }
    }
    for (int i = 0; i < ARRAY_SIZE(food); i ++) {
        setTile(food[i].first, food[i].second, bold + yellow + "&" + reset); // Change the tile at the food positions to &
    }
}

void clearScreen () {
    printf("\033c"); // Clears the screen to make way for a new frame
}

void printMap () {
    // Loops through the 2D array map, n prints the character contained at that index
    for (int y = 0; y < ARRAY_SIZE(map[0]); y ++) {
        for (int x = 0; x < ARRAY_SIZE(map); x ++) {
            std::cout << map[x][y] << " ";
        }
        printf("\n");
    }
}

void log (string s) {
    printout = s + "\n";
}

void spamLog (string s) {
    printout += s + "\n";
}

void printStat () {  
    printf("Press \"q\" to quit.\n");
    printf("You have a score of: %d \n", (int)snake.score);
    printf("\n%s \n", printout.c_str());
}
