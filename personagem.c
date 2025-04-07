#ifndef PERSONAGEM_C
#define PERSONAGEM_C
#include "raylib.h"
#include "personagem.h"
#include "string.h"

Personagem CreatePerson(float x, float y, Texture des){ //cria o personagem
    Personagem pessoa = {
        .position_x = x,
        .position_y = y,
        .itens = "oooo",
        .colete = 0,
        .desenho = des
    };

    return pessoa;
}

void ModifyPerson(float *x, float *y, int *e, bool PodeAndar){
    //movimenta o personagem
    const float speed = 2;
    if (PodeAndar){
    if (IsKeyDown(KEY_LEFT)){*x = *x - speed;}
    else if (IsKeyDown(KEY_RIGHT)){*x = *x + speed;}
    else if (IsKeyDown(KEY_UP)){*y = *y - speed;}
    else if (IsKeyDown(KEY_DOWN)){*y = *y + speed;}}

    if (IsKeyPressed(KEY_E)){*e = 1;}
    else{*e = 0;}

    /*
    //detecta se ele pegou algum item
    if (IsKeyPressed(KEY_E)){ //se ele apertou o botão de coletar

        //se a colisão do personagem estava dentro da colisão do item
            //-verifica qual item é
            //-abre um for no range max_bag
                //-se bag[i] == 'o' {bag[i] = item}
    }
    */
}

#endif