// Copyright [2025] <Sofia Gazolla da Costa Silva>

/*
(1) o cálculo do menor valor:
Exemplo:
matriz de entrada:
[[10, 50, 30, 70, 20],
 [40, 80, 20, 10, 60]]
valor de saída: 10
*/
int minimo(int **mat, int M, int N) {
    int min = mat[0][0];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (mat[i][j] < min) {
                min = mat[i][j];
            }
        }
    }
    return min;
}

/*
(2) coordenada (linha e coluna) da primeira ocorrência do menor valor:
Exemplo:
matriz de entrada:
[[10, 50, 30, 70, 20],
 [40, 80, 20, 10, 60]]
coordenada de saída: [1, 3]
*/
struct coord {
    int x;  // linha
    int y;  // coluna
};
coord coordenada_menor(int **mat, int M, int N) {
    coord C;
    C.x = 0;
    C.y = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (mat[i][j] < mat[C.x][C.y]) {
                C.x = i;
                C.y = j;
            }
        }
    }
    return C;
}

/*
o cálculo de mínimo ponto-a-ponto entre duas matrizes mat1 e mat2 de mesmo tamanho MxN; a resposta consiste em atualização dos valores na própria mat1:
Exemplo:
matriz 1 original de entrada:
[[10, 50, 30, 70, 20],
 [40, 80, 20, 10, 60]]
matriz 2 original de entrada:
[[20, 30, 10, 50, 80],
 [30, 90, 10, 40, 50]]
matriz 1 após o processamento:
[[10, 30, 10, 50, 20],
 [30, 80, 10, 10, 50]]
*/
void minimo_matrizes(int **mat1, int **mat2, int M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (mat1[i][j] > mat2[i][j]) {
                mat1[i][j] = mat2[i][j];
            }
        }
    }
}

/*
(4) criação de um vetor para a obtenção da diagonal principal de uma matriz mat quadada NxN:
Exemplo:
matriz original:
[[10, 30, 10],
 [30, 80, 10],
 [70, 20, 30]]
vetor de saída: [10, 80, 30]
*/
int *diagonal(int **mat, int N) {
    int *d;
    d = new int[N];
    int j = 0;
    for (int i = 0; i < N; i++) {
        d[i] = mat[i][j];
        j++;
    }
    return d;
}

/*
(5) criação de um vetor para a obtenção da soma de cada coluna de uma matriz mat de dimensão MxN:
Exemplo:
matriz original:
[[10, 30, 10, 40],
 [30, 80, 10, 60],
 [70, 20, 30, 20]]
vetor de saída: [110, 130, 50, 120]
*/
int *soma_colunas(int **mat, int M, int N) {
    int *s;
    s = new int[N];
    for (int i = 0; i < N; i++) {
        s[i] = 0;
    }
    for (int i = 0; i < N; i++) {  // colunas
        for (int j = 0; j < M; j++) {  // linhas
            s[i] += mat[j][i];
        }
    }
    return s;
}


/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
