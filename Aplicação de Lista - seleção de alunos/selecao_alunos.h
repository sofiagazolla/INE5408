// Copyright [2025] <COLOQUE SEU NOME AQUI...>

/*
    *** Importante ***

    - É preciso anexar o código de lista em vetor
    
    - Não é necessário incluir a lista (#include "./array_list.h")
      Isto é feito nos testes

*/


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


/*
(1) seleciona alunos de uma lista 'turma_entrada', cujos nomes iniciam com uma determinada 'letra', produzinda uma lista 'turma_saida' como resposta.
Exemplo:
  turma_entrada = [{'Fulano',1010}, {'Beltrano',2020}, {'Fulana',7070}, {'Cicrana':1515}, {'Beltrana',8080}]
  letra = 'F'
  turma_saida = [{'Fulano',1010}, {'Fulana',7070}]
*/

structures::ArrayList<Aluno> selecao_nome(structures::ArrayList<Aluno> &turma_entrada, char letra) {
    structures::ArrayList<Aluno> turma_saida(turma_entrada.size());

    for (std::size_t i = 0; i < turma_entrada.size(); i++) { // percorre todos os alunos
        Aluno aluno = turma_entrada[i]; // verifica o aluno atual
        if (!aluno.devolveNome().empty() && aluno.devolveNome()[0] == letra) { // se não for vazio e a letra for igual a verificada
            turma_saida.push_back(aluno); // adiciona o aluno a lista
        }
    }

    return turma_saida;
}

/*
(2) amostra alunos a cada 'k' posições de uma lista 'turma_entrada'.
Exemplo: 
  turma_entrada: [A,B,C,D,E,F,G,H]
  k = 3
  turma_saida: [C,F]
*/

structures::ArrayList<Aluno> selecao_amostra(structures::ArrayList<Aluno> &turma_entrada, int k) {
    structures::ArrayList<Aluno> turma_saida(turma_entrada.size());

    if (k <= 0) { // se entrada for inválida
        return turma_saida; // retorna lista vazia
    }
    
    for (std::size_t i = k - 1; i < turma_entrada.size(); i += k) { // começa na posição k - 1 e a cada incremento aumenta k índices
        turma_saida.push_back(turma_entrada[i]); // adiciona o aluno a lista
    }


    return turma_saida;
}

