#ifndef FANTASMA_H
#define FANTASMA_H
#include "raylib.h"

typedef struct Fantasma{
    float position_x;
    float position_y;
    Texture desenho;
    Rectangle hitbox;
}Fantasma;

Fantasma CreateGhost(float x, float y, Texture des);
void MovementGhost(float x_person, float y_person, Fantasma *ghost, int currentFrame, Rectangle *frame);

#endif