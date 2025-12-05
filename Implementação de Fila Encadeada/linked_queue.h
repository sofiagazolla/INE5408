//! Copyright [2025] <Sofia Gazolla da Costa Silva>
namespace structures {


template<typename T>
class LinkedQueue {
public:
    LinkedQueue();

    ~LinkedQueue();

    void clear(); // limpar

    void enqueue(const T& data); // enfilerar

    T dequeue(); // desenfilerar

    T& front() const; // primeiro dado

    T& back() const; // último dado

    bool empty() const; // fila vazia

    std::size_t size() const; // tamanho

private:

    class Node {
     public:
        explicit Node(const T& data) :
            data_{data}
        {}

        Node(const T& data, Node* next) :
            data_{data},
            next_{next}
        {}

        T& data() { return data_; }
        const T& data() const { return data_; }

        Node* next() { return next_; }
        const Node* next() const { return next_; }

        void next(Node* node) { next_ = node; }

     private:
        T data_;     // dado armazenado
        Node* next_{nullptr};  // ponteiro para o próximo
    };

    Node* head; // nodo-cabeça
    Node* tail; // nodo-fim
    std::size_t size_; // tamanho
};

}


template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (size_ != 0) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    
    Node* novo = new Node(data,nullptr);
    
    if (novo == nullptr) {
        throw std::out_of_range("inválido");
    }
    
    if (empty()) {
        head = novo;
    } else {
        tail->next(novo);
    }
    
    tail = novo;
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    
    if (empty()) {
        throw std::out_of_range("a fila esta vazia");
    }
    
    Node* saiu = head; // primeiro será retirado
    T volta = saiu->data();
    
    head = saiu->next();
    
    if (size_ == 1) {
        tail = nullptr;
    }
    
    delete saiu;
    size_--;

    return volta;
    
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    
    if (empty()) {
        throw std::out_of_range("a fila esta fazia");
    }
    
    return head->data();
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    
    if (empty()) {
        throw std::out_of_range("a fila esta fazia");
    }
    
    return tail->data();
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const{
    return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}

