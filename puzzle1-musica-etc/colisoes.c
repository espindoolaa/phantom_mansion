#include "raylib.h"
#include "colisoes.h"
#define scale_up 1.875 

Colisoes CreateColision(){
    Colisoes aux = {
        .paredecima = (Rectangle){0, 0, 1920, 125 * scale_up},
        .paredebaixo = (Rectangle){0, 1080, 1920, 1},
        .paredeesquerda = (Rectangle){-5, 0, 6, 1080},
        .parededireita = (Rectangle){1919, 0, 5, 1080},
        .mesaesquerda = (Rectangle){87*scale_up, 206*scale_up, 53*scale_up, 160*scale_up},
        .mesadireita = (Rectangle){799*scale_up, 481*scale_up, 141*scale_up, 50*scale_up},
        .cofre = (Rectangle){65*scale_up, 96*scale_up, 104*scale_up, 80*scale_up},
        .estante = (Rectangle){717*scale_up, 320*scale_up, 302*scale_up, 121*scale_up},
        .lareira = (Rectangle){773*scale_up, 92*scale_up, 136*scale_up, 72*scale_up},
        .paredebaixo_salacofre  = (Rectangle){0, 376*scale_up, 266*scale_up, 96*scale_up},
        .parededireita1_salacofre = (Rectangle){237*scale_up, 115*scale_up, 29*scale_up, 90*scale_up},
        .parededireita2_salacofre = (Rectangle){237*scale_up, 302*scale_up, 29*scale_up, 170*scale_up},
        .paredecima_salaescura = (Rectangle){625*scale_up, 292*scale_up, 399*scale_up, 106*scale_up},
        .paredeesquerda1_salaescura = (Rectangle){625*scale_up, 292*scale_up, 28*scale_up, 154*scale_up},
        .paredeesquerda2_salaescura = (Rectangle){625*scale_up, 531*scale_up, 28*scale_up, 96*scale_up}
    };

    return aux;
}

bool WillCollide(Rectangle direction, Colisoes map){
    bool retorno = false;
    if (CheckCollisionRecs(direction, map.cofre) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.estante) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.lareira) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.mesadireita) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.mesaesquerda) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredebaixo) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredebaixo_salacofre) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredecima) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredecima_salaescura) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.parededireita1_salacofre) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.parededireita2_salacofre) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.parededireita) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredeesquerda1_salaescura) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredeesquerda2_salaescura) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredeesquerda) == true){retorno = true;}

    return retorno;
}
