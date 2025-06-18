#include <stdio.h>

// ---------------------
// Função recursiva: Movimento da Torre (Direita)
// ---------------------
void moverTorre(int casas) {
    if (casas <= 0) return;
    printf("Direita\n");
    moverTorre(casas - 1);
}

// ---------------------
// Função recursiva: Movimento do Bispo (Diagonal: Cima Direita)
// Também implementa loops aninhados para fins didáticos
// ---------------------
void moverBispoRecursivo(int casas) {
    if (casas <= 0) return;
    printf("Cima Direita\n");
    moverBispoRecursivo(casas - 1);
}

void moverBispoComLoops(int linhas, int colunas) {
    printf("Movimento do Bispo com Loops Aninhados:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (i == j) {  // Movimento diagonal: só imprime se linha == coluna
                printf("Cima Direita\n");
            }
        }
    }
}

// ---------------------
// Função recursiva: Movimento da Rainha (Esquerda)
// ---------------------
void moverRainha(int casas) {
    if (casas <= 0) return;
    printf("Esquerda\n");
    moverRainha(casas - 1);
}

// ---------------------
// Movimento do Cavalo: em "L" (2 para cima, 1 para a direita)
// Utiliza loops aninhados e controle com continue/break
// ---------------------
void moverCavalo() {
    printf("Movimento do Cavalo:\n");
    for (int i = 0; i < 3; i++) { // Representa tentativas de movimento vertical
        for (int j = 0; j < 3; j++) { // Representa tentativas de movimento horizontal
            if (i == 2 && j == 1) {
                printf("Cima\n");
                printf("Cima\n");
                printf("Direita\n");
                break;  // Movimento em "L" realizado
            } else {
                continue; // Ignora combinações inválidas
            }
        }
    }
}

int main() {
    // ---------------------
    // Torre
    // ---------------------
    int casasTorre = 5;
    printf("Movimento da Torre:\n");
    moverTorre(casasTorre);

    // ---------------------
    // Bispo (Recursivo)
    // ---------------------
    int casasBispo = 5;
    printf("\nMovimento do Bispo (Recursivo):\n");
    moverBispoRecursivo(casasBispo);

    // ---------------------
    // Bispo (Loops Aninhados)
    // ---------------------
    printf("\n");
    moverBispoComLoops(5, 5);

    // ---------------------
    // Rainha
    // ---------------------
    int casasRainha = 8;
    printf("\nMovimento da Rainha:\n");
    moverRainha(casasRainha);

    // ---------------------
    // Cavalo
    // ---------------------
    printf("\n");
    moverCavalo();

    return 0;
}
