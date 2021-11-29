#pragma once

#include <string>
#include "Snake.h"
#include "network.h"


extern bool devTesting;
extern bool running;
extern Snake snake;
extern Snake otherSnake;
extern Network network;
extern std::string server_ip;
extern int server_port;