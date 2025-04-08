#include "raylib.h"
#include "salao.h"
#define Largura 1920
#define Altura 1080

typedef enum Telas { MENU, CREDITOS, GAMEPLAY } Telas;

int main()
{   
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Menu");

    Texture2D gameplay_background = LoadTexture("./backgrounds/GAMEPLAY.jpeg");
    Texture2D creditos_background = LoadTexture("./backgrounds/CREDITOS.jpeg");


    Telas tela_atual = MENU;
    
    Rectangle start = {       // botão de START
        1250,  // x
        750,  // y
        350,                  // largura
        90                   // altura
    };
    Rectangle creditos = {    // botão de CREDITOS
        1695,  // x
        910,       // y
        60,                  // largura
        60                 // altura
    };
    Rectangle voltar = {      // botão de VOLTAR
        1250,        // x
        100,       // y
        80,                  // largura
        80                    // altura
    };

    bool mouse_sobre_start = false;
    bool mouse_sobre_creditos = false;
    bool mouse_sobre_voltar = false;
    
    //SetTargetFPS(60);
    SetWindowSize(Largura, Altura);
    ToggleFullscreen();
    while (!WindowShouldClose())
    {
        Vector2 posicao_mouse = GetMousePosition();
        mouse_sobre_start = CheckCollisionPointRec(posicao_mouse, start);
        mouse_sobre_creditos = CheckCollisionPointRec(posicao_mouse, creditos);
        mouse_sobre_voltar = CheckCollisionPointRec(posicao_mouse, voltar);

        // TRANSIÇÃO DE TELAS
        switch (tela_atual) {
            case MENU: {
                if (mouse_sobre_start && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){             // transição para GAMEPLAY
                    tela_atual = GAMEPLAY;
                } else if (mouse_sobre_creditos && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){   // transição para CREDITOS
                    tela_atual = CREDITOS;
                }
            } break;

            case CREDITOS: {
                if (mouse_sobre_voltar && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){ // transição para MENU
                    tela_atual = MENU;
                }
            } break;

            case GAMEPLAY:
                mapa1();
                break;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE); 

        switch (tela_atual) {
            case MENU: {
                DrawTextureEx(gameplay_background, (Vector2){0,0}, 0, 1.2, WHITE);
                //DrawRectangleRec(start, mouse_sobre_start ? RED : MAROON); // desenha o botão START
                /*DrawText("START",
                start.x + start.width/2 - MeasureText("START", 20)/2,
                start.y + start.height/2 - 10, 
                20,
                WHITE);
            
                DrawRectangleRec(creditos, mouse_sobre_creditos ? RED : MAROON); // desenha o botão CREDITOS
                DrawText("CRÉDITOS",
                creditos.x + creditos.width/2 - MeasureText("CRÉDITOS", 20)/2,
                creditos.y + creditos.height/2 - 10, 
                20,
                WHITE);
                */
            } break;

            case CREDITOS: {
                DrawTextureEx(creditos_background, (Vector2){0,0}, 0, 1.2, WHITE);
                DrawRectangleRec(voltar, mouse_sobre_voltar ? RED : MAROON);     // desenha o botão VOLTAR
                DrawText("Voltar",
                voltar.x + voltar.width/2 + 10 - MeasureText("VOLTAR", 20)/2,
                voltar.y + voltar.height/2 - 10, 
                20,
                WHITE);
            } break;
            
            default: DrawText("CARREGANDO",
                voltar.x + voltar.width/2 - MeasureText("CARREGANDO", 20)/2,
                voltar.y + voltar.height/2 - 10, 
                20,
                BLACK);
        }
        EndDrawing();
    }
    UnloadTexture(gameplay_background);
    UnloadTexture(creditos_background);

    CloseWindow();
    return 0;
}