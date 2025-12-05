//! Copyright [year] <Owner>
#ifndef HASHING_H
#define HASHING_H

#include <cstdint>
#include <string>
#include "./linked_list_public.h"


//! Classe Hash usando LinkedList para resolução de colisão
template<typename T>
class Hash {
 public:

    //! Classe Data que associa uma chave (string) a cada dado (tipo T)
    class Data {
     public:
        Data() {};
        ~Data() {};
        std::string key;
        T data;
    };

    //! ...
    Hash();  // construtor padrão
    //! ...
    Hash(std::size_t table_size);  // construtor com parâmetro
    //! ...
    ~Hash();  // destrutor
    //! ...
	std::size_t hash_function(std::string key);  // função de espalhamento - chave como string
	//! ...
    void clear();  // limpar hashing
    //! ...
    void insert(const std::string& key, const T& data);  // inserir
    //! ...
    void remove(const std::string& key);  // remover
    //! ...
    bool has_key(const std::string& key);  // verificar se chave/elemento existe
    //! ...
    std::size_t size() const;  // quantidade de elementos presentes no hashing
    //! ...
    std::size_t table_size() const;  // tamanho da tabela
    //! ...
    bool empty() const;  // verificar se hashing sem elementos
    //! ...
    T get(std::string key);  // devolver dado a partir da chave
    //! ...
    T operator[](std::string key);  // devolver dado a partir da chave
    //! ...
    structures::LinkedList<std::string> get_keys() const;  // lista de chaves existentes
    //! ...
    structures::LinkedList<T> get_contents() const;  // lista dados existentes
    //! ...
    structures::LinkedList<Data> get_items() const;  // lista 'chave+dado's (Data) existentes
    //! ...
    Hash<T> clone(std::size_t new_table_size);  // duplicação em memória e criação de um novo hashing
                                                // se new_table_size == 0, mantém o tamanho original

    //******************************************************************
    // Implementações necessárias:
    //! (1)
    void fromkeys(structures::LinkedList<std::string>& keys, const T& data);  // cria hashing
                                   // novo, no qual todas as chaves têm o mesmo valor 'data'
    //! (2)
    std::size_t highest();  // maior tamanho de lista (maior número de colisões)
    //! (3)
    Hash<T> firstletter(char first_letter);  // cria novo Hash, mantendo só chaves como a 1ª letra dada
    //! (4)
    bool subset(Hash<T>& hash_s);  // chaves de 'hash_s' é um subconjunto de chaves?
    //! (5)
    void update(Hash<T>& newhash);  // atualiza o hashing atual com elementos de um novo hashing
                                    // ocorre substituição de dado, se as chaves forem iguais
    //******************************************************************

    //! ...
    void print_hash(std::ostream& os) const {
        auto list_ = get_items();
        os << "{\n";
        for (std::size_t i = 0; i < list_.size(); i++) {
            auto d = list_[i];
            os << "  \"" << d.key << "\": " << d.data << ",\n";
        }
        os << "}\n";
    }

 private:

    std::size_t size_;  // quantidade total de elementos
    std::size_t table_size_;  // tamanho da tabela
    structures::LinkedList<Data>** table;  // tabela: vetor de ponteiros para listas encadeadas

    static const auto DEFAULT_SIZE = 11u;
};

#endif


//! Construtor com DEFAULT_SIZE como tamanho da tabela
template<typename T>
Hash<T>::Hash() {
    size_ = 0u;
	table_size_ = DEFAULT_SIZE;
	table = new structures::LinkedList<Data>*[table_size_];
	for (std::size_t i = 0; i < table_size_; i++) {
		table[i] = new structures::LinkedList<Data>;
	}
}

//! Construtor com escolha do tamanho da tabela
template<typename T>
Hash<T>::Hash(std::size_t table_size) {
    size_ = 0u;
	table_size_ = table_size;
	table = new structures::LinkedList<Data>*[table_size_];
	for (std::size_t i = 0; i < table_size_; i++) {
		table[i] = new structures::LinkedList<Data>;
	}
}

//! Destrutor
template<typename T>
Hash<T>::~Hash() {
	for (std::size_t i = 0; i < table_size_; i++) {
		delete table[i];  // lista na posição i
	}
	delete [] table;
}

//! Destrutor
template<typename T>
std::size_t Hash<T>::hash_function(std::string key) {
	std::size_t table_id = 0;
	for (std::size_t i = 0; i < key.length(); i++) {
		table_id = table_id + key[i];
	}
	table_id = table_id % table_size_;
	return table_id;
}

//! Esvaziar
template<typename T>
void Hash<T>::clear() {
	for (int i = 0; i < table_size_; i++) {
		table[i]->clear();
	}
	size_ = 0u;
}

//! Inserir no fim da lista alvo
template<typename T>
void Hash<T>::insert(const std::string& key, const T& data) {
    std::size_t table_id;
    table_id = hash_function(key);
    Data newdata;
    newdata.key = key;
    newdata.data = data;
    table[table_id]->push_back(newdata);
    size_++;
}

//! Remover
template<typename T>
void Hash<T>::remove(const std::string& key) {
    std::size_t table_id;
    table_id = hash_function(key);
    auto list = table[table_id];
    auto p = list->head;
    std::size_t index = 0;
    while (p != nullptr && p->data().key != key) {
        p = p->next();
        index++;
    }
    if (p != nullptr) {
        list->pop(index);
        size_--;
    }
}

//! Verficar se dado existe
template<typename T>
bool Hash<T>::has_key(const std::string& key) {
    std::size_t table_id;
    table_id = hash_function(key);
    auto list = table[table_id];
    auto p = list->head;
    while (p != nullptr && p->data().key != key) {
        p = p->next();
    }
    return p != nullptr;
}

//! Quantidade total de elementos
template<typename T>
std::size_t Hash<T>::size() const {
    return size_;
}

//! Tamanho da tabela
template<typename T>
std::size_t Hash<T>::table_size() const {
    return table_size_;
}

//! Verificar se vazio
template<typename T>
bool Hash<T>::empty() const {
    return size() == 0;
}

//! Devolver dado a partir da chave
template<typename T>
T Hash<T>::get(std::string key) {
    std::size_t table_id;
    table_id = hash_function(key);
    auto list = table[table_id];
    auto p = list->head;
    while (p != nullptr && p->data().key != key) {
        p = p->next();
    }
    if (p == nullptr) {
        throw std::out_of_range("Chave inexistente");
    }
    return p->data().data;
}

//! Devolver dado a partir da chave (notação de colchetes; ex: H["chave"])
template<typename T>
T Hash<T>::operator[](std::string key) {
    return get(key);
}

// Overload do 'operator<<' para executar 'print_hash' do 'Hash'
template <typename T>
std::ostream& operator<<(std::ostream& os, const Hash<T>& hash) {
    hash.print_hash(os);  // método interno para exibir o 'Hash' na tela
    return os;
}

//! Devolver lista de chaves existentes
template<typename T>
structures::LinkedList<std::string> Hash<T>::get_keys() const {
    structures::LinkedList<std::string> list_keys;
    for (std::size_t i = 0; i < table_size(); i++) {
        auto list = table[i];
        auto p = list->head;
        while (p != nullptr) {
            list_keys.push_back(p->data().key);
            p = p->next();
        }
    }
    return list_keys;
}

//! Devolver lista de dados existentes
template<typename T>
structures::LinkedList<T> Hash<T>::get_contents() const {
    structures::LinkedList<T> list_data;
    for (std::size_t i = 0; i < table_size(); i++) {
        auto list = table[i];
        auto p = list->head;
        while (p != nullptr) {
            list_data.push_back(p->data().data);
            p = p->next();
        }
    }
    return list_data;
}

//! Devolver lista de 'chave+dado's existentes
template<typename T>
structures::LinkedList<typename Hash<T>::Data> Hash<T>::get_items() const {
    structures::LinkedList<typename Hash<T>::Data> list_item;
    for (std::size_t i = 0; i < table_size(); i++) {
        auto list = table[i];
        auto p = list->head;
        while (p != nullptr) {
            list_item.push_back(p->data());
            p = p->next();
        }
    }
    return list_item;
}


//! Criação de um clone (duplicação em memória) do hashing
//! se new_table_size == 0, mantém o tamanho da tabela original
template<typename T>
Hash<T> Hash<T>::clone(std::size_t new_table_size) {
    Hash<T> hash_clone(table_size());
    if (new_table_size > 0) {
        hash_clone.table_size_ = new_table_size;
    }
    
    auto items = get_items();
    for (std::size_t i = 0; i < items.size(); i++) {
        auto d = items[i];
        hash_clone.insert(d.key, d.data);
    }
    return hash_clone;
}



//******************************************************************
// Implementações necessárias:

//! (1) Criação de um hashing, no qual todas as chaves recebem o mesmo dado 'data'
template<typename T>
void Hash<T>::fromkeys(structures::LinkedList<std::string>& keys, const T& data) {
    // esvazia cada lista
    for (std::size_t i = 0; i < table_size_; i++) {
        while (!table[i]->empty()) {
            table[i]->pop_front();
        }
    }

    size_ = 0;

    // insere as chaves com o mesmo dado
    for (std::size_t i = 0; i < keys.size(); i++) {
        insert(keys[i], data);
    }
}

//! (2) Cálculo do maior tamanho de lista, ou seja, o maior número de colisões existente
template<typename T>
std::size_t Hash<T>::highest() {
    std::size_t high = 0;
    
    for (std::size_t i = 0; i < table_size_; i++) {
        if (table[i]->size() > high) {
            high = table[i]->size();
        }
    }
    
    return high;
}

//! (3) Criação de novo Hash com manutenção apenas de chaves como a 1ª letra dada
template<typename T>
Hash<T> Hash<T>::firstletter(char first_letter) {
    Hash<T> hash_out(table_size());
    
    auto items = get_items();
    
    for (std::size_t i = 0; i < items.size(); i++) {
        
        auto d = items[i];
        
        if (!d.key.empty() && d.key[0] == first_letter) {
            hash_out.insert(d.key, d.data);
        }
    }
    return hash_out;
}

//! (4) Verificar se as chaves de 'hash_s' o caracterizam como um 
//!     subconjunto das chaves do próprio Hash
template<typename T>
bool Hash<T>::subset(Hash<T>& hash_s) {
    
    auto keys = hash_s.get_keys();

    for (std::size_t i = 0; i < keys.size(); i++) {
        
        if (!has_key(keys[i])) {
            return false;
        }
    }
    
    return true;
}

//! (5) Atualização do hashing atual com elementos de um novo hashing
//!     Ocorre substituição de dado, se as chaves forem iguais
template<typename T>
void Hash<T>::update(Hash<T>& newhash) {
    
    auto items = newhash.get_items();

    for (std::size_t i = 0; i < items.size(); i++) {
        auto d = items[i];

        if (has_key(d.key)) {
            remove(d.key);
        }
        
        insert(d.key, d.data);
    }
    
}
