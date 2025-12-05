// Copyright [2025] <Maria Eduarda Teixeira Costa e Sofia Gazolla da Costa Silva>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int tamanho_alfabeto = 26; // definimos o tamanho do alfabeto como uma constante

struct NoTrie {
    NoTrie* filhos[tamanho_alfabeto]; // vetor de ponteiros para todos os filhos do nó
    unsigned long posicao;     // posição onde a palavra começa
    unsigned long comprimento; // tamanho da palavra
};


NoTrie* criarNo() { // funciona como um construtor
    NoTrie* no = new NoTrie; // aloca memória para o novo nó

    // inicializa com os valores padrão
    no->posicao = 0;
    no->comprimento = 0;

    // inicializa todos os filhos como nulos, já que eles não existem ainda
    for (int i = 0; i < tamanho_alfabeto; i++) {
        no->filhos[i] = nullptr;
    }

    return no;
}


void inserir(NoTrie* raiz, string palavra, unsigned long pos, unsigned long comp) {
    NoTrie* atual = raiz; // começamos a partir da raiz

    // percorre cada caractere da palavra
    for (char c : palavra) {

        int index = c - 'a'; // converte o caractere em um índice

        if (atual->filhos[index] == nullptr) { // se ainda não existe um nó
            atual->filhos[index] = criarNo(); // cria um novo nó
        }

        atual = atual->filhos[index]; // vai para o próximo nó até chegar no fim da palavra
    }

    // aqui, atual está na última letra da palavra
    atual->posicao = pos; // guarda onde a palavra está no arquivo
    atual->comprimento = comp; // guarda o tamanho da palavra
}


NoTrie* buscarNo(NoTrie* raiz, string prefixo) {
    NoTrie* atual = raiz; // começa na raiz

    for (char c : prefixo) { // percorre cada caractere do prefixo inserido pelo usuário
        int index = c - 'a'; // converte o caractere em um índice

        if (atual->filhos[index] == nullptr) { // se o prefixo não existe
            return nullptr; // o prefixo não está na trie
        }

        atual = atual->filhos[index]; // vai para o próximo nó até chegar no final do prefixo
    }

    return atual; // retorna o nó onde o prefixo termina
}


int contarPalavras(NoTrie* no) {
    if (no == nullptr) { // se o nó não existe, não há palavras
        return 0;
    }

    int contador = 0;

    // verifica se o próprio nó é uma palavra
    if (no->comprimento > 0) {
        contador = 1;
    }

    // chama a função recursivamente para somar as palavras dos filhos para cada filho
    for (int i = 0; i < tamanho_alfabeto; i++) {
        contador += contarPalavras(no->filhos[i]);
    }

    return contador; // retorna a quantidade total de palavras
}


void liberarMemoria(NoTrie* no) {
    if (no == nullptr) { // se o nó estiver vazio não há nada pra liberar
        return;
    }

    // libera todos os filhos primeiro
    for (int i = 0; i < tamanho_alfabeto; i++) {
        liberarMemoria(no->filhos[i]);
    }

    delete no; // depois de liberar os filhos, libera o próprio nó
}


int main() {
    string filename;

    NoTrie* raiz = criarNo(); // cria o nó raiz

    cin >> filename; // entrada
    ifstream arquivo(filename); // abre o arquivo

    if (!arquivo.is_open()) { // se não abrir o arquivo corretamente
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return 1; // encerra com erro
    }

    string linha;
    unsigned long pos = arquivo.tellg(); // tellg() pega a posição atual

    // loop que lê o arquivo linha por linha
    while (getline(arquivo, linha)) {
        size_t posFechamento = linha.find(']'); // encontra a posição do ] para saber onde acaba a palavra
        
        if (posFechamento == string::npos) { // se não encontrou o ]
            continue; // ignora a linha
        }

        string palavra = linha.substr(1, posFechamento - 1); // extrai a palavra do primeiro caractere até o ]
        unsigned long comp = linha.length(); // pega o comprimento da linha

        inserir(raiz, palavra, pos, comp); // chama a função inserir para inserir na trie

        pos = arquivo.tellg(); // atualiza para a posição da próxima linha
    }
    
    arquivo.close(); // fecha o arquivo após terminar de ler

    string word;

    // lê e processa as palavras inseridas pelo usuário
    while (cin >> word && word != "0") { // enquanto a entrada for diferente de 0
        
        NoTrie* no = buscarNo(raiz, word); // chama a função pra encontrar o nó

        if (no == nullptr) { // se o nó não foi encontrado, não é prefixo
            cout << word << " is not prefix" << endl;
        } else { // se o nó foi encontrado, ele é um prefixo
            
            // primeiro problema: identificação de prefixos
            int qtdePalavras = contarPalavras(no);
            cout << word << " is prefix of " << qtdePalavras << " words" << endl;

            // segundo problema: indexação de arquivo de dicionário
            if (no->comprimento > 0) { // se comprimento > 0, ela existe
                cout << word << " is at (" << no->posicao << "," << no->comprimento << ")" << endl;
            }
        }
    }

    liberarMemoria(raiz); // libera a memória

    return 0;
}