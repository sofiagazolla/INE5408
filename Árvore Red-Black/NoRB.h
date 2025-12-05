#ifndef NO_RB_HPP
#define NO_RB_HPP
#include <vector>
#include <stdexcept>

#define RB_RUBRO true
#define RB_NEGRO false

template <typename T>
class NoRB {
 private:
    T* dado;
    NoRB<T>* esquerda;
    NoRB<T>* direita;
    NoRB<T>* pai;
    bool cor;
    std::vector<NoRB<T>*> elementos;

    NoRB<T>* getRaiz(NoRB<T>* nodo) {
        if (nodo == nullptr) {
            return nullptr;
        }
        while (nodo->pai != nullptr) {
            nodo = nodo->pai;
        }
        return nodo;
    }

    NoRB<T>* simp_roda_esq(NoRB<T>* nodo) {
        NoRB<T>* pivo = nodo->direita;
        nodo->direita = pivo->esquerda;
        
        if (pivo->esquerda != nullptr) {
            pivo->esquerda->pai = nodo;
        }
        
        pivo->pai = nodo->pai;
        
        if (nodo->pai != nullptr) {
            if (nodo == nodo->pai->esquerda) {
                nodo->pai->esquerda = pivo;
            } else {
                nodo->pai->direita = pivo;
            }
        }
        
        pivo->esquerda = nodo;
        nodo->pai = pivo;
        
        return pivo;
    }

    NoRB<T>* simp_roda_dir(NoRB<T>* nodo) {
        NoRB<T>* pivo = nodo->esquerda;
        nodo->esquerda = pivo->direita;
        
        if (pivo->direita != nullptr) {
            pivo->direita->pai = nodo;
        }
        
        pivo->pai = nodo->pai;
        
        if (nodo->pai != nullptr) {
            if (nodo == nodo->pai->direita) {
                nodo->pai->direita = pivo;
            } else {
                nodo->pai->esquerda = pivo;
            }
        }
        
        pivo->direita = nodo;
        nodo->pai = pivo;
        
        return pivo;
    }

    void arrumar_insercao(NoRB<T>* nodo) {
        while (nodo->pai != nullptr && nodo->pai->cor == RB_RUBRO) {
            NoRB<T>* pai = nodo->pai;
            NoRB<T>* avo = pai->pai;
            
            if (avo == nullptr) break;
            
            if (pai == avo->esquerda) {
                NoRB<T>* tio = avo->direita;
                
                if (getCor(tio) == RB_RUBRO) {
                    pai->cor = RB_NEGRO;
                    tio->cor = RB_NEGRO;
                    avo->cor = RB_RUBRO;
                    nodo = avo;
                } else {
                    if (nodo == pai->direita) {
                        simp_roda_esq(pai);
                        nodo = pai;
                        pai = nodo->pai;
                    }
                    
                    pai->cor = RB_NEGRO;
                    avo->cor = RB_RUBRO;
                    simp_roda_dir(avo);
                    break;
                }
            } else {
                NoRB<T>* tio = avo->esquerda;
                
                if (getCor(tio) == RB_RUBRO) {
                    pai->cor = RB_NEGRO;
                    tio->cor = RB_NEGRO;
                    avo->cor = RB_RUBRO;
                    nodo = avo;
                } else {
                    if (nodo == pai->esquerda) {
                        simp_roda_dir(pai);
                        nodo = pai;
                        pai = nodo->pai;
                    }
                    
                    pai->cor = RB_NEGRO;
                    avo->cor = RB_RUBRO;
                    simp_roda_esq(avo);
                    break;
                }
            }
        }
    }

    void arrumar_remocao(NoRB<T>* nodo) {
        while (nodo->pai != nullptr && getCor(nodo) == RB_NEGRO) {
            if (nodo == nodo->pai->esquerda) {
                NoRB<T>* irmao = nodo->pai->direita;
                
                if (getCor(irmao) == RB_RUBRO) {
                    irmao->cor = RB_NEGRO;
                    nodo->pai->cor = RB_RUBRO;
                    simp_roda_esq(nodo->pai);
                    irmao = nodo->pai->direita;
                }
                
                if (getCor(irmao->esquerda) == RB_NEGRO && 
                    getCor(irmao->direita) == RB_NEGRO) {
                    irmao->cor = RB_RUBRO;
                    nodo = nodo->pai;
                } else {
                    if (getCor(irmao->direita) == RB_NEGRO) {
                        if (irmao->esquerda != nullptr) {
                            irmao->esquerda->cor = RB_NEGRO;
                        }
                        irmao->cor = RB_RUBRO;
                        simp_roda_dir(irmao);
                        irmao = nodo->pai->direita;
                    }
                    
                    irmao->cor = nodo->pai->cor;
                    nodo->pai->cor = RB_NEGRO;
                    if (irmao->direita != nullptr) {
                        irmao->direita->cor = RB_NEGRO;
                    }
                    simp_roda_esq(nodo->pai);
                    break;
                }
            } else {
                NoRB<T>* irmao = nodo->pai->esquerda;
                
                if (getCor(irmao) == RB_RUBRO) {
                    irmao->cor = RB_NEGRO;
                    nodo->pai->cor = RB_RUBRO;
                    simp_roda_dir(nodo->pai);
                    irmao = nodo->pai->esquerda;
                }
                
                if (getCor(irmao->direita) == RB_NEGRO && 
                    getCor(irmao->esquerda) == RB_NEGRO) {
                    irmao->cor = RB_RUBRO;
                    nodo = nodo->pai;
                } else {
                    if (getCor(irmao->esquerda) == RB_NEGRO) {
                        if (irmao->direita != nullptr) {
                            irmao->direita->cor = RB_NEGRO;
                        }
                        irmao->cor = RB_RUBRO;
                        simp_roda_esq(irmao);
                        irmao = nodo->pai->esquerda;
                    }
                    
                    irmao->cor = nodo->pai->cor;
                    nodo->pai->cor = RB_NEGRO;
                    if (irmao->esquerda != nullptr) {
                        irmao->esquerda->cor = RB_NEGRO;
                    }
                    simp_roda_dir(nodo->pai);
                    break;
                }
            }
        }
    }

    void preOrdemAux(NoRB<T>* nodo) {
        if (nodo != nullptr) {
            elementos.push_back(nodo);
            preOrdemAux(nodo->esquerda);
            preOrdemAux(nodo->direita);
        }
    }

    void emOrdemAux(NoRB<T>* nodo) {
        if (nodo != nullptr) {
            emOrdemAux(nodo->esquerda);
            elementos.push_back(nodo);
            emOrdemAux(nodo->direita);
        }
    }

    void posOrdemAux(NoRB<T>* nodo) {
        if (nodo != nullptr) {
            posOrdemAux(nodo->esquerda);
            posOrdemAux(nodo->direita);
            elementos.push_back(nodo);
        }
    }

 public:
    explicit NoRB(const T& dado) {
        this->dado = new T(dado);
        this->esquerda = nullptr;
        this->direita = nullptr;
        this->pai = nullptr;
        this->cor = RB_RUBRO;
    }

    virtual ~NoRB() {
        delete dado;
    }

    NoRB<T>* getPai() {
        return pai;
    }

    bool getCor(NoRB<T>* nodo) {
        if (nodo == nullptr) {
            return RB_NEGRO;
        }
        return nodo->cor;
    }

    std::vector<NoRB<T>*> getElementos() {
        return elementos;
    }

    NoRB<T>* getEsquerda() {
        return esquerda;
    }

    NoRB<T>* getDireita() {
        return direita;
    }

    T* getDado() {
        return dado;
    }

    NoRB<T>* minimo(NoRB<T>* nodo) {
        if (nodo == nullptr) {
            return nullptr;
        }
        while (nodo->esquerda != nullptr) {
            nodo = nodo->esquerda;
        }
        return nodo;
    }

    T* busca(const T& dado, NoRB<T>* arv) {
        while (arv != nullptr) {
            if (dado < *arv->dado) {
                arv = arv->esquerda;
            } else if (dado > *arv->dado) {
                arv = arv->direita;
            } else {
                return arv->dado;
            }
        }
        throw std::runtime_error("Elemento não encontrado");
    }

    void preOrdem(NoRB<T>* nodo) {
        elementos.clear();
        preOrdemAux(nodo);
    }

    void emOrdem(NoRB<T>* nodo) {
        elementos.clear();
        emOrdemAux(nodo);
    }

    void posOrdem(NoRB<T>* nodo) {
        elementos.clear();
        posOrdemAux(nodo);
    }

    NoRB<T>* inserir(const T& dado, NoRB<T>* arv) {
        if (dado < *arv->dado) {
            if (arv->esquerda == nullptr) {
                NoRB<T>* novo = new NoRB<T>(dado);
                arv->esquerda = novo;
                novo->pai = arv;
                arrumar_insercao(novo);
                NoRB<T>* raiz = getRaiz(novo);
                raiz->cor = RB_NEGRO;
                return raiz;
            } else {
                return inserir(dado, arv->esquerda);
            }
        } else {
            if (arv->direita == nullptr) {
                NoRB<T>* novo = new NoRB<T>(dado);
                arv->direita = novo;
                novo->pai = arv;
                arrumar_insercao(novo);
                NoRB<T>* raiz = getRaiz(novo);
                raiz->cor = RB_NEGRO;
                return raiz;
            } else {
                return inserir(dado, arv->direita);
            }
        }
    }

    NoRB<T>* remover(NoRB<T>* arv, const T& dado) {
        if (arv == nullptr) {
            return nullptr;
        }
        
        NoRB<T>* nodo = arv;
        
        while (nodo != nullptr && *nodo->dado != dado) {
            if (dado < *nodo->dado) {
                nodo = nodo->esquerda;
            } else {
                nodo = nodo->direita;
            }
        }
        
        if (nodo == nullptr) {
            return arv;
        }
        
        // Caso especial: removendo o único nó
        if (nodo->pai == nullptr && nodo->esquerda == nullptr && nodo->direita == nullptr) {
            // delete nodo->dado; // REMOVA ESTA LINHA
            delete nodo;
            return nullptr;
        }
        
        bool cor_original = nodo->cor;
        NoRB<T>* x = nullptr;
        
        if (nodo->esquerda == nullptr) {
            x = nodo->direita;
            
            if (nodo->pai == nullptr) {
                arv = x;
            } else if (nodo == nodo->pai->esquerda) {
                nodo->pai->esquerda = x;
            } else {
                nodo->pai->direita = x;
            }
            
            if (x != nullptr) {
                x->pai = nodo->pai;
            }
            
            // delete nodo->dado; // REMOVA ESTA LINHA
            delete nodo;
            
        } else if (nodo->direita == nullptr) {
            x = nodo->esquerda;
            
            if (nodo->pai == nullptr) {
                arv = x;
            } else if (nodo == nodo->pai->esquerda) {
                nodo->pai->esquerda = x;
            } else {
                nodo->pai->direita = x;
            }
            
            if (x != nullptr) {
                x->pai = nodo->pai;
            }
            
            // delete nodo->dado; // REMOVA ESTA LINHA
            delete nodo;
            
        } else {
            NoRB<T>* sucessor = minimo(nodo->direita);
            cor_original = sucessor->cor;
            x = sucessor->direita;
            
            if (sucessor->pai == nodo) {
                if (x != nullptr) {
                    x->pai = sucessor;
                }
            } else {
                sucessor->pai->esquerda = x;
                
                if (x != nullptr) {
                    x->pai = sucessor->pai;
                }
                
                sucessor->direita = nodo->direita;
                if (sucessor->direita != nullptr) {
                    sucessor->direita->pai = sucessor;
                }
            }
            
            if (nodo->pai == nullptr) {
                arv = sucessor;
            } else if (nodo == nodo->pai->esquerda) {
                nodo->pai->esquerda = sucessor;
            } else {
                nodo->pai->direita = sucessor;
            }
            
            sucessor->pai = nodo->pai;
            sucessor->esquerda = nodo->esquerda;
            if (sucessor->esquerda != nullptr) {
                sucessor->esquerda->pai = sucessor;
            }
            sucessor->cor = nodo->cor;
            
            // delete nodo->dado; // REMOVA ESTA LINHA
            delete nodo;
        }
        
        if (cor_original == RB_NEGRO && arv != nullptr && x != nullptr) {
            arrumar_remocao(x);
            arv = getRaiz(x);
        }
        
        if (arv != nullptr) {
            arv->cor = RB_NEGRO;
        }
        
        return arv;
    }
};

#endif /* NO_RB_HPP */