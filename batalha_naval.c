#include <stdio.h>
#include <stdbool.h>


#define TAMANHO_TABULEIRO 10
#define NUMERO_NAVIOS 3
#define AGUA 0
#define NAVIO 1
#define NAVIO_ACERTADO 2
#define TIRO_ERRADO 3


typedef struct {
    int x;
    int y;
    bool navio_afundado;
} Navio;

void inicializaTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}


void imprimeTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("======================\n");
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ ");
            } else if (tabuleiro[i][j] == 1) {
                printf("~ "); 
            } else if (tabuleiro[i][j] == 2) {
                printf("O "); 
            } else if (tabuleiro[i][j] == 3) {
                printf("X ");
            }
        }
        printf("\n");
    }
    printf("======================\n");
}

void colocaNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio *navio) {
    int x, y;
    printf("Posicione o navio (linha coluna): ");
    scanf("%d %d", &x, &y);
    
    if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO || tabuleiro[x][y] != 0) {
        printf("Posição inválida. Tente novamente.\n");
        colocaNavio(tabuleiro, navio);
    } else {
        navio->x = x;
        navio->y = y;
        tabuleiro[x][y] = 1;
    }
}


bool verificaAcerto(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio navios[], int x, int y) {
    for (int i = 0; i < NUMERO_NAVIOS; i++) {
        if (navios[i].x == x && navios[i].y == y && !navios[i].navio_afundado) {
            navios[i].navio_afundado = true;
            tabuleiro[x][y] = 2;
            return true;
        }
    }
    tabuleiro[x][y] = TIRO_ERRADO; 
    return false;
}


bool verificaNaviosAfundados(Navio navios[]) {
    for (int i = 0; i < NUMERO_NAVIOS; i++) {
        if (!navios[i].navio_afundado) {
            return false;
        }
    }
    return true;
}

int main() {
    int tabuleiroJogador1[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int tabuleiroJogador2[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Navio naviosJogador1[NUMERO_NAVIOS];
    Navio naviosJogador2[NUMERO_NAVIOS];
    
    inicializaTabuleiro(tabuleiroJogador1);
    inicializaTabuleiro(tabuleiroJogador2);
    
    imprimeTabuleiro(tabuleiroJogador1);
    printf("Jogador 1, posicione seus navios:\n");
    for (int i = 0; i < NUMERO_NAVIOS; i++) {
        colocaNavio(tabuleiroJogador1, &naviosJogador1[i]);
        imprimeTabuleiro(tabuleiroJogador1);
    }
    
    printf("Jogador 2, posicione seus navios:\n");
    for (int i = 0; i < NUMERO_NAVIOS; i++) {
        colocaNavio(tabuleiroJogador2, &naviosJogador2[i]);
        imprimeTabuleiro(tabuleiroJogador2);
    }
    
    int jogadorAtual = 1;
    
    while (true) {
        if (jogadorAtual == 1) {
            imprimeTabuleiro(tabuleiroJogador2);
            printf("======================\n");
            printf("Legenda: \n");
            printf("'~' = agua.\n'O' = navio atingido.\n'X' tiro errado.\n");
            printf("======================\n");
        } else {
            imprimeTabuleiro(tabuleiroJogador1);
            printf("======================\n");
            printf("Legenda: \n");
            printf("'~' = agua.\n'O' = navio atingido.\n'X' tiro errado.\n");
            printf("======================\n");
        }
        
        int x, y;
        printf("Escolha um lugar para atirar (linha coluna): ");
        scanf("%d %d", &x, &y);
        
        if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO) {
            printf("Coordenadas inválidas. Tente novamente.\n");
            continue;
        }
        
        if (jogadorAtual == 1) {
            if (verificaAcerto(tabuleiroJogador2, naviosJogador2, x, y)) {
                printf("Jogador 1 acertou um navio!\n");
                printf("======================\n");
                if (verificaNaviosAfundados(naviosJogador2)) {
                    printf("Jogador 1 venceu!\n");
                    printf("Todos os navios do jogador 2 foram afundados.\n");
                    break;
                }
            } else {
                printf("Jogador 1 errou o tiro.\n");
                printf("======================\n");
            }
        } else {
            if (verificaAcerto(tabuleiroJogador1, naviosJogador1, x, y)) {
                printf("Jogador 2 acertou um navio!\n");
                if (verificaNaviosAfundados(naviosJogador1)) {
                    printf("Jogador 2 venceu! Todos os navios do jogador 1 foram afundados.\n");
                    break;
                }
            } else {
                printf("Jogador 2 errou o tiro.\n");
            }
        }
        
        jogadorAtual = (jogadorAtual == 1) ? 2 : 1; 
    }
    
    return 0;
}
