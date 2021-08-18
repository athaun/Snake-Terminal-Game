#pragma once

#include <utility>
#include "input.h"
#include <string>

// Defines growth parameters for when the snake eats food.
#define segmentGrowth 2
#define scoreGrowth 50

class Snake {
    public:
        std::pair <int, int> segments [100];

        float score = 0;

        int snakeLength = 5;

        bool isAlive = true;

        DIRECTION direction = UP;

        std::string headCharacter = "<";

        void display ();

        void move (int x, int y);

        void death ();

        void findMove ();

        void initSnake (int x, int y);

        void collectFood ();
};