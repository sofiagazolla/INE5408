#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
// Arquivos com as estruturas de pilha e fila implementados anteriormente
#include "array_stack.h"
#include "array_queue.h"

using namespace std;
using namespace structures; // Para o uso dos métodos de pilha e fila

class Cenario {
  public:
    // Construtor
    Cenario(string& texto, size_t indice_inicial) {
        size_t pos = indice_inicial;
        nome = proxima_tag_conteudo(texto, pos, "nome");
        altura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "altura") ) );
        largura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "largura") ) );
        x = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "x") ) );
        y = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "y") ) );
        matriz = matriz_remove_espacos( proxima_tag_conteudo(texto, pos, "matriz") );
        indice_final = pos;
    }
    //Destrutor
    ~Cenario() {};
    string nome;
    size_t altura;
    size_t largura;
    size_t x;
    size_t y;
    string matriz;
    size_t indice_final;

  private:
    string proxima_tag(string& texto, size_t& pos) { // 
        string tag = "";
        for ( ; pos < texto.length(); pos++) {
            if (texto[pos] == '<') { // Busca o caractere de abertura <
                pos++;
                while (texto[pos] != '>') { // Começa a capturar todos os caracteres na string tag até encontrar o caractere de fechamento >
                    tag += texto[pos]; 
                    pos++;
                }
                pos++;
                return tag; // Retorna a tag capturada, ex: se encontrar <altura>, retorna altura
            }
        }
        return tag;
    }
    string proximo_conteudo(string& texto, size_t& pos) { // Extrai o texto que está entre uma tag de abertura e sua tag de fechamento
        string txt = "";
        while (texto[pos] != '<') {
            txt += texto[pos];
            pos++;
        }
        while (texto[pos] != '>') {
            pos++;
        }
        pos++;
        return txt;
    }
    string proxima_tag_conteudo(string& texto, size_t& pos, string nome_tag) {
        string tag = "";
        while (tag != nome_tag) {
            tag = proxima_tag(texto, pos);
        }
        return proximo_conteudo(texto, pos);
    }
    string matriz_remove_espacos(string texto) {
        string saida;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] == '0' || texto[i] == '1') {
                saida += texto[i];
            }
        }
        return saida;
    }
};

// Problema 1 : validação de arquivo XML
bool verificaAninhamento(string &texto){

    ArrayStack<string> pilha; // Pilha com elementos do tipo string

    size_t indice = 0;

    // Percorrendo o texto
    while(indice < texto.length()) {
        
        if (texto[indice] == '<') { // Procurando o início de uma tag
            indice++;

            string nome_da_tag = ""; // Inicializando o nome da tag como vazio
            bool e_tag_de_fechamento = false; // Inicializa como false

            if (indice < texto.length() && texto[indice] == '/') { // Checa se é uma tag de fechamento, tem </
                e_tag_de_fechamento = true;
                indice++; // Avança para o caractere após o '/'
            }

            while (indice < texto.length() && texto[indice] != '>') { // Enquanto não chega em >, captura o nome da tag
                nome_da_tag += texto[indice];
                indice++;
            }

            if (!e_tag_de_fechamento) { // Se não é tag de fechamento (tag de abertura)
                pilha.push(nome_da_tag); // Empilha o nome da tag
            } else {
                // Erro: fechamento sem abertura
                if (pilha.empty()) {
                    return false;
                }
                // Erro: aninhamento incorreto
                if (pilha.top() != nome_da_tag) {
                    return false;
                }
                // Desempilha
                pilha.pop();
            }
        } else { // Se não encontrou <, continua avançando
            indice++;
        }
    }

    // Checagem, a pilha deve estar vazia para estar correto
    return pilha.empty();

}

// Conta <matriz>, para saber quantas matrizes teremos no nosso cenário
size_t numero_de_matrizes(const string &texto) {
    size_t contador = 0;
    size_t posicao = 0;

    while((posicao = texto.find("<matriz>", posicao)) != string::npos){
        contador ++;
        posicao = posicao + 8;
    }
    return contador;
}

size_t area_limpeza(Cenario &cenario){

    string matriz_entrada = cenario.matriz;
    size_t x = cenario.x;
    size_t y = cenario.y;
    size_t altura = cenario.altura;
    size_t largura = cenario.largura;

    size_t area_limpada = 0;

    vector<pair<int, int>> vizinhanca_4 = {{-1,0}, {1,0}, {0, -1}, {0, 1}};

    // Fila que recebe coordenadas
    ArrayQueue<pair<size_t, size_t>> fila(altura * largura);

    // Matriz R, guarda as posicoes visitadas
    string matriz_r = "";
    for (int i = 0; i < matriz_entrada.length(); i++){
        matriz_r += '0';
    }

    if (matriz_entrada[x * largura + y] == '1'){
        matriz_r[x * largura + y] = '1'; // Se na matriz de entrada eu tenho 1 em determinada posicao eu visito essa mesma posicao na mtriz r, com 1 ja que antes ela vem vazia
        fila.enqueue(make_pair(x, y)); // Coloca essa coordenada na fila
        area_limpada ++;
    }

    while (!fila.empty()){ // Enquanto houver posicoes para serem exploradas
        pair<size_t, size_t> fila_auxiliar = fila.dequeue(); // Retira a primeira coordenada da fila, que e a posicao que vai ser explorada

        for (int i = 0; i < 4; i++) { //itera sobre os 4 vizinhos
            size_t dx = fila_auxiliar.first + vizinhanca_4[i].first; // Calcula a proxima linha
            size_t dy = fila_auxiliar.second + vizinhanca_4[i].second; // Calcula a proxima coluna

            // Posicoes validas
            if (dx < altura && dx >= 0 && dy < largura && dy >=0 ) {
                size_t posicao_valida = dx * largura + dy;
                if (matriz_entrada[posicao_valida] == '1' && matriz_r[posicao_valida] == '0') { // Verifica se a matriz de entrada é limpavel e se ela nao foi visitada ainda consultando a r
                    fila.enqueue(make_pair(dx, dy)); // Enfileira a coordenada
                    matriz_r[posicao_valida] = '1'; // Visita a matriz r
                    area_limpada ++;
                }
            }
        }
    }
    return area_limpada; // retorna q quantidade de 1s limpados
}


/**********************
    FUNÇÃO PRINCIPAL
***********************/
int main() {

    string filename;

    std::cin >> filename;  // nome do arquivo de entrada 
                           // (no 'executar': escrever pelo teclado;
                           //  no 'avaliar' : nome é passado pelos testes)

    // Abertura do arquivo
    ifstream filexml(filename);
    if (!filexml.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        throw runtime_error("Erro no arquivo XML");
    }

    // Leitura do XML completo para 'texto'
    string texto;
    char character;
    while (filexml.get(character)) {
        texto += character;
    }

    // PARTE 1 - VERIFICACAO DE XML
    if (!verificaAninhamento(texto)){
        cout << "erro" << endl;
        return 0; // Se o XML for inválido, encerra o programa
    }

    // PARTE 2 - DETERMINACAO DE AREA LIMPADA
    int contador_de_matrizes = numero_de_matrizes(texto);
    size_t indice = 0;
    for (int i = 0; i < contador_de_matrizes; i++){
        Cenario cenario(texto, indice); // Cria o cenário
        int area_total = area_limpeza(cenario); // Passa ele pra funcao do calculo da area
        cout << cenario.nome << " " << area_total << endl;
        indice= cenario.indice_final;
    }
    return 0;
}