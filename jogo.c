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
     bool geladeira_na_tela = false; 
    int senha = 0;
    char cod[4];
    int muda_mapa = 0;
    int HasKey = 0;

    //area dos sprites
    Texture fundo_mapa1,fundo_mapa3, fundo_mapa, sprite_alicate, sprite_geladeira, quarto_liberado, quadro, sprite_personagem, sprite_baronesa, sprite_diario, sprite_lamp, sprite_lamp_fire, sprite_oil, sprite_dica_p1, sprite_chess, sprite_cavalo, sprite_xadrezinho;
    fundo_mapa1 = LoadTexture("./backgrounds/background1f.jpeg");
    fundo_mapa3 = LoadTexture("./backgrounds/background3.jpeg");
    fundo_mapa = LoadTexture("./backgrounds/cozinha.png");
    sprite_chess = LoadTexture("./sprites/chess.png");
    sprite_personagem = LoadTexture("./sprites/spritesheet_personagem.png");
    sprite_baronesa = LoadTexture("./sprites/spritesheet_fantasma.png");
    sprite_diario = LoadTexture("./sprites/item.png");
    sprite_cavalo = LoadTexture("./sprites/cavalopreto.png");
    sprite_xadrezinho = LoadTexture("./sprites/chess-pixilart.gif");

    quadro = LoadTexture("./sprites/quadro_barao.png");
    quarto_liberado = LoadTexture("./backgrounds/quarto_liberado.jpg");

    sprite_lamp = LoadTexture("./sprites/lamp.png");
    sprite_lamp_fire = LoadTexture("./sprites/light lamp.png");//
    sprite_oil = LoadTexture("./sprites/oil.png");
    sprite_dica_p1 = LoadTexture("./sprites/dicap1.png");
    sprite_alicate = LoadTexture("./sprites/alicate.png");
    sprite_geladeira = LoadTexture("./sprites/fridge_puzzle.png");

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

    Item info_xadrez = CreateItem(600, 200,sprite_chess, 0); //tabuleiro do jogo
    Item info_cavalo = CreateItem(1030, 400, sprite_cavalo,0);
    Item xadrez_ojeto = CreateItem(350, 90, sprite_xadrezinho, 0);

    Item info_quadro = CreateItem(1446, 572, quadro, 0);

    Item info_lamp = CreateItem(1160, 20 * scale_up, sprite_lamp, 0);
    info_lamp.coletavel = true;
    Item info_oil = CreateItem(25 * scale_up, 800 * scale_up, sprite_oil, 1);
    info_oil.coletavel = true;

    // Alicate 
    Item info_alicate = CreateItem(1500, 193, sprite_alicate, 1);
    info_alicate.coletavel = true;

    // Geladeira 
    Item info_geladeira = CreateItem(810, 200, sprite_diario, 0);

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


        switch(muda_mapa){
            case 0:
                DrawTextureEx(fundo_mapa1, (Vector2){0,0}, 0, scale_up, WHITE);
            break;
            case 1:
                DrawTextureEx(fundo_mapa, (Vector2){0,0}, 0, 1, WHITE);
                break;
            case 2:
                DrawTextureEx(fundo_mapa3, (Vector2){0,0}, 0, scale_up, WHITE);
                DrawTextureEx(quadro, (Vector2){1446,572}, 0, 0.18, WHITE);
            break;
            case 3:
                DrawTextureEx(quarto_liberado, (Vector2){0,0}, 0, scale_up, WHITE);
                DrawTextureEx(quadro, (Vector2){1600,572}, 0, 0.18, WHITE);
                
        }
        if (IsKeyPressed(KEY_M)){
            if (muda_mapa < 3)
                muda_mapa++;
            else
                muda_mapa = 0;

        }
        

        //retangulo preto no escritorio
        if (muda_mapa == 0){
            DrawTextureEx(sprite_lamp, (Vector2){info_lamp.position_x, info_lamp.position_y}, 0, 5, WHITE);//
            DrawTextureEx(sprite_oil, (Vector2){info_oil.position_x, info_oil.position_y}, 0, 5, WHITE); //
            DrawTextureEx(sprite_diario, (Vector2){info_dica_p1.position_x, info_dica_p1.position_y}, 0, 4, WHITE);
            if(LampCheck(&info_personagem) == 0 && muda_mapa == 0){
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
        }
        if (muda_mapa == 1){
        //Interação com a geladeira 
        if(InteracPerson(&info_personagem, &info_geladeira) == 1){
            geladeira_na_tela = !geladeira_na_tela; 
            PodeAndar = !geladeira_na_tela; 
        }}
        if (muda_mapa == 2 || muda_mapa == 3){
        //interação com o xadrez
        if(IsKeyPressed(KEY_C))
            muda_mapa = 3;
            DrawRectangle(350, 90, 80.0, 80.0, BLUE);//posição xadrez
            DrawTextureEx(sprite_xadrezinho, (Vector2){350,90}, 0, 4, WHITE);
            if(InteracPerson(&info_personagem, &xadrez_ojeto) == 1){
                PodeAndar = !PodeAndar;
                xadrez_na_tela = !xadrez_na_tela;
            }

            // enquanto o puzzle do xadrez estiver ativo
            if(xadrez_na_tela){
                Rectangle rei  = {970, 350, 20, 20};
                Rectangle cavalo = {info_cavalo.position_x+10, info_cavalo.position_y +90, 50.0, 50.0};
                DrawTextureEx(sprite_chess, (Vector2){info_xadrez.position_x, info_xadrez.position_y}, 0, 0.8, WHITE);
                DrawTextureEx(sprite_cavalo, (Vector2){info_cavalo.position_x, info_cavalo.position_y}, 0, 0.6, WHITE);
                MoveItem(GetKeyPressed(), &info_cavalo);
                if (CheckCollisionRecs(cavalo, rei) == true) {
                    DrawText("colidiu", 200, 900, 100, GREEN);
                }
            }
        }
        CofreCheck(cofre_na_tela, cod, &senha, &info_personagem);
        XadrezCheck(xadrez_na_tela, &info_personagem, &info_cavalo);
        DrawRectangleRec(info_personagem.hitbox, BLUE);
        DrawTexturePro(sprite_personagem, frame_personagem, info_personagem.hitbox, (Vector2){info_personagem.hitbox.width - 13*size, info_personagem.hitbox.height - 21*size}, 0, WHITE);
        
        // Desenho da geladeira acima do personagem principal 
        if(geladeira_na_tela){
            DrawTextureEx(sprite_geladeira,(Vector2){400, 40}, 0, 1, WHITE);//
        }
        
        DrawRectangleRec(info_baronesa.hitbox, RED);
        DrawTexturePro(sprite_baronesa, frame_baronesa, info_baronesa.hitbox, (Vector2){info_baronesa.hitbox.width - 15*size, info_baronesa.hitbox.height - 20*size}, 0, WHITE);
        
        
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