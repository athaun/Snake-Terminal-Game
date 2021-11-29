#pragma once
#include "networkTypes.h"
/** 
 * Start:
 * one class, that choses if it is a Client or server:
 * 
   Data:
    serverClient: Client

 * Methods:
     init (bool server)
     getGameData()
     setGameData()
     tickUpdate() sends/receives (update game data)
     
 * Init()
 * if Server:
 * Initialize server
 * 
 * if Client:
 * initialize client
 * send beacon to server ()
 * search for server, if found, connect to server
*/


class Network {
    public:
        bool isServer;
        GAME_DATA game_data;
        GAME_DATA other_game_data;

        void init ();

        GAME_DATA getGameData ();

        void setGameData (GAME_DATA data);

        void update ();
};