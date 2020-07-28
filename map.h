#pragma once

#define mapSize 40

#define amountOfFood 4

extern char map [mapSize][mapSize];

extern std::pair <int, int> food [amountOfFood];

void setTile (int x, int y, char c);
void initMap ();
void clearScreen ();
void printMap ();
void printStat ();