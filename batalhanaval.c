#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO_TABULEIRO 10
#define NUM_NAVIOS 4

// Definição dos tipos de navio
typedef struct {
    int linha;
    int coluna;
    int tamanho;
    char direcao; // 'H' para horizontal, 'V' para vertical, 'D' para diagonal
    char simbolo;
} Navio;

// Protótipos das funções
void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool validarPosicaoNavio(Navio navio, char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void posicionarNavio(Navio navio, char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void criarMatrizCone(int matriz[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_origem, int coluna_origem);
void criarMatrizCruz(int matriz[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_origem, int coluna_origem);
void criarMatrizOctaedro(int matriz[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_origem, int coluna_origem);
void aplicarHabilidade(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      int matriz_habilidade[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      char simbolo);

int main() {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int matriz_habilidade[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Array de navios pré-definidos (conforme solicitado)
    Navio navios[NUM_NAVIOS] = {
        {2, 3, 3, 'H', 'A'}, // Navio horizontal de tamanho 3
        {5, 7, 2, 'V', 'B'}, // Navio vertical de tamanho 2
        {7, 1, 4, 'D', 'C'}, // Navio diagonal de tamanho 4
        {1, 8, 3, 'D', 'D'}  // Navio diagonal de tamanho 3
    };
    
    printf("=== SISTEMA DE BATALHA NAVAL COM HABILIDADES ESPECIAIS ===\n\n");
    
    // Inicialização do tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    printf("Posicionando navios no tabuleiro...\n");
    
    // Posicionamento e validação dos navios
    for (int i = 0; i < NUM_NAVIOS; i++) {
        printf("\nNavio %d: Tamanho %d, Direcao %c, Posicao (%d,%d)\n", 
               i + 1, navios[i].tamanho, navios[i].direcao, 
               navios[i].linha, navios[i].coluna);
        
        if (validarPosicaoNavio(navios[i], tabuleiro)) {
            posicionarNavio(navios[i], tabuleiro);
            printf("Navio posicionado com sucesso!\n");
        } else {
            printf("ERRO: Posicao invalida para o navio %d!\n", i + 1);
            return 1;
        }
    }
    
    // Exibir tabuleiro com navios
    printf("\n=== TABULEIRO COM NAVIOS POSICIONADOS ===\n");
    exibirTabuleiro(tabuleiro);
    
    // Demonstração das habilidades especiais
    printf("\n=== DEMONSTRACAO DAS HABILIDADES ESPECIAIS ===\n");
    
    // Habilidade CONE
    printf("\n1. HABILIDADE CONE (origem: 4,4)\n");
    criarMatrizCone(matriz_habilidade, 4, 4);
    aplicarHabilidade(tabuleiro, matriz_habilidade, '*');
    exibirTabuleiro(tabuleiro);
    
    // Reset do tabuleiro para próxima habilidade
    inicializarTabuleiro(tabuleiro);
    for (int i = 0; i < NUM_NAVIOS; i++) {
        posicionarNavio(navios[i], tabuleiro);
    }
    
    // Habilidade CRUZ
    printf("\n2. HABILIDADE CRUZ (origem: 5,5)\n");
    criarMatrizCruz(matriz_habilidade, 5, 5);
    aplicarHabilidade(tabuleiro, matriz_habilidade, '+');
    exibirTabuleiro(tabuleiro);
    
    // Reset do tabuleiro para próxima habilidade
    inicializarTabuleiro(tabuleiro);
    for (int i = 0; i < NUM_NAVIOS; i++) {
        posicionarNavio(navios[i], tabuleiro);
    }
    
    // Habilidade OCTAEDRO
    printf("\n3. HABILIDADE OCTAEDRO (origem: 3,6)\n");
    criarMatrizOctaedro(matriz_habilidade, 3, 6);
    aplicarHabilidade(tabuleiro, matriz_habilidade, 'O');
    exibirTabuleiro(tabuleiro);
    
    printf("\n=== LEGENDA ===\n");
    printf(". - Agua\n");
    printf("A,B,C,D - Navios\n");
    printf("* - Area afetada pelo Cone\n");
    printf("+ - Area afetada pela Cruz\n");
    printf("O - Area afetada pelo Octaedro\n");
    
    return 0;
}

/**
 * Inicializa o tabuleiro com água ('.')
 */
void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = '.';
        }
    }
}

/**
 * Exibe o tabuleiro no console
 */
void exibirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d", j);
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2c", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Valida se um navio pode ser posicionado no tabuleiro
 */
bool validarPosicaoNavio(Navio navio, char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Verifica se a posição inicial está dentro do tabuleiro
    if (navio.linha < 0 || navio.linha >= TAMANHO_TABULEIRO || 
        navio.coluna < 0 || navio.coluna >= TAMANHO_TABULEIRO) {
        return false;
    }
    
    // Verifica se o navio cabe no tabuleiro na direção especificada
    if (navio.direcao == 'H') { // Horizontal
        if (navio.coluna + navio.tamanho > TAMANHO_TABULEIRO) {
            return false;
        }
        // Verifica sobreposição
        for (int j = navio.coluna; j < navio.coluna + navio.tamanho; j++) {
            if (tabuleiro[navio.linha][j] != '.') {
                return false;
            }
        }
    } 
    else if (navio.direcao == 'V') { // Vertical
        if (navio.linha + navio.tamanho > TAMANHO_TABULEIRO) {
            return false;
        }
        // Verifica sobreposição
        for (int i = navio.linha; i < navio.linha + navio.tamanho; i++) {
            if (tabuleiro[i][navio.coluna] != '.') {
                return false;
            }
        }
    } 
    else if (navio.direcao == 'D') { // Diagonal (45 graus)
        if (navio.linha + navio.tamanho > TAMANHO_TABULEIRO || 
            navio.coluna + navio.tamanho > TAMANHO_TABULEIRO) {
            return false;
        }
        // Verifica sobreposição
        for (int k = 0; k < navio.tamanho; k++) {
            if (tabuleiro[navio.linha + k][navio.coluna + k] != '.') {
                return false;
            }
        }
    }
    
    return true;
}

/**
 * Posiciona um navio no tabuleiro
 */
void posicionarNavio(Navio navio, char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    if (navio.direcao == 'H') { // Horizontal
        for (int j = navio.coluna; j < navio.coluna + navio.tamanho; j++) {
            tabuleiro[navio.linha][j] = navio.simbolo;
        }
    } 
    else if (navio.direcao == 'V') { // Vertical
        for (int i = navio.linha; i < navio.linha + navio.tamanho; i++) {
            tabuleiro[i][navio.coluna] = navio.simbolo;
        }
    } 
    else if (navio.direcao == 'D') { // Diagonal
        for (int k = 0; k < navio.tamanho; k++) {
            tabuleiro[navio.linha + k][navio.coluna + k] = navio.simbolo;
        }
    }
}

/**
 * Cria matriz de efeito para habilidade CONE
 */
void criarMatrizCone(int matriz[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_origem, int coluna_origem) {
    // Inicializa matriz com 0 (não afetado)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            matriz[i][j] = 0;
        }
    }
    
    // Cria padrão de cone (triângulo apontando para baixo)
    for (int i = linha_origem; i < TAMANHO_TABULEIRO && i < linha_origem + 4; i++) {
        int largura = (i - linha_origem) * 2 + 1;
        int inicio = coluna_origem - (i - linha_origem);
        
        for (int j = inicio; j < inicio + largura && j < TAMANHO_TABULEIRO; j++) {
            if (j >= 0) {
                matriz[i][j] = 1;
            }
        }
    }
}

/**
 * Cria matriz de efeito para habilidade CRUZ
 */
void criarMatrizCruz(int matriz[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_origem, int coluna_origem) {
    // Inicializa matriz com 0 (não afetado)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            matriz[i][j] = 0;
        }
    }
    
    // Cria padrão de cruz (linha vertical e horizontal)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Linha vertical
        if (i >= linha_origem - 2 && i <= linha_origem + 2) {
            matriz[i][coluna_origem] = 1;
        }
        // Linha horizontal
        if (i >= coluna_origem - 2 && i <= coluna_origem + 2) {
            matriz[linha_origem][i] = 1;
        }
    }
}

/**
 * Cria matriz de efeito para habilidade OCTAEDRO
 */
void criarMatrizOctaedro(int matriz[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_origem, int coluna_origem) {
    // Inicializa matriz com 0 (não afetado)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            matriz[i][j] = 0;
        }
    }
    
    // Cria padrão octaedro (losango)
    int raio = 3;
    for (int i = linha_origem - raio; i <= linha_origem + raio; i++) {
        for (int j = coluna_origem - raio; j <= coluna_origem + raio; j++) {
            if (i >= 0 && i < TAMANHO_TABULEIRO && j >= 0 && j < TAMANHO_TABULEIRO) {
                int dist_vertical = abs(i - linha_origem);
                int dist_horizontal = abs(j - coluna_origem);
                
                // Forma de losango: dist_vertical + dist_horizontal <= raio
                if (dist_vertical + dist_horizontal <= raio) {
                    matriz[i][j] = 1;
                }
            }
        }
    }
}

/**
 * Aplica uma habilidade ao tabuleiro, marcando as áreas afetadas
 */
void aplicarHabilidade(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      int matriz_habilidade[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                      char simbolo) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (matriz_habilidade[i][j] == 1) {
                // Se a célula não contém um navio, marca com o símbolo da habilidade
                if (tabuleiro[i][j] == '.') {
                    tabuleiro[i][j] = simbolo;
                }
            }
        }
    }
}