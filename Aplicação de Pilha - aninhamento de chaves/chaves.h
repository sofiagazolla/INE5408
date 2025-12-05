// Copyright [2025] <Sofia Gazolla da Costa Silva>
#include "./array_stack.h"

bool verificaChaves(std::string trecho_programa) {
    bool resposta = true;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);
    
    for (int i = 0; i < tamanho; i++) {
        if (trecho_programa[i] == '{') {
            pilha.push('{');
        } else if (trecho_programa[i] == '}') {
            if (pilha.empty()) {
                resposta = false;
                break;
            }
            pilha.pop();
        }
    }
    return resposta;
}

