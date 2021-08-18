#include <iostream>
#include "audio.h"
#include "utilities.h"

std::string musicQueue[] = {
    "lines_of_code.ogg",
    "spy.ogg"
};

std::string soundFiles[] = {
    "food_eat.ogg"
};

void playQueue () {
    // Create a screen to play the audio in the background
    std::string playCommand = "screen -S snakeMusic -dm bash -c \"";

    // String all of the audio files into a single command to be executed in the audio screen
    for (int i = 0; i < ARRAY_SIZE(musicQueue); i++) {
        playCommand.append("canberra-gtk-play -V 0.1 -l 1 -f ./music/" + musicQueue[i] + " ; ");
    }
    playCommand.append("\" &");

    system(playCommand.c_str()); // Runs the bash command
}

void stopAudioProcess () {
    // Kills the screen that the music is playing in (and all child processes)
    system("2>/dev/null 1>&2 screen -X -S snakeMusic kill");
    system("2>/dev/null 1>&2 killall canberra-gtk-play");
}

void playSound (int soundID, float volume) {
    std::string volumeStr = std::to_string(volume); // Converts volume to a float
    // Pipes the output to /dev/null
    std::string command = "2>/dev/null 1>&2 bash -c \"canberra-gtk-play -V " + volumeStr + " -l 1 -f ./sound/" + soundFiles[soundID] + "\" & ";
    system(command.c_str()); // Runs the bash command
}