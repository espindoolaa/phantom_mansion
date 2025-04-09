#include "raylib.h"
#include "personagem.h"
#include "string.h"
#include "item.h"
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
        .itens = "oooo",
        .desenho = des,
        .hitbox = (Rectangle){x, y, 13 * size, 21 * size}
    };

    return pessoa;
}

void ModifyPerson(Personagem *person, int *framesCounter, int *currentFrame, Rectangle *scale, bool PodeAndar){
    const float speed = 3;
    const float frameSpeed = 3;
    Rectangle aux = (Rectangle){0, 63, 13, 21};

    int multplier = 13 * (*currentFrame);
    if(PodeAndar){
    if (IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)){
        person->position_x = person->position_x - speed;
        aux = (Rectangle){multplier, 0, 13, 21};
    }
    else if (IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)){
        person->position_x = person->position_x + speed;
        aux = (Rectangle){multplier, 21, 13, 21};
    }
    else if (IsKeyDown(KEY_UP)||IsKeyDown(KEY_W)){
        person->position_y = person->position_y - speed;
        aux = (Rectangle){multplier, 42, 13, 21};
    }
    else if (IsKeyDown(KEY_DOWN)||IsKeyDown(KEY_S)){
        person->position_y = person->position_y + speed;
        aux = (Rectangle){multplier, 63, 13, 21};
    }
    
    *framesCounter = *framesCounter + 1;
    if (*framesCounter >= (60/frameSpeed)){
        *currentFrame = *currentFrame + 1;
        if (*currentFrame > 2) {*currentFrame = 0;}
        *framesCounter = 0;
    }

    person->hitbox = (Rectangle){person->position_x, person->position_y, 13 * size, 21 * size};
    *scale = aux;
    }
}

int InteracPerson(Personagem *person, Item *item){
    if(CheckCollisionRecs(person->hitbox, item->hitbox) == true){
        DrawRectangle(20, 20, 300, 30, WHITE);
        DrawRectangleLines(20, 20, 300, 30, SKYBLUE);
        DrawText("APERTE E PARA INTERAGIR", 22, 25, 20, DARKBLUE);
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
    DrawRectangleRec(ret , WHITE);
    DrawRectangleLines(300 * scale_up, 600 * scale_up, 900 * scale_up, 250 * scale_up, SKYBLUE);
}

void CofreCheck(bool texto, char cod[4], int *senha, Personagem *person){ 
    if(texto){
        Caixa_de_Texto();
        DrawText("HMM... 3 DIGITOS, QUAL DEVE SER A SENHA?", 302 * scale_up, 602 * scale_up, 40, DARKBLUE);

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

        DrawText(cod, 302 * scale_up, 602 * scale_up + 40, 40, DARKBLUE);

        if(*senha == 3){
            if(strcmp(cod, "508") == 0){
                Caixa_de_Texto();
                DrawText("FUNCIONOU!", 302 * scale_up, 602 * scale_up, 40, DARKBLUE);
                DrawText("TINHA UM MACHADO DENTRO DO COFRE!", 302 * scale_up, 602 * scale_up + 40, 40, DARKBLUE);
                person->itens[2] = 'i';
            }
            else{
                Caixa_de_Texto();
                DrawText("SENHA ERRADA, MELECA.", 302 * scale_up, 602 * scale_up, 40, DARKBLUE);
            }
        }
    }
}

void XadrezCheck(bool texto, Personagem *person, Item *cavalo){ 
    if(texto){
        Caixa_de_Texto();
        DrawText("UM XADREZ COM A...PARTIDA NO MEIO?", 302 * scale_up, 602 * scale_up, 40, DARKBLUE);
        DrawText("DEVE ESTAR PERTO DO FIM!", 302 * scale_up, 672 * scale_up, 40, DARKBLUE);
        DrawRectangle(20, 50, 390, 30, WHITE);
        DrawRectangleLines(20, 50, 390, 30, SKYBLUE);
        DrawText("Use W, A, S, e D para mexer o cavalo", 22, 51, 20, DARKBLUE);
        

        int digito = GetCharPressed();
        MoveItem(digito, cavalo);
        if ((cavalo->position_x + 20 < 1065 && cavalo->position_x + 20> 1005) && (cavalo->position_y + 125 < 410 && cavalo->position_y + 125 > 338)){
            DrawText("colidiu", 200,900, 40, BLACK);
        }
    }
}
