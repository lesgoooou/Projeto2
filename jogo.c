#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define LINHAS 10
#define COLUNAS 20

void imprimirMatriz(char matriz[LINHAS][COLUNAS], int posX, int posY) {
    system("cls");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (i == posX && j == posY) {
                printf("^ ");  // jogador
            } else {
                printf(". ");  // espaço
            }
        }
        printf("\n");
    }
}

int main() {
    char matriz[LINHAS][COLUNAS] = {{0}};
    int posX = 8, posY = 9; // Posição inicial

    imprimirMatriz(matriz, posX, posY);

    while (1) {
        char tecla = _getch();  //importe do conio

        switch (tecla) {
            case 'w': //cima
                if (posX > 0) posX--;
                break;
            case 's': //baixo
                if (posX < LINHAS - 1) posX++;
                break;
            case 'a': //esquerda
                if (posY > 0) posY--;
                break;
            case 'd': //direita
                if (posY < COLUNAS - 1) posY++;
                break;
            case 'q': //sair
                return 0;
        }

        imprimirMatriz(matriz, posX, posY);
        Sleep(100); //pequeno atraso do windows
    }

    return 0;
}