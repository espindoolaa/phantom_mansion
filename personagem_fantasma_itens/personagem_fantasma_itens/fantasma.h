#ifndef FANTASMA_H
#define FANTASMA_H
#include "raylib.h"

typedef struct Fantasma{
    float position_x;
    float position_y;
    Texture desenho;
    Rectangle frame;
    Rectangle hitbox;
}Fantasma;

#include "fantasma.c"
#endif