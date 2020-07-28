#pragma once

void keyInput ();
void setNonBlocking (int fd);

typedef enum 
{
    RIGHT,
    LEFT,
    UP,
    DOWN

}DIRECTION;