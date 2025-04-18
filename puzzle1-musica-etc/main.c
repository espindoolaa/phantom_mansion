#include <string.h>
#include "raylib.h"
#include "personagem.h"
#include "personagem.c"
#include "fantasma.c"
#include "item.c"


int main(){
    const int Largura = 1920, Altura = 1080;
    InitWindow(Largura, Altura, "Phantom Mansion");

    Texture sprite_personagem, sprite_baronesa, sprite_diario;
    sprite_personagem = LoadTexture("./sprites/spritesheet_personagem.png");
    sprite_baronesa = LoadTexture("./sprites/spritesheet_fantasma.png");
    sprite_diario = LoadTexture("./item.png");
    float posx = Largura/2, posy = Altura/2;

    Personagem info_personagem;
    info_personagem = CreatePerson(posx, posy, sprite_personagem);
    Rectangle frame_personagem = (Rectangle){0, 63,39 ,84};
    Rectangle destino_personagem = (Rectangle){info_personagem.position_x, info_personagem.position_y, frame_personagem.width, frame_personagem.height};

    Fantasma info_baronesa;
    info_baronesa = CreateGhost(0, 0, sprite_baronesa);
    Rectangle frame_baronesa = (Rectangle){0, 0, 15, 20};
    Rectangle destino_baronesa = (Rectangle){info_baronesa.position_x, info_baronesa.position_y, frame_baronesa.width, frame_baronesa.height};

    Item info_diario;
    info_diario = CreateItem(1800, 10, sprite_diario);

    int contador_frames = 0;
    int frame_atual = 0;
    while (!WindowShouldClose()){
        ModifyPerson(&info_personagem.position_x, &info_personagem.position_y, &contador_frames, &frame_atual, &frame_personagem, &destino_personagem);
        MovementGhost(info_personagem.position_x, info_personagem.position_y, &info_baronesa.position_x, &info_baronesa.position_y, frame_atual, &frame_baronesa, &destino_baronesa);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureEx(sprite_diario, (Vector2){info_diario.position_x, info_diario.position_y}, 0, 5, WHITE);
        DrawTexturePro(sprite_personagem, frame_personagem, destino_personagem, (Vector2){destino_personagem.width - 14*size, destino_personagem.height - 21*size}, 0, WHITE);
        DrawTexturePro(sprite_baronesa, frame_baronesa, destino_baronesa, (Vector2){destino_baronesa.width - 15*size, destino_baronesa.height - 20*size}, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(sprite_personagem);
    UnloadTexture(sprite_baronesa);
    UnloadTexture(sprite_diario);
    CloseWindow();
    return 0;
}