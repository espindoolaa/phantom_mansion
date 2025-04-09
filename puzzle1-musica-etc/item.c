#include "item.h"
#include "raylib.h"
#define size 5

//para criar um item, primeiro importe este aquivo Cs
//vá no arquivo main e crie uma variavel 'sprite' do tipo 'Texture' e importe a imagem do item
//crie uma outra variavel para armazenar as informações do item, essa tem que ser do tipo 'Item'
//use a função 'CreateItem' para inicializar o item
//obs: funciona para qualquer tipo de item coletavel

Item CreateItem(float x, float y, Texture des, int in, int size_x, int size_y){
    Item any = {
        .position_x = x,
        .position_y = y,
        .coletavel = false,
        .inventario = in,
        .desenho = des,
        .hitbox = (Rectangle){x, y, size_x * size, size_y * size}
    };

    return any;
}

bool SafePassword(){
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 48) && (key <= 57)) keyPressed = true;
    return keyPressed;
}