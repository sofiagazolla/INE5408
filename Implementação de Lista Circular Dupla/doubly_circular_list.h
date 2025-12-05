//! "Copyright [2025] <Sofia Gazolla da Costa Silva>"
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data);
       // Node(const T& data, Node* next);
        Node(const T& data, Node* prev, Node* next);

        T& data();
        const T& data() const;

        Node* prev();
        const Node* prev() const;
        void prev(Node* node);

        Node* next();
        const Node* next() const;
        void next(Node* node);

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

// Implementação da parte do private 

template<typename T>
DoublyCircularList<T>::Node::Node(const T& data):
    data_(data), prev_(nullptr), next_(nullptr) {}

template<typename T>
DoublyCircularList<T>::Node::Node(const T& data, Node* prev, Node* next):
    data_(data), prev_(prev), next_(next) {}

template<typename T>
T& DoublyCircularList<T>::Node::data() { 
    return data_; 
}

template<typename T>
const T& DoublyCircularList<T>::Node::data() const { 
    return data_; 
}

template<typename T>
typename DoublyCircularList<T>::Node* DoublyCircularList<T>::Node::prev() { 
    return prev_; 
}

template<typename T>
const typename DoublyCircularList<T>::Node* DoublyCircularList<T>::Node::prev() const { 
    return prev_; 
}

template<typename T>
void DoublyCircularList<T>::Node::prev(Node* node) { 
    prev_ = node; 
}

template<typename T>
typename DoublyCircularList<T>::Node* DoublyCircularList<T>::Node::next() { 
    return next_; 
}

template<typename T>
const typename DoublyCircularList<T>::Node* DoublyCircularList<T>::Node::next() const { 
    return next_; 
}

template<typename T>
void DoublyCircularList<T>::Node::next(Node* node) { 
    next_ = node; 
}


// Implementação dos métodos em public

//! Construtor
template<typename T>
DoublyCircularList<T>::DoublyCircularList():
    head(nullptr), size_(0u) {}

//! Destrutor
template<typename T>
DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

//! Esvazia a lista
template<typename T>
void DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

//! Inserção no início
template<typename T>
void DoublyCircularList<T>::push_front(const T& data) {
    Node* novo = new Node(data);

    if (empty()) {
        head = novo;
        head->next(head);
        head->prev(head);
    } else {
        Node* tail = head->prev();
        novo->next(head);
        novo->prev(tail);
        tail->next(novo);
        head->prev(novo);
        head = novo;
    }

    size_++;
}

//! Inserção no fim
template<typename T>
void DoublyCircularList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
        return;
    }

    Node* tail = head->prev();
    Node* novo = new Node(data, tail, head);
    tail->next(novo);
    head->prev(novo);

    size_++;
}

//! Inserção na posição
template<typename T>
void DoublyCircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("indice invalido");

    if (index == 0) {
        push_front(data);
        return;
    }

    if (index == size_) {
        push_back(data);
        return;
    }

    Node* atual = head;
    for (std::size_t i = 0; i < index; i++)
        atual = atual->next();

    Node* anterior = atual->prev();
    Node* novo = new Node(data, anterior, atual);
    anterior->next(novo);
    atual->prev(novo);

    size_++;
}

//! Inserção ordenada
template<typename T>
void DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty() || data <= head->data()) {
        push_front(data);
        return;
    }

    Node* atual = head->next();
    std::size_t index = 1;

    while (atual != head && data > atual->data()) {
        atual = atual->next();
        index++;
    }

    insert(data, index);
}

//! Remoção do início
template<typename T>
T DoublyCircularList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("a lista esta vazia");

    Node* temp = head;
    T data = temp->data();

    if (size_ == 1) {
        head = nullptr;
    } else {
        Node* tail = head->prev();
        head = head->next();
        head->prev(tail);
        tail->next(head);
    }

    delete temp;
    size_--;
    return data;
}

//! Remoção do fim
template<typename T>
T DoublyCircularList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("a lista esta vazia");

    if (size_ == 1)
        return pop_front();

    Node* tail = head->prev();
    T data = tail->data();
    Node* novo_tail = tail->prev();

    novo_tail->next(head);
    head->prev(novo_tail);

    delete tail;
    size_--;
    return data;
}

//! Remoção da posição
template<typename T>
T DoublyCircularList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("a lista esta vazia");

    if (index >= size_)
        throw std::out_of_range("indice invalido");

    if (index == 0)
        return pop_front();

    if (index == size_ - 1)
        return pop_back();

    Node* atual = head;
    for (std::size_t i = 0; i < index; i++)
        atual = atual->next();

    T data = atual->data();
    Node* anterior = atual->prev();
    Node* proximo = atual->next();

    anterior->next(proximo);
    proximo->prev(anterior);

    delete atual;
    size_--;
    return data;
}

//! Remove específico
template<typename T>
void DoublyCircularList<T>::remove(const T& data) {
    std::size_t index = find(data);
    if (index == size_)
        throw std::out_of_range("elemento nao encontrado");
    pop(index);
}

//! Lista vazia?
template<typename T>
bool DoublyCircularList<T>::empty() const {
    return size_ == 0u;
}

//! Verifica se contém o dado
template<typename T>
bool DoublyCircularList<T>::contains(const T& data) const {
    return find(data) != size_;
}
 
//! Retorna referência ao dado na posição
template<typename T>
T& DoublyCircularList<T>::at(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("índice inválido");

    Node* atual = head;
    for (std::size_t i = 0; i < index; i++)
        atual = atual->next();

    return atual->data();
}

//! Retorna referência constante ao dado na posição
template<typename T>
const T& DoublyCircularList<T>::at(std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("índice inválido");

    Node* atual = head;
    for (std::size_t i = 0; i < index; i++)
        atual = atual->next();

    return atual->data();
}

//! Encontra o índice do dado
template<typename T>
std::size_t DoublyCircularList<T>::find(const T& data) const {
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
std::size_t DoublyCircularList<T>::size() const {
    return size_;
}

 
} // namespace structures

#endif


