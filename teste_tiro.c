#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <time.h>

#define LINHAS 8
#define COLUNAS 15
#define CHANCE_TIRO 40

int tiro_inimigo() {
    int num_aleatorio = rand() % 100;
    return num_aleatorio < CHANCE_TIRO;
}

void imprimirMatriz(char matriz[LINHAS][COLUNAS], int posX, int posY, int posINIx, int posINIy) {
    system("cls");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (i == posX && j == posY) {
                printf("W ");  // jogador
            } else if (i == posINIx && j == posINIy) {
                printf("& ");  // inimigo
                posINIy += 2;
            } else {
                printf("  ");  // espaço
            }
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "");

    char matriz[LINHAS][COLUNAS] = {{0}};
    int posX = 6, posY = 8; // Posição inicial do jogador
    int posINIx = 2, posINIy = 1; // Posição do inimigo

    imprimirMatriz(matriz, posX, posY, posINIx, posINIy);

    clock_t lastUpdate = clock(); // Para controle de tempo
    while (1) {
        if (_kbhit()) { // Verifica se uma tecla foi pressionada
            char tecla = _getch(); // Lê a tecla pressionada

            switch (tecla) {
                case 'a': // esquerda
                    if (posY > 0) posY--;
                    break;
                case 'd': // direita
                    if (posY < COLUNAS - 1) posY++;
                    break;
                case 'q': // sair
                    return 0;
            }
        }

        // Atualiza a matriz a cada 100 milissegundos
        if ((clock() - lastUpdate) * 1000 / CLOCKS_PER_SEC >= 1000) {
            lastUpdate = clock(); // Atualiza o tempo

            if (tiro_inimigo()) {
                printf("Inimigo atirou!\n");
                // Aqui você pode adicionar a lógica para criar e mover o tiro
            }

            imprimirMatriz(matriz, posX, posY, posINIx, posINIy);
        }
    }

    return 0;
}
