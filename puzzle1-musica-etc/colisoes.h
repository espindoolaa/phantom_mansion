#ifndef COLISOES_H
#define COLISOES_H
#include "raylib.h"

typedef struct Colisoes{
    Rectangle paredecima;
    Rectangle paredebaixo;
    Rectangle paredeesquerda;
    Rectangle parededireita;
    Rectangle mesaesquerda;
    Rectangle mesadireita;
    Rectangle cofre;
    Rectangle estante;
    Rectangle lareira;
    Rectangle paredebaixo_salacofre;
    Rectangle parededireita1_salacofre;
    Rectangle parededireita2_salacofre;
    Rectangle paredecima_salaescura;
    Rectangle paredeesquerda1_salaescura;
    Rectangle paredeesquerda2_salaescura;
}Colisoes;

Colisoes CreateColision();
bool WillCollide(Rectangle direction, Colisoes map);

#endif