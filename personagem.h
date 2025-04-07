#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#define max_bag 5
#include "item.h"
#include "raylib.h"

typedef struct Personagem{
    float position_x;
    float position_y;
    char itens[max_bag];
    Texture desenho;
    Rectangle hitbox;
}Personagem; 

Personagem CreatePerson(float x, float y, Texture des);
void ModifyPerson(Personagem *person, int *framesCounter, int *currentFrame, Rectangle *scale, bool PodeAndar);
int InteracPerson(Personagem *person, Item *item);
int LampCheck(Personagem *person);
void Caixa_de_Texto();
void CofreCheck(bool texto, char cod[4], int *senha, Personagem *person);
void XadrezCheck(bool texto, Personagem *person, Item *cavalo);







#endif