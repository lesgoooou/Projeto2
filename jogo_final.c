#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define LINHAS 10
#define COLUNAS 12
#define CHANCE_TIRO_INIMIGO 25 
#define TEMPO_ATIRO_INIMIGO 2000 

typedef struct {
    int x, y;
} Ponto;

typedef struct {
    Ponto posicao;
    DWORD ultimoTiro; 
} Inimigo;

typedef struct {
    Ponto jogador;
    Inimigo inimigos[LINHAS][COLUNAS];
    Ponto tiro;
    bool tiroAtivo;
    char tirosInimigos[LINHAS][COLUNAS];
    int pontuacao;
    int vida;
    int inimigosRestantes;
} Estado;

void inicializarInimigos(Estado *estado) {
    int contadorInimigos = 0;
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            estado->inimigos[i][j].posicao.x = -1;
            estado->inimigos[i][j].posicao.y = -1;
            estado->inimigos[i][j].ultimoTiro = 0;
            if ((i == 2) && (j % 2 == 1)) { 
                estado->inimigos[i][j].posicao.x = i;
                estado->inimigos[i][j].posicao.y = j;
                contadorInimigos++;
            }
        }
    }
    estado->inimigosRestantes = contadorInimigos; 
}

void imprimirMatriz(Estado *estado) {
    system("cls");
    printf("Pontuacao: %d\n", estado->pontuacao);
    printf("Vida: %d\n", estado->vida);
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (i == estado->jogador.x && j == estado->jogador.y) {
                printf("W ");  // jogador
            } else if (estado->inimigos[i][j].posicao.x != -1) {
                printf("T ");  // inimigo
            } else if (estado->tirosInimigos[i][j] == '*') {
                printf("o ");  // tiro inimigo
            } else if (i == estado->tiro.x && j == estado->tiro.y) {
                printf("| ");  // tiro jogador
            } else {
                printf("  "); 
            }
        }
        printf("\n");
    }
}

DWORD WINAPI moverTiro(LPVOID lpParam) {
    Estado *estado = (Estado*)lpParam;
    while (1) {
        if (estado->tiroAtivo) {
            Sleep(150);  
            estado->tiro.x--;

            // Verifica colisão com os inimigos
            if (estado->tiro.x >= 0 && estado->tiro.x < LINHAS && estado->tiro.y >= 0 && estado->tiro.y < COLUNAS && 
                estado->inimigos[estado->tiro.x][estado->tiro.y].posicao.x != -1) { 
                estado->inimigos[estado->tiro.x][estado->tiro.y].posicao.x = -1;
                estado->inimigos[estado->tiro.x][estado->tiro.y].posicao.y = -1;
                estado->pontuacao++; 
                estado->inimigosRestantes--;
                estado->tiro.x = -1;
                estado->tiro.y = -1;
                estado->tiroAtivo = false;
            }
            
            if (estado->tiro.x < 0) {
                estado->tiro.x = -1;
                estado->tiro.y = -1;
                estado->tiroAtivo = false;
            }
            imprimirMatriz(estado);
        }
    }
    return 0;
}

void tiro_personagem(Estado *estado) {
    if (!estado->tiroAtivo) {
        estado->tiro.x = estado->jogador.x - 1;
        estado->tiro.y = estado->jogador.y;
        estado->tiroAtivo = true;
    }
}

void atualizarTirosInimigos(Estado *estado) {
    for (int i = LINHAS - 2; i >= 0; i--) {
        for (int j = 0; j < COLUNAS; j++) {
            if (estado->tirosInimigos[i][j] == '*') {
                estado->tirosInimigos[i][j] = ' ';
                if (i + 1 < LINHAS) {
                    estado->tirosInimigos[i + 1][j] = '*';
                }
            }
        }
    }
    for (int j = 0; j < COLUNAS; j++) {
        estado->tirosInimigos[LINHAS - 1][j] = ' ';
    }
}

void atirarInimigos(Estado *estado) {
    DWORD tempoAtual = GetTickCount();
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (estado->inimigos[i][j].posicao.x != -1) {
                if (tempoAtual - estado->inimigos[i][j].ultimoTiro >= TEMPO_ATIRO_INIMIGO && (rand() % 100 < CHANCE_TIRO_INIMIGO)) {
                    if (i + 1 < LINHAS) {
                        estado->tirosInimigos[i + 1][j] = '*';
                        estado->inimigos[i][j].ultimoTiro = tempoAtual;
                    }
                }
            }
        }
    }
}

bool verificarColisao(int posX, int posY, Estado *estado) {
    if (estado->tirosInimigos[posX][posY] == '*') {
        estado->tirosInimigos[posX][posY] = ' ';
        return true;
    }
    return false;
}

int main(void) {
    Estado estado = {
        .jogador = {7, 6},
        .tiro = {-1, -1},
        .tiroAtivo = false,
        .pontuacao = 0,
        .vida = 3
    };

    memset(estado.tirosInimigos, ' ', sizeof(estado.tirosInimigos));
    inicializarInimigos(&estado);

    HANDLE hThread = CreateThread(NULL, 0, moverTiro, &estado, 0, NULL);

    imprimirMatriz(&estado);

    while (estado.vida > 0) {
        if (estado.inimigosRestantes == 0) { 
            printf("Parabens! Voce derrotou todos os inimigos.\n");
            break;
        }

        if (_kbhit()) {
            char tecla = _getch();
            switch (tecla) {
                case 'a':
                    if (estado.jogador.y > 0) estado.jogador.y--;
                    break;
                case 'd':
                    if (estado.jogador.y < COLUNAS - 1) estado.jogador.y++;
                    break;
                case ' ':
                    tiro_personagem(&estado);
                    break;
                case 'q':
                    return 0;
            }
            imprimirMatriz(&estado);
        }

        atirarInimigos(&estado);
        atualizarTirosInimigos(&estado);

        if (verificarColisao(estado.jogador.x, estado.jogador.y, &estado)) {
            estado.vida--;
            if (estado.vida > 0) {
                printf("\nVoce foi atingido! Vidas restantes: %d\n", estado.vida);
                Sleep(1000);
            }
        }

        imprimirMatriz(&estado);
        Sleep(150); 
    }

    if (estado.vida <= 0) {
        printf("Game Over! Voce perdeu todas as suas vidas.\n");
    }
    
    return 0;
}
