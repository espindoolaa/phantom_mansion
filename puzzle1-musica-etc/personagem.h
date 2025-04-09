#define max_bag 5
#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include "raylib.h"
#include "item.h"
#include "colisoes.h"

typedef struct Personagem{
    float position_x;
    float position_y;
    int arrow;
    char itens[max_bag];
    Texture desenho;
    Rectangle hitbox;
    Rectangle colision_left;
    Rectangle colision_right;
    Rectangle colision_up;
    Rectangle colision_down;
}Personagem; 

Personagem CreatePerson(float x, float y, Texture des);
void ModifyPerson(Personagem *person, int *framesCounter, int *currentFrame, Rectangle *scale, bool PodeAndar, int numero_mapa, Colisoes1 mapa_colisoes, Colisoes2 mapa_colisoes2);
int InteracPerson(Personagem *person, Item *item);
int LampCheck(Personagem *person);
void Caixa_de_Texto();
void CofreCheck(bool texto, char cod[4], int *senha, Personagem *person);
void PortaoCheck(bool texto, char cod[4], int *senha, Personagem *person, int * avanca_mapa);
#endif