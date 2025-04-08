#include <string.h>
#include "raylib.h"
#include "personagem.h"
#include "personagem.c"
#include "fantasma.c"
#include "item.c"


int main(){
    const int Largura = 1920, Altura = 1080;

    InitWindow(Largura, Altura, "Phantom Mansion");
    InitAudioDevice(); // pode ter audio agora 

    bool PodeAndar = true;
    bool dica_na_tela = false;
    bool cofre_na_tela = false;
    bool geladeira_na_tela = false;
    bool portao_cozinha_na_tela = false;  

    int senha = 0;
    char cod[4];

    // senha portão 
    int senha_portao = 0;
    char cod_portao[4];

    // area dos sprites
    Texture fundo_mapa, sprite_personagem, sprite_alicate, sprite_baronesa, sprite_diario, sprite_lamp, sprite_lamp_fire, sprite_oil, sprite_dica_p1, sprite_geladeira;
    fundo_mapa = LoadTexture("./backgrounds/cozinha.png");

    sprite_personagem = LoadTexture("./sprites/spritesheet_personagem.png");
    sprite_baronesa = LoadTexture("./sprites/spritesheet_fantasma.png");
    sprite_diario = LoadTexture("./sprites/item.png");

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
    //Item info_diario1 = CreateItem(1500, 900, sprite_diario);

    Item info_lamp = CreateItem(1160 , 20 * scale_up, sprite_lamp, 0);
    info_lamp.coletavel = true;
    Item info_oil = CreateItem(25 * scale_up, 800 * scale_up, sprite_oil, 1);
    info_oil.coletavel = true;

    // Alicate 
    Item info_alicate = CreateItem(1500, 193, sprite_alicate, 1);
    info_alicate.coletavel = true;
    
    // Cofre
    Item info_cofre = CreateItem(145 * scale_up, 150 * scale_up, sprite_diario, 0);

    // Portão Cozinha
    Item info_portao_cozinha = CreateItem(1300, 750, sprite_diario, 0);

    // Geladeira 
    Item info_geladeira = CreateItem(810, 200, sprite_diario, 0);

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
        
        DrawTextureEx(fundo_mapa, (Vector2){0,0}, 0, 1, WHITE);
        
        //Interação com a geladeira 
        if(InteracPerson(&info_personagem, &info_geladeira) == 1){
            geladeira_na_tela = !geladeira_na_tela; 
            PodeAndar = !geladeira_na_tela; 
        }
        
        //efeito sonoro de coletar
        if(InteracPerson(&info_personagem, &info_oil) == 2 || InteracPerson(&info_personagem, &info_lamp) == 2){
            PlaySound(collect); 
        }

        // efeito sonoro ao coletar o alicate
        if (InteracPerson(&info_personagem, &info_alicate) == 2) {
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

         //interacao com o portão
        if(InteracPerson(&info_personagem, &info_portao_cozinha) == 1){
            PodeAndar = !PodeAndar;
            portao_cozinha_na_tela = !portao_cozinha_na_tela;
            if(senha == 3 && strcmp(cod, "CIN") != 0){
                senha = 0;
                cod[senha] = '\0';
            }
        }
        
        if (cofre_na_tela){
           CofreCheck(cofre_na_tela, cod, &senha, &info_personagem);
        }
        
        if (portao_cozinha_na_tela){
            PortaoCheck(portao_cozinha_na_tela, cod, &senha, &info_personagem);
        }
 
       
    
        DrawRectangleRec(info_personagem.hitbox, BLUE);
        DrawTexturePro(sprite_personagem, frame_personagem, info_personagem.hitbox, (Vector2){info_personagem.hitbox.width - 13*size, info_personagem.hitbox.height - 21*size}, 0, WHITE);
        
        // Desenho da geladeira acima do personagem principal 
        if(geladeira_na_tela){
            DrawTextureEx(sprite_geladeira,(Vector2){400, 40}, 0, 1, WHITE);//
        }
        
        //DrawRectangleRec(info_baronesa.hitbox, RED);
        DrawTexturePro(sprite_baronesa, frame_baronesa, info_baronesa.hitbox, (Vector2){info_baronesa.hitbox.width - 15*size, info_baronesa.hitbox.height - 20*size}, 0,WHITE);
        DrawTextureEx(sprite_lamp, (Vector2){info_lamp.position_x, info_lamp.position_y}, 0, 5, WHITE);//
        DrawTextureEx(sprite_alicate, (Vector2){info_alicate.position_x, info_alicate.position_y}, 0, 1.8, WHITE);//
        DrawTextureEx(sprite_oil, (Vector2){info_oil.position_x, info_oil.position_y}, 0, 5, WHITE); //
        
        EndDrawing();
    }

    UnloadTexture(fundo_mapa);

    UnloadTexture(sprite_personagem);
    UnloadTexture(sprite_baronesa);
    UnloadTexture(sprite_diario);

    UnloadTexture(sprite_lamp);
    UnloadTexture(sprite_lamp_fire);
    UnloadTexture(sprite_oil);
    UnloadTexture(sprite_alicate);

    UnloadMusicStream(musica_fase1);     
    UnloadMusicStream(musica_fase2);   
    UnloadSound(collect);
    CloseAudioDevice();     

    CloseWindow();
    return 0;
}