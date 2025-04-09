#include "raylib.h"
#include "personagem.h"
#include "string.h"
#include "item.h"
#include "colisoes.h"
#define size 5
#define scale_up 1.2





//para criar um personagem, primeiro importe este aquivo C
//vá no arquivo main e crie uma variavel 'sprite' do tipo 'Texture' e importe a imagem do personagem
//crie uma outra variavel para armazenar as informações do personagem, essa tem que ser do tipo 'Personagem'
//use a função 'CreatePerson' para inicializar o personagem


Personagem CreatePerson(float x, float y, Texture des){ //cria o personagem
    Personagem pessoa = {
        .position_x = x,
        .position_y = y,
        .arrow = 3,
        .itens = "oooo",
        .desenho = des,
        .hitbox = (Rectangle){x, y, 13 * size, 21 * size},
        .colision_left = (Rectangle){x - 2, y + 62, 1, 40},
        .colision_right = (Rectangle){x + 13 * size, y + 62, 2, 40},
        .colision_up = (Rectangle){x, y + 60, 13 * size - 5, 2},
        .colision_down = (Rectangle){x, y + 21 *size, 13 * size - 5, 21 * size + 2}
    };

    return pessoa;
}

void ModifyPerson(Personagem *person, int *framesCounter, int *currentFrame, Rectangle *scale, bool PodeAndar, int numero_mapa, Colisoes1 mapa_colisoes1, Colisoes2 mapa_colisoes2){
    const float speed = 3;
    const float frameSpeed = 3;
    Rectangle aux = (Rectangle){0, 63, 13, 21};

    bool vai_colidir = false;

    int multplier = 13 * (*currentFrame);
    if(PodeAndar){
    if (IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)){
        person->arrow = 0;
        if(numero_mapa == 1){vai_colidir = WillCollide1(person->colision_left, mapa_colisoes1);}
        else if(numero_mapa == 2){vai_colidir = WillCollide2(person->colision_left, mapa_colisoes2);}
        
        if (vai_colidir == false){
            person->position_x = person->position_x - speed;
            aux = (Rectangle){multplier, 0, 13, 21};
        }
        else {aux = (Rectangle){0, 21 * person->arrow, 13, 21};}
    }
    else if (IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)){
        person->arrow = 1;
        if(numero_mapa == 1){vai_colidir = WillCollide1(person->colision_right, mapa_colisoes1);}
        else if(numero_mapa == 2){vai_colidir = WillCollide2(person->colision_right, mapa_colisoes2);}

        if (vai_colidir == false){
            person->position_x = person->position_x + speed;
            aux = (Rectangle){multplier, 21, 13, 21};
        }
        else {aux = (Rectangle){0, 21 * person->arrow, 13, 21};}
    }
    else if (IsKeyDown(KEY_UP)||IsKeyDown(KEY_W)){
        person->arrow = 2;
        if(numero_mapa == 1){vai_colidir = WillCollide1(person->colision_up, mapa_colisoes1);}
        else if(numero_mapa == 2){vai_colidir = WillCollide2(person->colision_up, mapa_colisoes2);}

        if (vai_colidir == false){
            person->position_y = person->position_y - speed;
            aux = (Rectangle){multplier, 42, 13, 21};
        }
        else {aux = (Rectangle){0, 21 * person->arrow, 13, 21};}
    }
    else if (IsKeyDown(KEY_DOWN)||IsKeyDown(KEY_S)){
        person->arrow = 3;
        if(numero_mapa == 1){vai_colidir = WillCollide1(person->colision_down, mapa_colisoes1);}
        else if(numero_mapa == 2){vai_colidir = WillCollide2(person->colision_down, mapa_colisoes2);}

        if (vai_colidir == false){
            person->position_y = person->position_y + speed;
            aux = (Rectangle){multplier, 63, 13, 21};
        }
        else {aux = (Rectangle){0, 21 * person->arrow, 13, 21};}
    }
    else {
        aux = (Rectangle){0, 21 * person->arrow, 13, 21};
    }
    
    *framesCounter = *framesCounter + 1;
    if (*framesCounter >= (60/frameSpeed)){
        *currentFrame = *currentFrame + 1;
        if (*currentFrame > 2) {*currentFrame = 0;}
        *framesCounter = 0;
    }



    person->colision_left = (Rectangle){person->position_x - 2, person->position_y + 67, 1, 30};
    person->colision_right = (Rectangle){person->position_x + 13 * size, person->position_y + 67, 2, 30};
    person->colision_up = (Rectangle){person->position_x + 5, person->position_y + 60, 13 * size - 10, 2};
    person->colision_down = (Rectangle){person->position_x + 5, person->position_y + 21 *size, 13 * size - 10, 2};


    person->hitbox = (Rectangle){person->position_x, person->position_y, 13 * size, 21 * size};
    *scale = aux;
    }
}


int InteracPerson(Personagem *person, Item *item){
    if(CheckCollisionRecs(person->hitbox, item->hitbox) == true){
        DrawRectangle(20, 20, 300, 30, BLACK);
        DrawRectangleLines(20, 20, 300, 30, RED);
        DrawText("APERTE E PARA INTERAGIR", 22, 25, 20, GRAY);
        if (IsKeyPressed(KEY_E)){
            if(item->coletavel == true){
                person->itens[item->inventario] = 'i';
                item->position_x = -100;
                item->position_y = -100;
                item->hitbox = (Rectangle){item->position_x, item->position_y, 0, 0};
                return 2;
            }
            else{
                return 1;
            }
        }
    }
    return 0;
}

int LampCheck(Personagem *person){
    if(person->itens[0] == 'i' && person->itens[1] == 'i'/*&& interagir com a porta*/){
        return 1;
    }
    else 
        return 0;
}

void Caixa_de_Texto(){
    Rectangle ret = {300 * scale_up, 600 * scale_up, 900 * scale_up, 250 * scale_up};
    DrawRectangleRec(ret , BLACK);
    DrawRectangleLines(300 * scale_up, 600 * scale_up, 900 * scale_up, 250 * scale_up, RED);
}

void CofreCheck(bool texto, char cod[4], int *senha, Personagem *person){ 
    if(texto){
        Caixa_de_Texto();
        DrawText("HMM... 3 DIGITOS, QUAL DEVE SER A SENHA?", 302 * scale_up, 602 * scale_up, 40, GRAY);

        int digito = GetCharPressed();
        if((digito >= 48) && (digito <= 57) && (*senha < 3)){
                cod[*senha] = (char)digito;
                cod[*senha+1] = '\0';
                *senha += 1;
            }
        if(IsKeyPressed(KEY_BACKSPACE)){
            *senha -= 1;
            if(*senha < 0) *senha = 0;
            cod[*senha] = '\0';
        }

        DrawText(cod, 302 * scale_up, 602 * scale_up + 40, 40, GRAY);

        if(*senha == 3){
            if(strcmp(cod, "508") == 0){
                Caixa_de_Texto();
                DrawText("FUNCIONOU!", 302 * scale_up, 602 * scale_up, 40, GRAY);
                DrawText("TINHA UM MACHADO DENTRO DO COFRE!", 302 * scale_up, 602 * scale_up + 40, 40, GRAY);
                person->itens[2] = 'i';
            }
            else{
                Caixa_de_Texto();
                DrawText("SENHA ERRADA, MELECA.", 302 * scale_up, 602 * scale_up, 40, GRAY);
            }
        }
    }
}

void PortaoCheck(bool texto, char cod[4], int *senha, Personagem *person, int * avanca_mapa){ 
    if(texto){
        Caixa_de_Texto();
        DrawText("HMM... AGORA SÃO TRÊS LETRAS. QUAL SERÁ A SENHA?", 302 * scale_up, 602 * scale_up, 35, GRAY);

        int digito = GetCharPressed();
        if((digito >= 65 && digito <= 90) && (*senha < 3)){
                cod[*senha] = (char)digito;
                cod[*senha+1] = '\0';
                *senha += 1;
            }
        if(IsKeyPressed(KEY_BACKSPACE)){
            *senha -= 1;
            if(*senha < 0) *senha = 0;
            cod[*senha] = '\0';
        }

        DrawText(cod, 302 * scale_up, 602 * scale_up + 40, 40, GRAY);

        if(*senha == 3){
            if((strcmp(cod, "CIN") == 0) || (strcmp(cod, "cin") == 0)){
                Caixa_de_Texto();
                DrawText("FUNCIONOU!", 302 * scale_up, 602 * scale_up, 35, GRAY);
                DrawText("O PORTÃO ABRIU!", 302 * scale_up, 602 * scale_up + 40, 35, GRAY);
                *avanca_mapa+=1;
                person->itens[2] = 'i';
            }
            else{
                Caixa_de_Texto();
                DrawText("SENHA ERRADA, MELECA!", 302 * scale_up, 602 * scale_up, 40, GRAY);
            }
        }
    }
}

