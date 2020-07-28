#pragma once

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

void seedRandom ();
int random (int min, int max);