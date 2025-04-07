#ifndef ITEM_H
#define ITEM_H
#include "raylib.h"

typedef struct Item{
    float position_x;
    float position_y;
    Texture desenho;
}Item;

#include "item.c"
#endif