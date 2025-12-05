namespace structures {

template<typename T>
class LinkedStack {
public:
    LinkedStack(){
        top_ = nullptr;
        size_ = 0;
    }

    ~LinkedStack(){
        clear();
    }

    void clear() {  // limpa pilha
        while (!empty()) {
            pop();
        }
    } 
    

    void push(const T& data) {  // empilha
        Node* novo = new Node(data,top_);
        top_ = novo;
        size_ ++;
    } 


    T pop() {  // desempilha
        if (empty()) {
            throw std::out_of_range("a pilha está vazia");
        }
        
        Node* saida = top_;
        
        T data = saida->data();
        
        top_ = saida->next();
        
        delete saida;
        
        size_--;
        
        return data;
    } 
    

    T& top() const{  // dado no topo
        if (empty()) {
            throw std::out_of_range("a pilha está vazia");
        }
        
        return top_->data();
    } 


    bool empty() const {  // pilha vazia
        return size_ == 0;
    } 

    std::size_t size() const {  // tamanho da pilha
        return size_;
    }

private:
    class Node {
    public:
        Node(const T& data){
            data_ = data;
            next_ = nullptr;
        }
        
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        T& data() {
            return data_;
        } // getter: info
        
        
        const T& data() const{
            return data_;
        } // getter-constante: info


        Node* next(){
            return next_;
        } // getter: próximo
        
        
        const Node* next() const{
            return next_;
        } // getter-constante: próximo

        
        void next(Node* next){
            next_ = next;
        } // setter: próximo
    
    
    private:
        T data_;
        Node* next_;
    };

    Node* top_; // nodo-topo
    std::size_t size_; // tamanho
};

}
