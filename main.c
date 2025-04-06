    #include <string.h>
    #include "raylib.h"
    #include "personagem.h"
    #include "personagem.c"
    #include "fantasma.c"
    #include "xadrez.c"
    #include "xadrez.h"
    #include "cavalo.c"
    #include "cavalo.h"


    int main(){
        const int Largura = 1920, Altura = 1080;
        InitWindow(Largura, Altura, "Prototipo");
        bool PodeAndar = 1;
        Texture sprite, sprite_barao, sprite_chess, sprite_cavalo;
        sprite_chess = LoadTexture("./chess.png");
        sprite = LoadTexture("./personagem.png");
        sprite_barao = LoadTexture("./barao.png");
        sprite_cavalo = LoadTexture("./cavalopreto.png");
        float posx = Largura/2, posy = Altura/2;    
        bool interagindo = 0;
        Personagem info_personagem;
        info_personagem = CreatePerson(posx, posy, sprite);

        Fantasma info_barao;
        info_barao = CreateGhost(0, 0, sprite_barao);

        Xadrez info_tabuleiro;
        info_tabuleiro = AbreTabuleiro(540,160, sprite_chess);

        Cavalo info_cavalo;
        info_cavalo = peca_cavalo(1075, 420, sprite_cavalo);

        while (!WindowShouldClose()){
            ModifyPerson(&info_personagem.position_x, &info_personagem.position_y, &info_personagem.colete, PodeAndar);
            MovementGhost(info_personagem.position_x, info_personagem.position_y, &info_barao.position_x, &info_barao.position_y);
            if (IsKeyDown(KEY_C)){
                AndaCavalo(&info_cavalo.position_x, &info_cavalo.position_y);}
            BeginDrawing();
            if ((info_personagem.position_x < 1320 && info_personagem.position_x > 1250) && (info_personagem.position_y < 340 && info_personagem.position_y > 260)) {
                DrawText("Aperte E para interagir", 200, 700, 40, BLACK);
                if (IsKeyPressed(KEY_E)) {  
                    interagindo = !interagindo; 
                }
                PodeAndar = !interagindo; 
            }
            if (interagindo){
                DrawTextureEx(sprite_chess,(Vector2){info_tabuleiro.position_x, info_tabuleiro.position_y}, 0, 1, WHITE);
                DrawTextureEx(sprite_cavalo,(Vector2){info_cavalo.position_x, info_cavalo.position_y}, 0, 0.75, WHITE);
                DrawRectangle(info_cavalo.position_x + 20, info_cavalo.position_y + 125, 2.0, 2.0, RED);//hitbox cavalo
                DrawRectangleLines(1005, 338, 60.0, 60.0, BROWN);//hitbox rei
                AndaCavalo(&info_cavalo.position_x, &info_cavalo.position_y);
                if ((info_cavalo.position_x + 20 < 1065 && info_cavalo.position_x + 20> 1005) && (info_cavalo.position_y + 125 < 410 && info_cavalo.position_y + 125 > 338)){
                    DrawText("colidiu", 200,900, 40, BLACK);
                }
            }
            DrawRectangle(1300, 300, 40.0, 40.0, BLACK);//posição xadrez
            ClearBackground(WHITE);
            DrawRectangle(info_personagem.position_x, info_personagem.position_y, info_personagem.desenho.width, info_personagem.desenho.height, BLUE);
            DrawTextureEx(sprite, (Vector2){info_personagem.position_x, info_personagem.position_y}, 0, 5, WHITE);
            DrawTextureEx(sprite_barao, (Vector2){info_barao.position_x, info_barao.position_y}, 0, 5, WHITE);
            EndDrawing();
        }
        CloseWindow();
        return 0;
    }