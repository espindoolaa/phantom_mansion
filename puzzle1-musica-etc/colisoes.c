#include "raylib.h"
#include "colisoes.h"
#define scale_up 1.875 

Colisoes1 CreateColision1(){
    Colisoes1 aux = {
        .paredecima = (Rectangle){0, 0, 1920, 125 * scale_up},
        .paredebaixo = (Rectangle){0, 1080, 1920, 1},
        .paredeesquerda = (Rectangle){-5, 0, 6, 1080},
        .parededireita = (Rectangle){1919, 0, 5, 1080},
        .parededireita_salaescura = (Rectangle){1910, 540, 10, 540},
        .mesaesquerda = (Rectangle){87*scale_up, 206*scale_up, 53*scale_up, 160*scale_up},
        .mesadireita = (Rectangle){799*scale_up, 481*scale_up, 141*scale_up, 50*scale_up},
        .cofre = (Rectangle){65*scale_up, 96*scale_up, 104*scale_up, 80*scale_up},
        .estante = (Rectangle){717*scale_up, 320*scale_up, 302*scale_up, 121*scale_up},
        .lareira = (Rectangle){773*scale_up, 92*scale_up, 136*scale_up, 72*scale_up},
        .paredebaixo_salacofre  = (Rectangle){0, 376*scale_up, 266*scale_up, 96*scale_up},
        .parededireita1_salacofre = (Rectangle){237*scale_up, 115*scale_up, 29*scale_up, 90*scale_up},
        .parededireita2_salacofre = (Rectangle){237*scale_up, 302*scale_up, 29*scale_up, 170*scale_up},
        .paredecima_salaescura = (Rectangle){625*scale_up, 315*scale_up, 399*scale_up, 83*scale_up},
        .paredeesquerda1_salaescura = (Rectangle){625*scale_up, 315*scale_up, 28*scale_up, 131*scale_up},
        .paredeesquerda2_salaescura = (Rectangle){625*scale_up, 531*scale_up, 28*scale_up, 96*scale_up}
    };

    return aux;
}

Colisoes2 CreateColision2(){
    Colisoes2 aux = {
        .paredecima = (Rectangle){0,0,1920, 126},
        .paredebaixo = (Rectangle){0,1080,1920, 5},
        .paredeesquerda = (Rectangle){5,0,6, 1080},
        .parededireita = (Rectangle){1919, 0, 5, 1080},
        .armario = (Rectangle){781*scale_up, 3*scale_up, 243*scale_up, 162*scale_up},
        .balcao = (Rectangle){177*scale_up, 0, 399*scale_up, 150*scale_up},
        .caixa1 = (Rectangle){840*scale_up, 0, 180*scale_up, 202*scale_up},
        .caixa2 = (Rectangle){931*scale_up, 0, 89*scale_up, 247*scale_up},
        .mesa = (Rectangle){131*scale_up, 238*scale_up, 333*scale_up, 160*scale_up},
        .parede1 = (Rectangle){752*scale_up, 0, 29*scale_up, 395*scale_up},
        .parede2 = (Rectangle){752*scale_up, 498*scale_up, 29*scale_up, 78*scale_up},
        .escombro1 = (Rectangle){598*scale_up, 275*scale_up, 100*scale_up, 80*scale_up},
        .escombro2 = (Rectangle){597*scale_up, 431*scale_up, 115*scale_up, 97*scale_up},
        .escombro3 = (Rectangle){860*scale_up, 425*scale_up, 115*scale_up, 97*scale_up}
    };

    return aux;
}

bool WillCollide1(Rectangle direction, Colisoes1 map){
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
    if (CheckCollisionRecs(direction, map.parededireita_salaescura) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredeesquerda1_salaescura) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredeesquerda2_salaescura) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredeesquerda) == true){retorno = true;}

    return retorno;
}

bool WillCollide2(Rectangle direction, Colisoes2 map){
    bool retorno = false;
    if (CheckCollisionRecs(direction, map.armario) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.balcao) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.caixa1) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.caixa2) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.escombro1) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.escombro2) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.escombro3) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.mesa) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.parede1) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.parede2) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredebaixo) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.paredecima) == true){retorno = true;}
    if (CheckCollisionRecs(direction, map.parededireita) == true){retorno = true;}
    //if (CheckCollisionRecs(direction, map.paredeesquerda) == true){retorno = true;}

    return retorno;
}
