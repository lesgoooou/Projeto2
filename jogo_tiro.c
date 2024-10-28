#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
// #include <locale.h>

#define LINHAS 10
#define COLUNAS 12

typedef struct {
    int x, y;
} Ponto;

typedef struct {
    Ponto jogador;
    Ponto inimigos[LINHAS][COLUNAS];
    Ponto tiro;
    bool tiroAtivo;
    int pontuacao;
    int vida;
} Estado;

void inicializarInimigos(Estado *estado) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            estado->inimigos[i][j].x = -1;
            estado->inimigos[i][j].y = -1;
            if ((i == 2) && (j % 2 == 1)) { // Coloca inimigos em posições ímpares
                estado->inimigos[i][j].x = i;
                estado->inimigos[i][j].y = j;
            }
        }
    }
}

void imprimirMatriz(Estado *estado) {
    system("cls");
    printf("Pontuacao: %d\n", estado->pontuacao); // Imprime a pontuação
    printf("Vida: %d\n", estado->vida); // Vida
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (i == estado->jogador.x && j == estado->jogador.y) {
                printf("W ");  // jogador
            } else if (estado->inimigos[i][j].x != -1 && estado->inimigos[i][j].y != -1) {
                printf("T ");  // inimigo
            } else if (i == estado->tiro.x && j == estado->tiro.y) {
                printf("| ");  // tiro
            } else {
                printf("  ");  // espaço vazio
            }
        }
        printf("\n");
    }
}

DWORD WINAPI moverTiro(LPVOID lpParam) {
    Estado *estado = (Estado*)lpParam;
    while (1) {
        if (estado->tiroAtivo) {
            Sleep(100);
            estado->tiro.x--;
            
            // Verifica colisão com os inimigos
            if (estado->tiro.x >= 0 && estado->tiro.x < LINHAS && estado->tiro.y >= 0 && estado->tiro.y < COLUNAS && // Verifica se o tiro está dentro da matriz
                estado->inimigos[estado->tiro.x][estado->tiro.y].x != -1 && estado->inimigos[estado->tiro.x][estado->tiro.y].y != -1 )// Verifica se o inimigo está ativo 
                { 
                estado->inimigos[estado->tiro.x][estado->tiro.y].x = -1;
                estado->inimigos[estado->tiro.x][estado->tiro.y].y = -1;
                estado->pontuacao++; // Incrementa a pontuação
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
    if (!estado->tiroAtivo) {  // Inicializa o tiro
        estado->tiro.x = estado->jogador.x - 1;
        estado->tiro.y = estado->jogador.y;
        estado->tiroAtivo = true;
    }
}

int main(void) {
    Estado estado = {
        .jogador = {7, 6},
        .tiro = {-1, -1},
        .tiroAtivo = false,
        .pontuacao = 0,
        .vida = 3
    };

    // setlocale(LC_ALL, "en_US.UTF-8");
    inicializarInimigos(&estado);

    HANDLE hThread = CreateThread(NULL, 0, moverTiro, &estado, 0, NULL);

    imprimirMatriz(&estado);

    while (1) {
        char tecla = _getch();
        switch (tecla) {
            case 'a': // esquerda
                if (estado.jogador.y > 0) estado.jogador.y--;
                break;
            case 'd': // direita
                if (estado.jogador.y < COLUNAS - 1) estado.jogador.y++;
                break;
            case ' ': // tiro
                tiro_personagem(&estado);
                break;
            case 'q': // sair
                return 0;
        }
        imprimirMatriz(&estado);
    }

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    return 0;
}
