#ifndef ITEM_H
#define ITEM_H
#include "raylib.h"

typedef struct Item{
    float position_x;
    float position_y;
    bool coletavel;
    int inventario;
    Texture desenho;
    Rectangle hitbox;
}Item;

Item CreateItem(float x, float y, Texture des, int in, int size_x, int size_y);
bool SafePassword();

#endif