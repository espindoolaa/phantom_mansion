#ifndef FANTASMA_C
#define FANTASMA_C
#include "raylib.h"
#include "fantasma.h"

Fantasma CreateGhost(float x, float y, Texture des){
    Fantasma ghost = {
        .position_x = x,
        .position_y = y,
        .desenho = des
    };
    
    return ghost;
}

void MovementGhost(float x_person, float y_person, float *x_ghost, float *y_ghost){
    const float speed = 0.5;
    if (x_person > *x_ghost){
        *x_ghost = *x_ghost + speed;
    }
    else{
        *x_ghost = *x_ghost - speed;
    }
    if (y_person > *y_ghost){
        *y_ghost = *y_ghost + speed;
    }
    else{
        *y_ghost = *y_ghost - speed;
    }
}
#endif