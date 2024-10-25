#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define LINHAS 8
#define COLUNAS 16

void imprimirMatriz(int posX, int posY, int posINIx, int posINIy, int tiroX, int tiroY) {
    system("cls");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (i == posX && j == posY) {
                printf("W ");  // jogador
            } else if (i == posINIx && j == posINIy) {
                printf("T ");  // inimigo
                posINIy += 2;
            } else if (i == tiroX && j == tiroY) {
                printf("| ");  // tiro
            } else {
                printf("  ");  // espaço vazio
            }
        }
        printf("\n");
    }
}

void tiro_personagem(int posX, int posY, int *tiroX, int *tiroY) {
    if (*tiroX == -1 && *tiroY == -1) {  // Inicializa o tiro
        *tiroX = posX - 1;
        *tiroY = posY;
    }
}

void abate()

int main() {
    int posX = 6, posY = 9; // Posição inicial do jogador
    int posINIx = 2, posINIy = 1; // Posição inicial do inimigo
    int tiroX = -1, tiroY = -1; // Posição inicial do tiro (fora da tela)

    imprimirMatriz(posX, posY, posINIx, posINIy, tiroX, tiroY);

    while (1) {
        char tecla = _getch();
        switch (tecla) {
            case 'a': // esquerda
                if (posY > 0) posY--;
                break;
            case 'd': // direita
                if (posY < COLUNAS - 1) posY++;
                break;
            case ' ': // tiro
                tiro_personagem(posX, posY, &tiroX, &tiroY);
                break;
            case 'q': // sair
                return 0;
        }

        // Atualiza a posição do tiro
        if (tiroX != -1) {
            tiroX--;
            if (tiroX < 0) {
                tiroX = -1;
                tiroY = -1;
            }
        }

        imprimirMatriz(posX, posY, posINIx, posINIy, tiroX, tiroY);
    }

    return 0;
}
