#ifndef ITEM_C
#define ITEM_C
#include "item.h"
#include "raylib.h"

Item CreateItem(float x, float y, Texture des){
    Item any = {
        .position_x = x,
        .position_y = y,
        .desenho = des
    };

    return any;
}



#endif