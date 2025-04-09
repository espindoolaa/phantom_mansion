#ifndef COLISOES_H
#define COLISOES_H
#include "raylib.h"

typedef struct Colisoes1{
    Rectangle paredecima;
    Rectangle paredebaixo;
    Rectangle paredeesquerda;
    Rectangle parededireita;
    Rectangle parededireita_salaescura;
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
}Colisoes1;

typedef struct Colisoes2{
    Rectangle paredecima;
    Rectangle paredebaixo;
    Rectangle paredeesquerda;
    Rectangle parededireita;
    Rectangle mesa;
    Rectangle balcao;
    Rectangle armario;
    Rectangle caixa1;
    Rectangle caixa2;
    Rectangle parede1;
    Rectangle parede2;
    Rectangle escombro1;
    Rectangle escombro2;
    Rectangle escombro3;
}Colisoes2;


Colisoes1 CreateColision1();
Colisoes2 CreateColision2();
bool WillCollide1(Rectangle direction, Colisoes1 map);
bool WillCollide2(Rectangle direction, Colisoes2 map);

#endif