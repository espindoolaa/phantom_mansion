#include <string.h>
#include "raylib.h"
#include "personagem.h"
#include "personagem.c"
#include "fantasma.c"
#include "item.c"



int main(){
    const int Largura = 1920, Altura = 1080;

    InitWindow(Largura, Altura, "Phantom Mansion");
    InitAudioDevice(); // pode ter audio agora //m

    bool PodeAndar = true;
    bool dica_na_tela = false;

    //area dos sprites
    Texture fundo_mapa1, sprite_personagem, sprite_baronesa, sprite_diario, sprite_lamp, sprite_lamp_fire, sprite_oil, sprite_dica_p1;
    fundo_mapa1 = LoadTexture("./backgrounds/mapa1.jpg");

    sprite_personagem = LoadTexture("./sprites/spritesheet_personagem.png");
    sprite_baronesa = LoadTexture("./sprites/spritesheet_fantasma.png");
    sprite_diario = LoadTexture("./sprites/item.png");

    sprite_lamp = LoadTexture("./sprites/lamp.png");
    sprite_lamp_fire = LoadTexture("./sprites/light lamp.png");
    sprite_oil = LoadTexture("./sprites/oil.png");
    sprite_dica_p1 = LoadTexture("./sprites/dicap1.png");
    //

    //personagem
    Personagem info_personagem;
    info_personagem = CreatePerson(Largura/2 - 30, 900, sprite_personagem);
    Rectangle frame_personagem = (Rectangle){0, 63,39 ,84};

    //fantasma
    Fantasma info_baronesa;
    info_baronesa = CreateGhost(1940, 900, sprite_baronesa);//
    Rectangle frame_baronesa = (Rectangle){0, 0, 15, 20};

    //itens(coletaveis e interagiveis)
    Item info_dica_p1 = CreateItem(1500, 900, sprite_diario, 0);
    //Item info_diario1 = CreateItem(1500, 900, sprite_diario);

    Item info_lamp = CreateItem(1160 * 1.2, 20 * 1.2, sprite_lamp, 0);
    info_lamp.coletavel = true;
    Item info_oil = CreateItem(25 * 1.2, 800 * 1.2, sprite_oil, 1);
    info_oil.coletavel = true;

    //porta_principal, porta_escritorio, porta_cozinha, porta_armazem, porta_segundo_andar
    //para fazer as portas de
    //portas
    //cofre
    //dialogo
    //


    //Porta porta_escritorio = CreateDoor();
    //Item cofre
    //

    //musicas e sons
    Music musica_fase1 = LoadMusicStream("./sound/firstfloor.mp3");
    Music musica_fase2 = LoadMusicStream("./sound/secondfloor.mp3");
    Music musica = musica_fase1;
    Sound collect = LoadSound("./sound/collect.mp3");

    PlayMusicStream(musica_fase1);
    PlayMusicStream(musica_fase2);
    //

    //
    int contador_frames = 0;
    int frame_atual = 0;
    //

    bool fechar_jogo = false;
    SetTargetFPS(120);
    SetWindowSize(Largura, Altura);
    ToggleFullscreen();
    while (!fechar_jogo){
        fechar_jogo = (WindowShouldClose());
        HideCursor();


        //menu



        if(IsKeyPressed(KEY_SPACE)){//mudar quando entrar na fase 2
            musica = musica_fase2;
        }
        UpdateMusicStream(musica);//

        ModifyPerson(&info_personagem, &contador_frames, &frame_atual, &frame_personagem, PodeAndar);

        //
        // if (info_personagem.itens[3] == 'i'){
        //     MovementGhost(info_personagem.position_x, info_personagem.position_y, &info_baronesa, frame_atual, &frame_baronesa);
        //     if(CheckCollisionRecs(info_personagem.hitbox, info_baronesa.hitbox) == true){fechar_jogo = true;}
        // }

        BeginDrawing();

        ClearBackground(WHITE);
        DrawTextureEx(fundo_mapa1, (Vector2){0,0}, 0, 1.2, WHITE);

        if(InteracPerson(&info_personagem, &info_dica_p1) == 1){
            dica_na_tela = !dica_na_tela; 
            PodeAndar = !dica_na_tela; 
        }
        if(dica_na_tela){
            DrawTextureEx(sprite_dica_p1,(Vector2){640, 160}, 0, 1, WHITE);//
        }

        if(InteracPerson(&info_personagem, &info_oil) == 2||InteracPerson(&info_personagem, &info_lamp) == 2){
            PlaySound(collect); 
        }

        DrawTextureEx(sprite_diario, (Vector2){info_dica_p1.position_x, info_dica_p1.position_y}, 0, 4, WHITE);
        if(LampCheck(&info_personagem) == 0){
            DrawRectangle(980 * 1.2, 460 * 1.2, 945 * 1.2, 445 * 1.2, BLACK);
        }
        //DrawRectangleRec(info_personagem.hitbox, BLUE);
        DrawTexturePro(sprite_personagem, frame_personagem, info_personagem.hitbox, (Vector2){info_personagem.hitbox.width - 13*size, info_personagem.hitbox.height - 21*size}, 0, WHITE);
        //DrawRectangleRec(info_baronesa.hitbox, RED);
        DrawTexturePro(sprite_baronesa, frame_baronesa, info_baronesa.hitbox, (Vector2){info_baronesa.hitbox.width - 15*size, info_baronesa.hitbox.height - 20*size}, 0, WHITE);
        DrawTextureEx(sprite_lamp, (Vector2){info_lamp.position_x, info_lamp.position_y}, 0, 5, WHITE);//
        DrawTextureEx(sprite_oil, (Vector2){info_oil.position_x, info_oil.position_y}, 0, 5, WHITE); //

        EndDrawing();
    }

    UnloadTexture(fundo_mapa1);

    UnloadTexture(sprite_personagem);
    UnloadTexture(sprite_baronesa);
    UnloadTexture(sprite_diario);

    UnloadTexture(sprite_lamp);
    UnloadTexture(sprite_lamp_fire);
    UnloadTexture(sprite_oil);

    UnloadMusicStream(musica_fase1);     
    UnloadMusicStream(musica_fase2);   
    UnloadMusicStream(musica);  
    UnloadSound(collect);
    CloseAudioDevice();     

    CloseWindow();
    return 0;
}
