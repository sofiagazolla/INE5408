// Copyright [2025] <Sofia Gazolla da Costa Silva>
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! CLASSE PILHA
class ArrayStack {
 public:
    //! construtor simples
    ArrayStack();
    //! construtor com parametro tamanho
    explicit ArrayStack(std::size_t max);
    //! destrutor
    ~ArrayStack();
    //! metodo empilha
    void push(const T& data);
    //! metodo desempilha
    T pop();
    //! metodo retorna o topo
    T& top();
    //! metodo limpa pilha
    void clear();
    //! metodo retorna tamanho - size_t é um inteiro unsigned
    std::size_t size();
    //! metodo retorna capacidade maxima
    std::size_t max_size();
    //! verifica se esta vazia
    bool empty();
    //! verifica se esta cheia
    bool full();

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

// Construtor simples
template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

// Construtor com parâmetro tamanho
template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

// Destrutor
template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

// Empilha
template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("pilha cheia");
    } else {
        contents[top_ + 1] = data;
        top_++;
    }
}

// Tira o último elemento
template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("A pilha está vazia");
    } else {
        return contents[top_--];
    }
}

// Retorna elemento do topo
template<typename T>
T& structures::ArrayStack<T>::top() {
    return contents[top_];
}

// Limpa
template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;  // pq quando a pilha está vazia, top é -1, já que quando adicionar o primeiro elemento, top vai ser 0
}

// Retorna o tamanho da pilha
template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_ + 1;
}

// Capacidade máxima
template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

// Verifica se está vazia
template<typename T>
bool structures::ArrayStack<T>::empty() {
    return top_ == -1;
}

// Verifica se está cheia
template<typename T>
bool structures::ArrayStack<T>::full() {
    return size() == max_size_;
}
