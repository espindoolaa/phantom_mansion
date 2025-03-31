#include <string.h>
#include "raylib.h"
#include "personagem.h"
#include "personagem.c"
#include "fantasma.c"
#include "item.c"


int main(){
    const int Largura = 1920, Altura = 1080;
    InitWindow(Largura, Altura, "Phantom Mansion");

    Texture fundo_mapa1, sprite_personagem, sprite_baronesa, sprite_diario;
    fundo_mapa1 = LoadTexture("./backgrounds/mapa1.jpg");
    sprite_personagem = LoadTexture("./sprites/spritesheet_personagem.png");
    sprite_baronesa = LoadTexture("./sprites/spritesheet_fantasma.png");
    sprite_diario = LoadTexture("./item.png");

    Personagem info_personagem;
    info_personagem = CreatePerson(Largura/2 - 30, 900, sprite_personagem);

    Fantasma info_baronesa;
    info_baronesa = CreateGhost(1940, 900, sprite_baronesa);

    Item info_diario;
    info_diario = CreateItem(1500, 900, sprite_diario);

    int contador_frames = 0;
    int frame_atual = 0;

    bool fechar_jogo = false;
    SetTargetFPS(120);
    SetWindowSize(Largura, Altura);
    ToggleFullscreen();
    while (!fechar_jogo){
        fechar_jogo = (WindowShouldClose());
        ModifyPerson(&info_personagem, &contador_frames, &frame_atual);
        InteracPerson(&info_personagem, &info_diario);
        if (info_personagem.itens[0] == 'd'){
            MovementGhost(info_personagem.position_x, info_personagem.position_y, &info_baronesa, frame_atual);
            if(CheckCollisionRecs(info_personagem.hitbox, info_baronesa.hitbox) == true){fechar_jogo = true;}
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureEx(fundo_mapa1, (Vector2){0,0}, 0, 1.2, WHITE);
        DrawTextureEx(sprite_diario, (Vector2){info_diario.position_x, info_diario.position_y}, 0, 4, WHITE);
        //DrawRectangleRec(info_personagem.hitbox, BLUE);
        DrawTexturePro(sprite_personagem, info_personagem.frame, info_personagem.hitbox, (Vector2){info_personagem.hitbox.width - 13*size, info_personagem.hitbox.height - 21*size}, 0, WHITE);
        //DrawRectangleRec(info_baronesa.hitbox, RED);
        DrawTexturePro(sprite_baronesa, info_baronesa.frame, info_baronesa.hitbox, (Vector2){info_baronesa.hitbox.width - 15*size, info_baronesa.hitbox.height - 20*size}, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(sprite_personagem);
    UnloadTexture(sprite_baronesa);
    UnloadTexture(sprite_diario);
    CloseWindow();
    return 0;
}