#include <string>

#pragma once

#define mapSize 53

#define amountOfFood 4

extern std::string yellow;
extern std::string green;
extern std::string white;
extern std::string bold;
extern std::string reset;
extern std::string lightgray;

extern std::string map [mapSize][mapSize];

extern std::pair <int, int> food [amountOfFood];

void log (std::string s);
void spamLog (std::string s);

void setTile (int x, int y, std::string c);
void initMap ();
void clearScreen ();
void printMap ();
void printStat ();