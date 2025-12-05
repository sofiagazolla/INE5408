// Copyright [2025] <Sofia Gazolla da Costa Silva>

/*
    *** Importante ***

    O código de fila em vetor está disponível internamente (não precisa de implementação aqui)

*/



void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    for (int i = 0; i < k - 1; i++) { // roda a fila até que o elemento na posição k esteja na frente
        int primeiro = f -> dequeue(); // remove o primeiro elemento
        f -> enqueue(primeiro); // adiciona ele no final da fila
    }
    
    f -> dequeue(); // remove o elemento da posição k 
}


void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    int size = f -> size(); // converte o return da função size() p inteiro
    
    int manter; // cria uma variável para armazenar o carro que será mantido
    for (int i = 0; i < size; i++) {
        if (i == k-1){ // se for o elemento da posição k
            manter = f -> dequeue(); // armazena o elemento que deve ser mantido em uma variável
        } else {
            f -> dequeue(); // tira da fila
        }
    }
    
    f -> enqueue(manter); // coloca o elemento armazenado na fila novamente
}



/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/

