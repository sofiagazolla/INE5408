//!  Copyright [2025] <Sofia Gazolla da Costa Silva>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "./array_list.h"


namespace structures {

//! Classe Árvore binária
template<typename T>
class BinaryTree {
 public:
    //! ...
    BinaryTree();
    //! ...
    ~BinaryTree();
    //! ...
    void insert(const T& data);
    //! ...
    void remove(const T& data);
    //! ...
    bool contains(const T& data) const;
    //! ...
    bool empty() const;
    //! ...
    std::size_t size() const;
    //! ...
    ArrayList<T> pre_order() const;
    //! ...
    ArrayList<T> in_order() const;
    //! ...
    ArrayList<T> post_order() const;

    //******************************************************************
    // Prova prática - implementações necessárias:

    // (1) determinação da altura da árvore:
    int height();

    // (2) contagem do número de folhas:
    int leaves();

    // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
    //     valor da árvore:
    ArrayList<T> limits();

    // (4) criação de uma duplicação, em memória, da árvore:
    BinaryTree<T> clone();

    // (5) remove nós pelo número de seus filhos:
    void filter(int n_child);

    // (6) criação de um nova árvore que tenha todos os valores e a
    //     menor altura possível, ou seja, balanceada com base apenas
    //     no estabelecimento de uma nova ordem de inserção:
    BinaryTree<T> balance();

    //******************************************************************


 private:
    struct Node {
        //! Construtor
        explicit Node(const T& data) :
        data_{data}
        {}

        //! Destrutor
        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;
        Node* left_{nullptr};
        Node* right_{nullptr};

        //! Inserção
        void insert(const T& data) {
            
            if (data < data_) { // inserção à esquerda
                    if (left_ == nullptr) {
                        left_ = new Node(data);
                    } else {
                        left_->insert(data);
                    }
                    
            } else { // inserção à direita
                if (right_ == nullptr) {
                    right_ = new Node(data);
                } else {
                    right_->insert(data);
                }
            }
        }

        //! Remoção
        bool remove(const T& data) {
            bool existe = false;

            if (data < data_) {
                if (left_ != nullptr) {
                    existe = left_->remove(data);
                    if (left_ != nullptr && left_->data_ == data && left_->left_ == nullptr && left_->right_ == nullptr) {
                        delete left_;
                        left_ = nullptr;
                    }
                }
            } else if (data > data_) {
                if (right_ != nullptr) {
                    existe = right_->remove(data);
                    if (right_ != nullptr && right_->data_ == data && right_->left_ == nullptr && right_->right_ == nullptr) {
                        delete right_;
                        right_ = nullptr;
                    }
                }
            } else {
                existe = true; // encontramos o nó a ser removido
                if (left_ != nullptr && right_ != nullptr) {
                    Node* minimo = right_;
                    while (minimo->left_ != nullptr) {
                        minimo = minimo->left_;
                    }
                    data_ = minimo->data_;
                    right_->remove(minimo->data_);
                } else {
                    Node* filho = (left_ != nullptr) ? left_ : right_;
                    if (filho != nullptr) {
                        data_ = filho->data_;
                        Node* esquerda = filho->left_;
                        Node* direita = filho->right_;
                        filho->left_ = nullptr;
                        filho->right_ = nullptr;
                        delete filho;
                        left_ = esquerda;
                        right_ = direita;
                    } else {
                        // nó folha
                        left_ = nullptr;
                        right_ = nullptr;
                    }
                }
            }

            return existe;
        }


        //! Contém
        bool contains(const T& data) const {
            bool existe = false;

            if (data == data_) {
                existe = true;
            } else if (data < data_) {
                if (left_ != nullptr) {
                    existe = left_->contains(data);
                }
            } else {
                if (right_ != nullptr) {
                    existe = right_->contains(data);
                }
            }

            return existe;
        }


        //! Pré ordem
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        //! Em ordem
        void in_order(ArrayList<T>& v) const {
            if (left_ != nullptr) {
                left_->in_order(v);
            }
            
            v.push_back(data_);
            
            if (right_ != nullptr) {
                right_->in_order(v);
            }
        }

        //! Pós ordem
        void post_order(ArrayList<T>& v) const {
            if (left_ != nullptr) {
                left_->post_order(v);
            }
            
            if (right_ != nullptr) {
                right_->post_order(v);
            }
            
            v.push_back(data_);
        }
        
        int altura(int atual) const {
            
            if (left_ == nullptr && right_ == nullptr) {
                return atual;
            }
            
            int direita = 0;
            int esquerda = 0;
    
            if (right_ != nullptr) {
                direita = right_->altura(atual + 1);
            }
    
            if (left_ != nullptr) {
                esquerda = left_->altura(atual + 1);
            }
    
            if (direita > esquerda) {
                return direita;
            }
            
            return esquerda;
        }
        
        int folhas() const {
            if (left_ == nullptr && right_ == nullptr) {
                return 1; // nó folha
            }
            
            int total = 0;
            
            if (left_ != nullptr) {
                total += left_->folhas();
            }
            
            if (right_ != nullptr) {
                total += right_->folhas();
            }
            
            return total;
        }
        


     private:
        // //! Complemento da funcão de remoção
        Node* remove(const T& data, Node* arv, bool& deleted) {
            if (!arv) {
                deleted = false;
                return nullptr;
            }
        
            if (data < arv->data_) {
                arv->left_ = remove(data, arv->left_, deleted);
            } else if (data > arv->data_) {
                arv->right_ = remove(data, arv->right_, deleted);
            } else {
                deleted = true;
                if (!arv->left_) {
                    Node* r = arv->right_;
                    arv->right_ = nullptr;
                    delete arv;
                    return r;
                }
        
                if (!arv->right_) {
                    Node* l = arv->left_;
                    arv->left_ = nullptr;
                    delete arv;
                    return l;
                }
        
                // dois filhos
                Node* min = arv->right_;
                while (min->left_) {
                    min = min->left_;
                }
                arv->data_ = min->data_;
                arv->right_ = remove(min->data_, arv->right_, deleted);
            }
        
            return arv;
        }

        //! Encontrar o menor
        Node* minimum() {
            if (left_ == nullptr)
                return this;
            return left_->minimum();
        }
    };

    Node* root_{nullptr};
    std::size_t size_{0};
    
    Node* minimo(Node* node);
    Node* maximo(Node* node);
    Node* clonar(Node* node);
    Node* filtrar(Node* node, int n_child);
    void insercao_recursiva(BinaryTree<T>& B, ArrayList<T>& L, int inicio, int fim);

};




//******************************************************************
// Prova prática - implementações necessárias:

//! (1) determinação da altura da árvore:
template<typename T>
int BinaryTree<T>::height() {
    if (empty()) {
        throw std::out_of_range("a arvore esta vazia");
    }
    
    return root_->altura(0);
}

//! (2) contagem do número de folhas:
template<typename T>
int BinaryTree<T>::leaves() {
    if (empty()) {
        throw std::out_of_range("a arvore esta vazia");
    }
    return root_->folhas();
}

//! (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//!     valor da árvore:
template<typename T>
ArrayList<T> BinaryTree<T>::limits() {
    ArrayList<T> L(2);
    if (root_ == nullptr) {
        return L;
    }

    Node* min = minimo(root_);
    Node* max = maximo(root_);

    L.insert(min->data_,0);
    L.insert(max->data_,1);
    
    return L;
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::minimo(Node* node) {
    if (node == nullptr || node->left_ == nullptr) {
        return node;
    }    
    
    return minimo(node->left_);
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::maximo(Node* node) {
    if (node == nullptr || node->right_ == nullptr) {
        return node;
    }    
    
    return maximo(node->right_);
}

//! (4) criação de uma duplicação, em memória, da árvore:
template<typename T>
BinaryTree<T> BinaryTree<T>::clone() {
    
    BinaryTree<T> C;
    ArrayList<T> L(size());
    root_->pre_order(L);
    
    for (size_t i = 0; i < L.size(); i++) {
        C.insert(L[i]);
    }
    
    return C;
}

// (5) remove nós pelo número de seus filhos:
template<typename T>
void BinaryTree<T>::filter(int n_child) {
        root_ = filtrar(root_, n_child);
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::filtrar(Node* node, int n_child) {
    if (node == nullptr) {
        return nullptr;
    }

    // primeiro filtra os filhos (pós-ordem)
    node->left_ = filtrar(node->left_, n_child);
    node->right_ = filtrar(node->right_, n_child);

    // conta quantos filhos o nó atual possui
    int cont_child = 0;
    if (node->left_ != nullptr) cont_child++;
    if (node->right_ != nullptr) cont_child++;

    // se o número de filhos for diferente do solicitado, mantém o nó
    if (cont_child != n_child) {
        return node;
    }

    // caso o nó tenha exatamente n_child filhos → remove ele

    // --- caso 0 filhos (nó folha)
    if (cont_child == 0) {
        delete node;
        --size_;
        return nullptr;
    }

    // --- caso 1 filho (substitui pelo filho)
    if (cont_child == 1) {
        Node* child = (node->left_ != nullptr) ? node->left_ : node->right_;
        // desconecta o nó antes de deletar para evitar double delete
        node->left_ = nullptr;
        node->right_ = nullptr;
        delete node;
        --size_;
        return child;
    }

    // --- caso 2 filhos (mantém o nó, não remove)
    return node;
}

//! (6) criação de um nova árvore que tenha todos os valores e a
//!     menor altura possível, ou seja, balanceada com base apenas
//!     no estabelecimento de uma nova ordem de inserção:
template<typename T>
BinaryTree<T> BinaryTree<T>::balance() {
    BinaryTree<T> B;
    if (empty()) {
        return B;  // árvore vazia
    }

    ArrayList<T> L(size());       
    root_->in_order(L);            // preenche L com todos os elementos em ordem
    insercao_recursiva(B, L, 0, static_cast<int>(L.size()) - 1);
    return B;
}

template<typename T>
void BinaryTree<T>::insercao_recursiva(BinaryTree<T>& B, ArrayList<T>& L, int inicio, int fim) {
    if (inicio > fim) return;

    int meio = (inicio + fim) / 2;
    B.insert(L[meio]);

    insercao_recursiva(B, L, inicio, meio - 1);  // insere esquerda
    insercao_recursiva(B, L, meio + 1, fim);     // insere direita
}



//******************************************************************



//! Construtor
template<typename T>
BinaryTree<T>::BinaryTree()
{}

//! Destrutor
template<typename T>
BinaryTree<T>::~BinaryTree() {
    delete root_;
}

//! Inserção
template<typename T>
void BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("FUll tree!");
    } else {
            root_->insert(data);
    }
    ++size_;
}

// Remoção
template<typename T>
void BinaryTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree");

    if (size() != 1u) {
        if (root_->remove(data))
            --size_;
    } else {
        if (root_->data_ == data) {
            delete root_;
            root_ = nullptr;
            --size_;
        }
    }
}

//! Contém
template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Vazio
template<typename T>
bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Tamanho
template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Pré ordem
template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->pre_order(v);
    return v;
}

//! Em ordem
template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

//! Pós ordem
template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

}  // namespace structures


#endif
