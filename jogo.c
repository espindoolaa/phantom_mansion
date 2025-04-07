#include <string.h>
#include "raylib.h"
#include "personagem.h"
#include "fantasma.h"
#include "item.h"
#define size 5
#define scale_up 1.2


int main(){
    const int Largura = 1920, Altura = 1080;

    InitWindow(Largura, Altura, "Phantom Mansion");
    InitAudioDevice(); // pode ter audio agora 

    bool PodeAndar = true;
    bool dica_na_tela = false;
    bool cofre_na_tela = false;
    bool xadrez_na_tela = false;
    int senha = 0;
    char cod[4];

    //area dos sprites
    Texture fundo_mapa1, sprite_personagem, sprite_baronesa, sprite_diario, sprite_lamp, sprite_lamp_fire, sprite_oil, sprite_dica_p1, sprite_chess, sprite_cavalo, sprite_xadrezinho;
    fundo_mapa1 = LoadTexture("./backgrounds/background1f.jpeg");

    sprite_chess = LoadTexture("./sprites/chess.png");
    sprite_personagem = LoadTexture("./sprites/spritesheet_personagem.png");
    sprite_baronesa = LoadTexture("./sprites/spritesheet_fantasma.png");
    sprite_diario = LoadTexture("./sprites/item.png");
    sprite_cavalo = LoadTexture("./sprites/cavalopreto.png");
    sprite_xadrezinho = LoadTexture("./sprites/chess-pixilart.gif");

    sprite_lamp = LoadTexture("./sprites/lamp.png");
    sprite_lamp_fire = LoadTexture("./sprites/light lamp.png");//
    sprite_oil = LoadTexture("./sprites/oil.png");
    sprite_dica_p1 = LoadTexture("./sprites/dicap1.png");

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
    //Item info_diario1 = CreateItem(1500, 900, sprite_diario,0);

    Item info_xadrez = CreateItem(600, 600,sprite_chess, 0); //tabuleiro do jogo
    Item info_cavalo = CreateItem(1075, 420, sprite_cavalo,0);
    Item xadrez_ojeto = CreateItem(1300, 300, sprite_xadrezinho, 0);

    Item info_lamp = CreateItem(1160 * scale_up, 20 * scale_up, sprite_lamp, 0);
    info_lamp.coletavel = true;
    Item info_oil = CreateItem(25 * scale_up, 800 * scale_up, sprite_oil, 1);
    info_oil.coletavel = true;

    Item info_cofre = CreateItem(145 * scale_up, 150 * scale_up, sprite_diario, 0);

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
    SetWindowSize(Largura, Altura);
    ToggleFullscreen();
    while (!fechar_jogo){
        fechar_jogo = (WindowShouldClose());
        HideCursor();


        //menu



        if(IsKeyPressed(KEY_SPACE)){//mudar quando entrar na fase 2
            musica = musica_fase2;
        }
        UpdateMusicStream(musica);

        //animacao do protagonista
        ModifyPerson(&info_personagem, &contador_frames, &frame_atual, &frame_personagem, PodeAndar);

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
        if(LampCheck(&info_personagem) == 0){
            DrawRectangle(980 * scale_up, 460 * scale_up, 945 * scale_up, 445 * scale_up, BLACK);
        }

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
        //interação com o xadrez
        if(InteracPerson(&info_personagem, &xadrez_ojeto) == 1){
            PodeAndar = !PodeAndar;
            xadrez_na_tela = !xadrez_na_tela;
        }

        // enquanto o puzzle do xadrez estiver ativo
        if(xadrez_na_tela){
            DrawTextureEx(sprite_chess, (Vector2){info_xadrez.position_x, info_xadrez.position_y}, 0, 1, WHITE);
            DrawTextureEx(sprite_cavalo, (Vector2){info_cavalo.position_x, info_cavalo.position_y}, 0, 0.75, WHITE);
            DrawRectangle(info_cavalo.position_x + 20, info_cavalo.position_y + 125, 2.0, 2.0, RED); //hitbox cavalo
            DrawRectangleLines(1005, 338, 60.0, 60.0, BROWN); //hitbox rei
            MoveItem(GetKeyPressed(), &info_cavalo);
            DrawRectangle(info_cavalo.position_x + 20, info_cavalo.position_y + 125, 2.0, 2.0, RED);

            if ((info_cavalo.position_x + 20 < 1065 && info_cavalo.position_x + 20> 1005) &&
                (info_cavalo.position_y + 125 < 410 && info_cavalo.position_y + 125 > 338)) {
                DrawText("colidiu", 200, 900, 40, BLACK);
            }
        }
        CofreCheck(cofre_na_tela, cod, &senha, &info_personagem);
        XadrezCheck(xadrez_na_tela, &info_personagem, &info_cavalo);
        DrawRectangleRec(info_personagem.hitbox, BLUE);
        DrawTexturePro(sprite_personagem, frame_personagem, info_personagem.hitbox, (Vector2){info_personagem.hitbox.width - 13*size, info_personagem.hitbox.height - 21*size}, 0, WHITE);
        DrawRectangleRec(info_baronesa.hitbox, RED);
        DrawTexturePro(sprite_baronesa, frame_baronesa, info_baronesa.hitbox, (Vector2){info_baronesa.hitbox.width - 15*size, info_baronesa.hitbox.height - 20*size}, 0, WHITE);
        DrawTextureEx(sprite_lamp, (Vector2){info_lamp.position_x, info_lamp.position_y}, 0, 5, WHITE);//
        DrawTextureEx(sprite_oil, (Vector2){info_oil.position_x, info_oil.position_y}, 0, 5, WHITE); //
        DrawRectangle(1300, 300, 40.0, 40.0, BLUE);//posição xadrez
        DrawTextureEx(sprite_xadrezinho, (Vector2){1300,300}, 0, 2, WHITE);
        
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
    UnloadSound(collect);
    CloseAudioDevice();     

    CloseWindow();
    return 0;
}