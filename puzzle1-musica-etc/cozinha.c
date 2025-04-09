#include <string.h>
#include "raylib.h"
#include "cozinha.h"
#include "personagem.h"
#include "fantasma.h"
#include "item.h"
#include "colisoes.h"
#define size 5
#define scale_up 1.2
#define Largura 1920
#define Altura 1080



void mapa2(Personagem persona2, Colisoes1 colisao_salao, Colisoes2 colisao_cozinha, int *numero_mapa, Texture fundo_cozinha, Texture perspectiva_cozinha, Music musica){
    bool PodeAndar = true;
    bool geladeira_na_tela = false; 
    bool portao_cozinha_na_tela = false;

    bool tela = true;
    int HasKey = 0;

    int senha_portao = 0;
    char cod_portao[4];
    int abriu_portao = 0;
    int senha = 0;
    char cod[4];
    *numero_mapa = 2;

    Texture portao_cozinha,sprite_alicate, sprite_geladeira;
    portao_cozinha = LoadTexture("./backgrounds/portao-cozinha.png");
    sprite_alicate = LoadTexture("./sprites/alicate.png");
    sprite_geladeira = LoadTexture("./sprites/fridge_puzzle.png");

    //personagem
    persona2.position_x = 100;
    Rectangle frame_personagem2 = (Rectangle){0, 63,39 ,84};
    //fantasma
    /*Fantasma info_baronesa;
    info_baronesa = CreateGhost(1940, 900, sprite_baronesa);
    Rectangle frame_baronesa = (Rectangle){0, 0, 15, 20};
    */
    //colisões de todos os objetos
    Colisoes2 colision_cozinha;
    colision_cozinha = CreateColision2();

    // Alicate 
    Item info_alicate = CreateItem(1500, 193, sprite_alicate, 1, 20, 20);
    info_alicate.coletavel = true;

    // Portão Cozinha
    Item info_portao_cozinha = CreateItem(1300, 750, sprite_alicate, 0, 50, 50);

    // Geladeira 
    Item info_geladeira = CreateItem(810, 200, sprite_alicate, 0, 50, 50);
    
    //musicas e sons
    Sound collect2 = LoadSound("./sound/collect.mp3");
    Sound alicate_usado =  LoadSound("./sound/alicate_usado.wav");

    //PlayMusicStream(musica);

    //
    int contador_frames2 = 0;
    int frame_atual2 = 0;
    //

    bool fechar_jogo2 = false;
    //SetWindowSize(Largura, Altura);
    //ToggleFullscreen();
    while (!fechar_jogo2){
        fechar_jogo2 = (WindowShouldClose());
        UpdateMusicStream(musica);

        if (CheckCollisionRecs(persona2.hitbox, colisao_cozinha.paredeesquerda)){
            fechar_jogo2 = true;
        }   
        //animacao do protagonista
        ModifyPerson(&persona2, &contador_frames2, &frame_atual2, &frame_personagem2, PodeAndar, *numero_mapa, colisao_salao, colisao_cozinha);
        //Interação com a geladeira
          
        

        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(fundo_cozinha, (Vector2){0,0}, 0, 1, WHITE);
        DrawTextureEx(perspectiva_cozinha, (Vector2){0,0}, 0, 1.875, WHITE);

          PortaoCheck(portao_cozinha_na_tela, cod_portao, &senha_portao, &persona2, &abriu_portao);
            if(InteracPerson(&persona2, &info_geladeira) == 1){
                geladeira_na_tela = !geladeira_na_tela; 
                PodeAndar = !geladeira_na_tela; 
            }
            //interacao com o portão
            
            // Desenho da geladeira acima do personagem principal 
            
            // efeito sonoro ao coletar o alicate
            if (InteracPerson(&persona2, &info_alicate) == 2) {
                PlaySound(alicate_usado); 
            }

            else
                DrawTextureEx(sprite_alicate, (Vector2){info_alicate.position_x, info_alicate.position_y}, 0, 1.8, WHITE);//

            if(geladeira_na_tela){
                DrawTextureEx(sprite_geladeira,(Vector2){400, 40}, 0, 1, WHITE);//
            }

            if(tela){
                DrawRectangle(1300, 0 * scale_up, 700, 1080 , BLACK);}
            
            if(InteracPerson(&persona2, &info_portao_cozinha) == 1){
                PodeAndar = !PodeAndar;
                portao_cozinha_na_tela = !portao_cozinha_na_tela;

                if(senha_portao == 3 && (strcmp(cod_portao, "CIN") != 0  || strcmp(cod_portao, "cin") != 0)){
                    senha_portao = 0;
                    cod_portao[senha] = '\0';
                    tela = !tela;
                }
            }
            
        

        /*
        DrawRectangleRec(todas_colisoes.cofre, PINK);
        DrawRectangleRec(todas_colisoes.estante, PINK);
        DrawRectangleRec(todas_colisoes.lareira, PINK);
        DrawRectangleRec(todas_colisoes.mesadireita, PINK);
        DrawRectangleRec(todas_colisoes.mesaesquerda, PINK);
        DrawRectangleRec(todas_colisoes.paredebaixo, PINK);
        DrawRectangleRec(todas_colisoes.paredebaixo_salacofre, PINK);
        DrawRectangleRec(todas_colisoes.paredecima, PINK);
        DrawRectangleRec(todas_colisoes.paredecima_salaescura, PINK);
        DrawRectangleRec(todas_colisoes.parededireita1_salacofre, PINK);
        DrawRectangleRec(todas_colisoes.parededireita2_salacofre, PINK);
        DrawRectangleRec(todas_colisoes.parededireita, PINK);
        DrawRectangleRec(todas_colisoes.paredeesquerda1_salaescura, PINK);
        DrawRectangleRec(todas_colisoes.paredeesquerda2_salaescura, PINK);
        DrawRectangleRec(todas_colisoes.paredeesquerda, PINK);
        */

        
        //DrawRectangleRec(info_personagem.hitbox, BLUE);
        DrawTexturePro(persona2.desenho, frame_personagem2, persona2.hitbox, (Vector2){persona2.hitbox.width - 13*size, persona2.hitbox.height - 21*size}, 0, WHITE);
        /*
        DrawRectangleRec(info_personagem.colision_left, WHITE);
        DrawRectangleRec(info_personagem.colision_right, WHITE);
        DrawRectangleRec(info_personagem.colision_up, WHITE);
        DrawRectangleRec(info_personagem.colision_down, WHITE);
        */
        //DrawRectangleRec(info_baronesa.hitbox, RED);
        
        EndDrawing();
    }

    UnloadSound(collect2); 


}