#include <stdlib.h>
#include <time.h>
#include "utilities.h"

using namespace std;

void seedRandom () {
    srand(time(NULL));
}

int random (int min, int max) {
    return rand() % (max - min + 1) + min;
}

// void printStat (string str) {

// }