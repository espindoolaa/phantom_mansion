#include "raylib.h"
#include "fantasma.h"
#define size 5
#define scale_up 1.2

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

void MovementGhost(float x_person, float y_person, Fantasma *ghost, int currentFrame, Rectangle *frame){
    const float speed = 1;
    Rectangle aux = {ghost->position_x, ghost->position_y, 15, 20};

    int multplier = 15 * currentFrame;

    if (x_person > ghost->position_x){
        ghost->position_x = ghost->position_x + speed;
        aux = (Rectangle){multplier, 20, 15, 20};
    }
    else if(x_person < ghost->position_x){
        ghost->position_x = ghost->position_x - speed;
        aux = (Rectangle){multplier, 0, 15, 20};
    }
    else{
        aux = (Rectangle){multplier, 20, 15, 20};
    }

    if (y_person > ghost->position_y){
        ghost->position_y = ghost->position_y + speed;
    }
    else if(y_person < ghost->position_y){
        ghost->position_y = ghost->position_y - speed;
    }


    ghost->hitbox = (Rectangle){ghost->position_x, ghost->position_y, aux.width * size, aux.height * size};
    *frame = aux;
}
