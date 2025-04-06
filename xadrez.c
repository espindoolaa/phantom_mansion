#ifndef XADREZ_C
#define XADREZ_C
#include "raylib.h"
#include "xadrez.h"

Xadrez AbreTabuleiro(float x, float y, Texture des){
    Xadrez tabuleiro = {
        .position_x = x,
        .position_y = y,
        .desenho = des
    };
    
    return tabuleiro;
}
#endif