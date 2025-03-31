#define max_bag 5
#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include "raylib.h"

typedef struct Personagem{
    float position_x;
    float position_y;
    char itens[max_bag];
    Texture desenho;
    Rectangle frame;
    Rectangle hitbox;
}Personagem; 

#include "personagem.c"
#endif