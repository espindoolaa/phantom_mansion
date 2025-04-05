#ifndef PERSONAGEM_C
#define PERSONAGEM_C
#include "raylib.h"
#include "personagem.h"
#include "string.h"
#define size 5


//para criar um personagem, primeiro importe este aquivo C
//vá no arquivo main e crie uma variavel 'sprite' do tipo 'Texture' e importe a imagem do personagem
//crie uma outra variavel para armazenar as informações do personagem, essa tem que ser do tipo 'Personagem'
//use a função 'CreatePerson' para inicializar o personagem


Personagem CreatePerson(float x, float y, Texture des){ //cria o personagem
    Personagem pessoa = {
        .position_x = x,
        .position_y = y,
        .itens = "oooo",
        .desenho = des,
        .hitbox = (Rectangle){x, y, 13 * size, 21 * size}
    };

    return pessoa;
}

void ModifyPerson(float *x, float *y, int *framesCounter, int *currentFrame, Rectangle *scale, Rectangle *destination){
    const float speed = 0.2;
    const int frameSpeed = 2;
    Rectangle aux = (Rectangle){0, 63, 13, 21};

    int multplier = 13 * (*currentFrame);

    if (IsKeyDown(KEY_LEFT)){
        *x = *x - speed;
        aux = (Rectangle){multplier, 0, 13, 21};
    }
    else if (IsKeyDown(KEY_RIGHT)){
        *x = *x + speed;
        aux = (Rectangle){multplier, 21, 13, 21};
    }
    else if (IsKeyDown(KEY_UP)){
        *y = *y - speed;
        aux = (Rectangle){multplier, 42, 13, 21};
    }
    else if (IsKeyDown(KEY_DOWN)){
        *y = *y + speed;
        aux = (Rectangle){multplier, 63, 13, 21};
    }
    
    //if (IsKeyPressed(KEY_E)){ //se ele apertou o botão de coletar
        //se a colisão do personagem estava dentro da colisão do item
            //-verifica qual item é
            //-abre um for no range max_bag
                //-se bag[i] == 'o' {bag[i] = item}
    //}

    *framesCounter = *framesCounter + 1;
    if (*framesCounter >= (240/frameSpeed)){
        *currentFrame = *currentFrame + 1;
        if (*currentFrame > 2) {*currentFrame = 0;}
        *framesCounter = 0;
    }
    *destination = (Rectangle){*x, *y, aux.width * size, aux.height * size};
    *scale = aux;
}

#endif