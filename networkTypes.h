#pragma once

#include "input.h"
#include "map.h"

#define MAXLINE     1024
#define MAX_FOOD    10

typedef struct
{
    int x;
    int y;
} PAIR;

typedef struct
{
    PAIR position;
    DIRECTION direction;
    int length;
    std::pair <int, int> segments [100];
    bool isAlive;
    int score;
} SNAKE_INFORMATION;

typedef enum
{
    NEW_CLIENT,
    CLIENT_DISCONNECTED,
    SERVER_UPDATE,
    CLIENT_UPDATE,
} MESSAGE_TYPE;

typedef struct
{
    MESSAGE_TYPE type;
    SNAKE_INFORMATION snake;
    SNAKE_INFORMATION clientSnake;
    std::pair <int, int> food [amountOfFood];
} GAME_DATA;

