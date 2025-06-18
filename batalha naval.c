#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Função para validar se o navio cabe no tabuleiro
int valida_posicao(int linha, int coluna, char orientacao) {
    switch (orientacao) {
        case 'H': return coluna + TAM_NAVIO <= TAM_TABULEIRO;
        case 'V': return linha + TAM_NAVIO <= TAM_TABULEIRO;
        case 'D': return linha + TAM_NAVIO <= TAM_TABULEIRO && coluna + TAM_NAVIO <= TAM_TABULEIRO;
        case 'I': return linha + TAM_NAVIO <= TAM_TABULEIRO && coluna - TAM_NAVIO + 1 >= 0;
        default: return 0;
    }
}

// Verifica se as posições já estão ocupadas
int verifica_sobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int r = linha, c = coluna;
        switch (orientacao) {
            case 'H': c += i; break;
            case 'V': r += i; break;
            case 'D': r += i; c += i; break;
            case 'I': r += i; c -= i; break;
        }
        if (tabuleiro[r][c] != 0)
            return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posiciona_navio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int r = linha, c = coluna;
        switch (orientacao) {
            case 'H': c += i; break;
            case 'V': r += i; break;
            case 'D': r += i; c += i; break;
            case 'I': r += i; c -= i; break;
        }
        tabuleiro[r][c] = 3;
    }
}

// Cria matriz de habilidade CONE (forma triangular para baixo)
void cria_habilidade_cone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= (TAM_HABILIDADE - 1)/2 - i && j <= (TAM_HABILIDADE - 1)/2 + i)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade CRUZ
void cria_habilidade_cruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade OCTAEDRO (losango)
void cria_habilidade_octaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Aplica matriz de habilidade no tabuleiro, marcando 5 nas posições afetadas
void aplica_habilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origem_linha, int origem_coluna) {
    int offset = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int tab_l = origem_linha - offset + i;
            int tab_c = origem_coluna - offset + j;
            if (tab_l >= 0 && tab_l < TAM_TABULEIRO && tab_c >= 0 && tab_c < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[tab_l][tab_c] == 0) {
                    tabuleiro[tab_l][tab_c] = 5;
                }
            }
        }
    }
}

// Exibe o tabuleiro no console com caracteres diferentes
void exibe_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro Batalha Naval:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");      // água
            else if (tabuleiro[i][j] == 3) printf("N ");  // navio
            else if (tabuleiro[i][j] == 5) printf("* ");  // habilidade
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Navios
    int linhas[4] = {1, 5, 2, 0};
    int colunas[4] = {1, 8, 2, 8};
    char orientacoes[4] = {'H', 'V', 'D', 'I'};

    for (int i = 0; i < 4; i++) {
        if (valida_posicao(linhas[i], colunas[i], orientacoes[i]) &&
            verifica_sobreposicao(tabuleiro, linhas[i], colunas[i], orientacoes[i])) {
            posiciona_navio(tabuleiro, linhas[i], colunas[i], orientacoes[i]);
        } else {
            printf("Erro ao posicionar navio %d\n", i + 1);
            return 1;
        }
    }

    // Matrizes de habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    cria_habilidade_cone(cone);
    cria_habilidade_cruz(cruz);
    cria_habilidade_octaedro(octaedro);

    // Aplicação das habilidades com pontos de origem definidos
    aplica_habilidade(tabuleiro, cone, 2, 2);
    aplica_habilidade(tabuleiro, cruz, 5, 5);
    aplica_habilidade(tabuleiro, octaedro, 7, 2);

    // Exibir resultado final
    exibe_tabuleiro(tabuleiro);

    return 0;
}
