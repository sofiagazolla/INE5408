// Copyright [2025] <Sofia Gazolla da Costa Silva>
#include <string>
#include "./array_queue.h"

structures::ArrayQueue<char> editaTexto(std::string texto) {
    structures::ArrayQueue<char> fila(500);
    char ultimo = '\0';  // salva o ultimo caractere caso precise reinserir

    for (char c : texto) {
        if (c == '<') {  // se for para remover
            if (fila.empty()) {  // verifica se não está vazia
                throw std::out_of_range("A fila está vazia");  // lança exceção se estiver
            }
            fila.dequeue();  // remove o caractere
        } else if (c == '>') {  // se for para reinserir
            if (ultimo != '\0') {  // se o caractere salvo não for nulo
                fila.enqueue(ultimo);  // adiciona ele na fila novamente
            }
        } else {  // se não for nenhum dos símbolos especiais
            fila.enqueue(c);  // adiciona o caractere
            ultimo = c;   // atualiza o caractere salvo na variável ultimo
        }
    }
    return fila;
}
