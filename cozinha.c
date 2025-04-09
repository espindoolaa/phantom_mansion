#include <string.h>
#include "raylib.h"
#include "salao.h"
#include "personagem.h"
#include "fantasma.h"
#include "item.h"
#include "colisoes.h"
#define size 5
#define scale_up 1.2
#define Largura 1920
#define Altura 1080

void mapa2(){

    InitWindow(Largura, Altura, "Phantom Mansion");
    InitAudioDevice(); // pode ter audio agora 

    bool PodeAndar = true;
    bool dica_na_tela = false;
    bool cofre_na_tela = false;
    int senha = 0;
    char cod[4];

    //area dos sprites
    Texture fundo_mapa1, perspectiva_mapa1, sprite_personagem, sprite_baronesa, sprite_diario, sprite_lamp, sprite_lamp_fire, sprite_oil, sprite_dica_p1;
    fundo_mapa1 = LoadTexture("./backgrounds/salao.jpeg");
    perspectiva_mapa1 = LoadTexture("./backgrounds/salao_perspectiva.png");

    sprite_personagem = LoadTexture("./sprites/spritesheet_personagem.png");
    sprite_baronesa = LoadTexture("./sprites/spritesheet_fantasma.png");
    sprite_diario = LoadTexture("./sprites/item.png");

    sprite_lamp = LoadTexture("./sprites/lamp.png");
    sprite_lamp_fire = LoadTexture("./sprites/light lamp.png");
    sprite_oil = LoadTexture("./sprites/oil.png");
    sprite_dica_p1 = LoadTexture("./sprites/dicap1.png");

    //personagem
    Personagem info_personagem;
    info_personagem = CreatePerson(Largura/2 - 30, 900, sprite_personagem);
    Rectangle frame_personagem = (Rectangle){0, 63,39 ,84};

    //fantasma
    Fantasma info_baronesa;
    info_baronesa = CreateGhost(1940, 900, sprite_baronesa);
    Rectangle frame_baronesa = (Rectangle){0, 0, 15, 20};

    //colisões de todos os objetos
    Colisoes1 todas_colisoes;
    todas_colisoes = CreateColision1();

    //itens(coletaveis e interagiveis)
    Item info_dica_p1 = CreateItem(1500, 900, sprite_diario, 0, sprite_diario.width, sprite_diario.height);
    //Item info_diario1 = CreateItem(1500, 900, sprite_diario);

    Item info_lamp = CreateItem(1160 * scale_up, 20 * scale_up, sprite_lamp, 0, sprite_lamp.width, sprite_lamp.height + 20);
    info_lamp.coletavel = true;
    Item info_oil = CreateItem(25 * scale_up, 800 * scale_up, sprite_oil, 1, sprite_oil.width, sprite_oil.height);
    info_oil.coletavel = true;

    Item info_cofre = CreateItem(145 * scale_up, 150 * scale_up, sprite_diario, 0, sprite_diario.width, sprite_diario.height + 10);

    //musicas e sons
    Music musica_fase1 = LoadMusicStream("./sound/firstfloor.mp3");
    Music musica_fase2 = LoadMusicStream("./sound/secondfloor.mp3");
    Music musica = musica_fase1;
    Sound collect = LoadSound("./sound/collect.mp3");

    PlayMusicStream(musica_fase1);
    PlayMusicStream(musica_fase2);

    //
    int contador_frames = 0;
    int frame_atual = 0;
    //

    bool fechar_jogo = false;
    SetTargetFPS(120);
    //SetWindowSize(Largura, Altura);
    //ToggleFullscreen();
    while (!fechar_jogo){
        fechar_jogo = (WindowShouldClose());
        HideCursor();


        //menu



        if(IsKeyPressed(KEY_SPACE)){//mudar quando entrar na fase 2
            musica = musica_fase2;
        }
        UpdateMusicStream(musica);

        //animacao do protagonista
        ModifyPerson(&info_personagem, &contador_frames, &frame_atual, &frame_personagem, PodeAndar, todas_colisoes);

        //spawnar e animar o fantasma, mudar a consequencia da colisao
        if (info_personagem.itens[3] == 'i'){
            MovementGhost(info_personagem.position_x, info_personagem.position_y, &info_baronesa, frame_atual, &frame_baronesa);
            if(CheckCollisionRecs(info_personagem.hitbox, info_baronesa.hitbox) == true){fechar_jogo = true;}
        }

        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(fundo_mapa1, (Vector2){0,0}, 0, scale_up, WHITE);

        //retangulo preto no escritorio
        DrawTextureEx(sprite_diario, (Vector2){info_dica_p1.position_x, info_dica_p1.position_y}, 0, 4, WHITE);
        

        //interacao com a dica da fase 1
        if(InteracPerson(&info_personagem, &info_dica_p1) == 1){
            dica_na_tela = !dica_na_tela; 
            PodeAndar = !dica_na_tela; 
        }
        if(dica_na_tela){
            DrawTextureEx(sprite_dica_p1,(Vector2){640, 160}, 0, 1, WHITE);//
        }

        //efeito sonoro de coletar
        if(InteracPerson(&info_personagem, &info_oil) == 2||InteracPerson(&info_personagem, &info_lamp) == 2){
            PlaySound(collect); 
        }

        //interacao com o cofre
        if(InteracPerson(&info_personagem, &info_cofre) == 1){
            PodeAndar = !PodeAndar;
            cofre_na_tela = !cofre_na_tela;
            if(senha == 3&&strcmp(cod, "508") != 0){
                senha = 0;
                cod[senha] = '\0';
            }
        }
        CofreCheck(cofre_na_tela, cod, &senha, &info_personagem);
        
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

        //itens
        DrawTextureEx(sprite_lamp, (Vector2){info_lamp.position_x, info_lamp.position_y}, 0, 5, WHITE);
        DrawTextureEx(sprite_oil, (Vector2){info_oil.position_x, info_oil.position_y}, 0, 5, WHITE);
        
        //DrawRectangleRec(info_personagem.hitbox, BLUE);
        DrawTexturePro(sprite_personagem, frame_personagem, info_personagem.hitbox, (Vector2){info_personagem.hitbox.width - 13*size, info_personagem.hitbox.height - 21*size}, 0, WHITE);
        /*
        DrawRectangleRec(info_personagem.colision_left, WHITE);
        DrawRectangleRec(info_personagem.colision_right, WHITE);
        DrawRectangleRec(info_personagem.colision_up, WHITE);
        DrawRectangleRec(info_personagem.colision_down, WHITE);
        */
        //DrawRectangleRec(info_baronesa.hitbox, RED);

        DrawTexturePro(sprite_baronesa, frame_baronesa, info_baronesa.hitbox, (Vector2){info_baronesa.hitbox.width - 15*size, info_baronesa.hitbox.height - 20*size}, 0, WHITE);
        DrawTextureEx(perspectiva_mapa1, (Vector2){0,0}, 0, 1.875, WHITE);

        if(LampCheck(&info_personagem) == 0){
            DrawRectangle(980 * scale_up, 455 * scale_up, 945 * scale_up, 450 * scale_up, BLACK);
        }
        EndDrawing();
    }

    UnloadTexture(fundo_mapa1);
    UnloadTexture(perspectiva_mapa1);

    UnloadTexture(sprite_personagem);
    UnloadTexture(sprite_baronesa);
    UnloadTexture(sprite_diario);

    UnloadTexture(sprite_lamp);
    UnloadTexture(sprite_lamp_fire);
    UnloadTexture(sprite_oil);

    UnloadMusicStream(musica_fase1);     
    UnloadMusicStream(musica_fase2);   
    UnloadSound(collect);
    CloseAudioDevice();     

    CloseWindow();
}