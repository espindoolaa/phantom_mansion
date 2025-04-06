#ifndef XADREZ_H
#define XADREZ_H
#include "raylib.h"

typedef struct Xadrez{
    float position_x;
    float position_y;
    Texture desenho;
}Xadrez;

#include "xadrez.c"
#endif