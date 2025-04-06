#ifndef CAVALO_C
#define CAVALO_C
#include "raylib.h"
#include "cavalo.h"
#include "string.h"

Cavalo peca_cavalo(float x, float y, Texture des){ //cria o personagem
    Cavalo peca = {
        .position_x = x,
        .position_y = y,
        .desenho = des
    };

    return peca;
}

void AndaCavalo(float *x, float *y){
    //movimenta o personagem
    const float speed = 1;
    if (IsKeyDown(KEY_A)){*x = *x - speed;}
    else if (IsKeyDown(KEY_D)){*x = *x + speed;}
    else if (IsKeyDown(KEY_W)){*y = *y - speed;}
    else if (IsKeyDown(KEY_S)){*y = *y + speed;}
}



#endif