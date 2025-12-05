//! "Copyright [2025] <Sofia Gazolla da Costa Silva>"
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class CircularList {
public:
    CircularList();
    ~CircularList();

    void clear(); // limpar lista

    void push_back(const T& data); // inserir no fim
    void push_front(const T& data); // inserir no início
    void insert(const T& data, std::size_t index); // inserir na posição
    void insert_sorted(const T& data); // inserir em ordem

    T& at(std::size_t index); // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const; // versão const do acesso ao indice

    T pop(std::size_t index); // retirar da posição
    T pop_back(); // retirar do fim
    T pop_front(); // retirar do início
    void remove(const T& data); // remover dado específico

    bool empty() const; // lista vazia
    bool contains(const T& data) const; // lista contém determinado dado?
    std::size_t find(const T& data) const; // posição de um item na lista

    std::size_t size() const; // tamanho da lista
    
    
 private:
    class Node {
     public:
        explicit Node(const T& data);
        Node(const T& data, Node* next);

        T& data();
        const T& data() const;

        Node* next();
        const Node* next() const;
        void next(Node* node);

     private:
        T data_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};


// Implementação do private

template<typename T>
structures::CircularList<T>::Node::Node(const T& data)
    : data_(data), next_(nullptr) {}

template<typename T>
structures::CircularList<T>::Node::Node(const T& data, Node* next)
    : data_(data), next_(next) {}

template<typename T>
T& CircularList<T>::Node::data() { 
    return data_; 
}

template<typename T>
const T& CircularList<T>::Node::data() const { 
    return data_; 
}

template<typename T>
typename CircularList<T>::Node* CircularList<T>::Node::next() { 
    return next_; 
}

template<typename T>
const typename CircularList<T>::Node* CircularList<T>::Node::next() const { 
    return next_; 
}

template<typename T>
void CircularList<T>::Node::next(Node* node) { 
    next_ = node; 
}


// Implementação dos métodos

//! Construtor
template<typename T>
CircularList<T>::CircularList()
    : head(nullptr), size_(0) {}


//! Destrutor
template<typename T>
CircularList<T>::~CircularList() {
    clear();
}


//!Esvazia a lista
template<typename T>
void CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}


//! Inserção no fim
template<typename T>
void CircularList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
        return;
    }
    
    Node* noMovel = head;
    
    while (noMovel->next() != head){
        noMovel = noMovel->next();
    }
    
    Node* novoNo = new Node(data,head);
    noMovel->next( novoNo);
    size_++;
}


//! Inserção no início
template<typename T>
void CircularList<T>::push_front(const T& data) {
    Node* novo = new Node(data);
    if (empty()) {
        head = novo;
        head->next(head);  // aponta pra si mesma
    } else {
        Node* tail = head;
        // encontra o último nó (que aponta para head)
        while (tail->next() != head)
            tail = tail->next();
        novo->next(head);
        head = novo;
        tail->next(head);  // fecha o círculo
    }
    size_++;
}


//! Inserção em posição
template<typename T>
void CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Índice inválido");

    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* anterior = head;
        for (std::size_t i = 0; i < index - 1; ++i)
            anterior = anterior->next();
        Node* novo = new Node(data, anterior->next());
        anterior->next(novo);
        size_++;
    }
}


//! Inserção ordenada
template<typename T>
void CircularList<T>::insert_sorted(const T& data) {
    if (empty() || data <= head->data()) {
        push_front(data);
    } else {
        Node* atual = head;
        std::size_t index = 0;
        while (atual->next() != head && data > atual->next()->data()) {
            atual = atual->next();
            index++;
        }
        insert(data, index + 1);
    }
}


//! Remoção em posição
template<typename T>
T CircularList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Lista vazia");

    if (index >= size_)
        throw std::out_of_range("Índice inválido");

    if (index == 0)
        return pop_front();

    Node* anterior = head;
    for (std::size_t i = 0; i < index - 1; ++i)
        anterior = anterior->next();

    Node* atual = anterior->next();
    T dado = atual->data();
    anterior->next(atual->next());
    delete atual;
    size_--;
    return dado;
}


//! Remoção do fim
template<typename T>
T CircularList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("Lista vazia");

    if (size_ == 1)
        return pop_front();

    Node* anterior = head;
    while (anterior->next()->next() != head)
        anterior = anterior->next();

    Node* ultimo = anterior->next();
    T dado = ultimo->data();
    anterior->next(head);
    delete ultimo;
    size_--;
    return dado;
}


//! Remoção do início
template<typename T>
T CircularList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista vazia");

    Node* antigo = head;
    T dado = antigo->data();

    if (size_ == 1) {
        head = nullptr;
    } else {
        Node* tail = head;
        while (tail->next() != head)
            tail = tail->next();
        head = head->next();
        tail->next(head);
    }

    delete antigo;
    size_--;
    return dado;
}


//! Remove um dado específico
template<typename T>
void CircularList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Lista vazia");

    std::size_t index = find(data);
    if (index != size_)
        pop(index);
}


//! Lista vazia?
template<typename T>
bool CircularList<T>::empty() const {
    return size_ == 0u;
}


//! Verifica se contém o dado
template<typename T>
bool CircularList<T>::contains(const T& data) const {
    return find(data) != size_;
}
 
 
//! Retorna referência ao dado na posição
template<typename T>
T& CircularList<T>::at(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("índice inválido");

    Node* atual = head;
    for (std::size_t i = 0; i < index; i++)
        atual = atual->next();

    return atual->data();
}


//! Retorna referência constante ao dado na posição
template<typename T>
const T& CircularList<T>::at(std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("índice inválido");

    Node* atual = head;
    for (std::size_t i = 0; i < index; i++)
        atual = atual->next();

    return atual->data();
}


//! Encontra o índice do dado
template<typename T>
std::size_t CircularList<T>::find(const T& data) const {
    Node* atual = head;
    for (std::size_t i = 0; i < size_; i++) {
        if (atual->data() == data)
            return i;
        atual = atual->next();
    }
    return size_;
}


//! Retorna tamanho
template<typename T>
std::size_t CircularList<T>::size() const {
    return size_;
}


}

#endif

