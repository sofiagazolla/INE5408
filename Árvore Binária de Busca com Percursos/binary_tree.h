// Copyright [2025] <Sofia Gazolla da Costa Silva>

#include "array_list.h"

namespace structures {

// AS IMPLEMENTAÇÕES PODEM SER RECURSIVAS OU NÃO
// SE NECESSÁRIO, OPERAÇÕES ALTERNATIVAS OU AUXILIARES PODEM SER ADICIONADAS
// (NESTE CASO, A OPERAÇÃO TESTADA É BASICAMENTE UMA CHAMADA A OUTRO MÉTODO)

template<typename T>
class BinaryTree {
public:
    BinaryTree();

    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;
    
    
private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            left = nullptr;
            right = nullptr;
        }

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            
            if (data_ < data) { // inserção à esquerda
                    if (left == nullptr) {
                        left = new Node(data_);
                    } else {
                        left->insert(data_);
                    }
                    
            } else { // inserção à direita
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }
        }

        bool remove(const T& data_) {
            
            if (data_ < data) {
                if (left != nullptr) {
                    left->remove(data_);
                    if (left->data == data_ && left->left == nullptr && left->right == nullptr) {
                        delete left;
                        left = nullptr;
                    }
                }
            } else if (data_ > data) {
                if (right != nullptr) {
                    right->remove(data_);
                    if (right->data == data_ && right->left == nullptr && right->right == nullptr) {
                        delete right;
                        right = nullptr;
                    }
                }
            } else {
                if (left != nullptr && right != nullptr) {
                    Node* minimo = right;
                    while (minimo->left != nullptr) {
                        minimo = minimo->left;
                    }
                    data = minimo->data;
                    right->remove(minimo->data);
                } else {
                    Node* filho;
                    if (left != nullptr) {
                        filho = left;
                    } else {
                        filho = right;
                    }

                    if (filho != nullptr) {
                        data = filho->data;
                        Node* esquerda = filho->left;
                        Node* direita = filho->right;
                        delete filho;
                        left = esquerda;
                        right = direita;
                    } else {
                        left = nullptr;
                        right = nullptr;
                    }
                }
            }

            return true;
        }

        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                if (left != nullptr) {
                    return left->contains(data_);
                } else {
                    return false;
                }
            } else {  // data_ > data
                if (right != nullptr) {
                    return right->contains(data_);
                } else {
                    return false;
                }
            }
        }

        void pre_order(ArrayList<T>& v) const {
            
            v.push_back(data);
            
            if (left != nullptr) {
                left->pre_order(v);
            }
            
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            
            if (left != nullptr) {
                left->in_order(v);
            }
            
            v.push_back(data);
            
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            
            if (left != nullptr) {
                left->post_order(v);
            }
            
            if (right != nullptr) {
                right->post_order(v);
            }
            
            v.push_back(data);
        }
            
    };

    Node* root;
    std::size_t size_;
    
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    
};

}  // namespace structures

//-------------------------------------

template<typename T>
structures::BinaryTree<T>::BinaryTree() {
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
        
    clear(root);
    root = nullptr;
    size_ = 0;
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    
    size_++;
    
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    
    if (root != nullptr) {
        root->remove(data);
        size_--;
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (root != nullptr) {
        return root->contains(data);
    } else {
        return false;
    }
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> L;
	if (root != nullptr) {
		root->pre_order(L);
	}
	return L;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
        structures::ArrayList<T> L;
	if (root != nullptr) {
		root->in_order(L);
	}
	return L;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
        structures::ArrayList<T> L;
	if (root != nullptr) {
		root->post_order(L);
	}
	return L;
}
