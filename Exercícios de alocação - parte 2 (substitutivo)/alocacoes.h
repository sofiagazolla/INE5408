// Copyright [2025] <Sofia Gazolla da Costa Silva>
#include <string>


class Aluno {
 public:
    Aluno() {}  // construtor
    ~Aluno() {}  // destrutor
    std::string devolveNome() {
        return nome;
    }
    int devolveMatricula() {
        return matricula;
    }
    void escreveNome(std::string nome_) {
        nome = nome_;
    }
    void escreveMatricula(int matricula_) {
        matricula = matricula_;
    }
 private:
    std::string nome;
    int matricula;
};


Aluno *turma_filtra(Aluno t[], int N, int menor_matr) {
    Aluno *tf;
    tf = nullptr;
    int total_menor = 0;
    
    for (int i = 0; i < N; i++) {
        int matricula = t[i].devolveMatricula();
        if (matricula >= menor_matr) {
            total_menor++;
        }
    }
    
    tf = new Aluno[total_menor];
    int j = 0;
    
    for (int i = 0; i < N; i++) {
        int matricula = t[i].devolveMatricula();
        if (matricula >= menor_matr) {
            tf[j] = t[i];
            j++;
        }
    }
    
    return tf;
}

int *turma_conta(Aluno t[], int N) {
    int *c;
    c = new int[26]();

    for (int i = 0; i < N; i++) {
        char nome;
        nome = t[i].devolveNome()[0];
        if (nome >= 'A' && nome <= 'Z'){
            int posicao = nome - 'A';
            c[posicao] ++;
        }
    }

    return c;
}


Aluno **grupos_por_iniciais(Aluno t[], int N) {
    Aluno **g;
    g = new Aluno*[26];  // vetor de ponteiros;
                         // cada posição aponta para um vetor de alunos;
                         // g deve ser alocado com o seguinte:
                         //   g[0] é um ponteiro para alunos com letra 'A'
                         //   g[1] é um ponteiro para alunos com letra 'B'
                         //   ...
                         //   g[25] é um ponteiro para alunos com letra 'Z'

    // DICA: utilize a função 'turma_conta' (implementada no execício 5) para
    //       definir o tamanho de cada um dos 26 vetores
    // int *c = turma_conta(t, N);

    int *alunos_inicial;
    alunos_inicial = turma_conta(t,N);
    
    for (int i = 0; i < 26; i++) {
        g[i] = new Aluno[alunos_inicial[i]];
    }
    
    int posicao[26];
    for (int i = 0; i < 26; i++) {
        posicao[i] = 0;
    }
    
    for (int i = 0; i < N; i++) {
        char nome = t[i].devolveNome()[0];
        if (nome >= 'A' && nome <= 'Z') {
            int p = nome - 'A';
            g[p][posicao[p]] = t[i];
            posicao[p]++;
        }
    }
    
    delete[] alunos_inicial;
    return g;
}



/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/

