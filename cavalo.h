#ifndef CAVALO_H
#define CAVALO_H
#include "raylib.h"

typedef struct Cavalo{
    float position_x;
    float position_y;
    Texture desenho;
}Cavalo;

#include "cavalo.c"
#endif