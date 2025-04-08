#include "item.h"
#include "raylib.h"
#define size 5
#define scale_up 1.2

//para criar um item, primeiro importe este aquivo C
//vá no arquivo main e crie uma variavel 'sprite' do tipo 'Texture' e importe a imagem do item
//crie uma outra variavel para armazenar as informações do item, essa tem que ser do tipo 'Item'
//use a função 'CreateItem' para inicializar o item
//obs: funciona para qualquer tipo de item coletavel

Item CreateItem(float x, float y, Texture des, int in){
    Item any = {
        .position_x = x,
        .position_y = y,
        .coletavel = false,
        .inventario = in,
        .desenho = des,
        .hitbox = (Rectangle){x, y, des.width * size, des.height * size}
    };

    return any;
}

bool SafePassword(){
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 48) && (key <= 57)) keyPressed = true;
    return keyPressed;
}

void MoveItem(int char_apertado, Item *movido){
    //movimenta o personagem
    const float speed = 14;
    if (char_apertado == 65){movido->position_x = movido->position_x - speed;}
    else if (char_apertado == 68){movido->position_x = movido->position_x + speed;}
    else if (char_apertado == 87){movido->position_y = movido->position_y - speed;}
    else if (char_apertado == 83){movido->position_y = movido->position_y + speed;}
}