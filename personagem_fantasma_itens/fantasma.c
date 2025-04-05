#ifndef FANTASMA_C
#define FANTASMA_C
#include "raylib.h"
#include "fantasma.h"
#define size 5

//para criar um inimigo, primeiro importe este aquivo C
//vá no arquivo main e crie uma variavel 'sprite' do tipo 'Texture' e importe a imagem do inimigo
//crie uma outra variavel para armazenar as informações do inimigo, essa tem que ser do tipo 'Fantasma'
//use a função 'CreateGhost' para inicializar o inimigo

Fantasma CreateGhost(float x, float y, Texture des){
    Fantasma ghost = {
        .position_x = x,
        .position_y = y,
        .desenho = des,
        .hitbox = (Rectangle){x, y, 15 * size, 20 * size}
    };
    
    return ghost;
}

void MovementGhost(float x_person, float y_person, float *x_ghost, float *y_ghost, int currentFrame, Rectangle *frame, Rectangle *destination){
    const float speed = 0.05;
    Rectangle aux = {*x_ghost, *y_ghost, 15, 20};

    int multplier = 15 * currentFrame;

    if (x_person > *x_ghost){
        *x_ghost = *x_ghost + speed;
        aux = (Rectangle){multplier, 20, 15, 20};
    }
    else{
        *x_ghost = *x_ghost - speed;
        aux = (Rectangle){multplier, 0, 15, 20};
    }
    if (y_person > *y_ghost){
        *y_ghost = *y_ghost + speed;
    }
    else{
        *y_ghost = *y_ghost - speed;
    }

    *destination = (Rectangle){*x_ghost, *y_ghost, aux.width * size, aux.height * size};
    *frame = aux;
}
#endif