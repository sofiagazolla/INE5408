/* Copyright [2025] <Alexandre Gonçalves Silva> */
#include <stdexcept>
#include <string>
#include "gtest/gtest.h"
#include "./array_list.h"
#include "./selecao_alunos.h"

Aluno *turma(std::string nomes[], int matriculas[], int N) {
    Aluno *t = new Aluno[N];
    for (int i = 0; i < N; i++) {
        t[i].escreveNome(nomes[i]);
        t[i].escreveMatricula(matriculas[i]);
    }
    return t;
}
structures::ArrayList<Aluno> vetor2lista(Aluno *vetor, int N) {
    structures::ArrayList<Aluno> lista(N);
    for (int i = 0; i < N; i++) {
        lista.push_back(vetor[i]);
    }    
    return lista;
}

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//! comment
class TestesSelecao: public ::testing::Test {
 protected:
    //! comment
    std::string nomes1[9] = {"Alana", "Arthur", "Lorena", "Maria", "Pedro", "Olivia", "Adriano", "Lucas", "Milton"};
    int matriculas1[9] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    int N1 = 9;

    std::string nomes2[120] = {"Antonella","Lia","Ava","Pietra","Bia","Cecilia","Camila","Heloise","Jade","Kesia","Kamala","Livia","Liz","Melinda","Maite","Rayka","Raabe","Sol","Zara","Zoe","Alice","Alana","Giovanna","Greta","Mayra","Maira","Livia","Vicky","Giovanna","Emma","Gabriela","Nina","Yasmin","Flora","Leona","Camila","Anne","Layla","Sasha","Eva","Rebeca","Eloa","Luna","Elisa","Kiara","Safira","Charlotte","Mariah","Dominique","Aylla","Ravena","Iris","Louise","Alba","Leonor","Jade","Naomi","Olga","Ava","Vicky","Anthony","Bento","Xavier","Benicio","Dante","Dom","Matteo","Milo","Kalel","Kael","Lorenzo","Lucca","Oliver","Ruan","Skyler","Arlo","Sebastian","Vicente","Uriel","Yuri","Benjamin","Bento","Dominic","Levi","Noah","Otto","Otavio","Pietro","Rian","Zyan","Valentino","Micah","Dilan","Felix","Estevao","Yohan","Kaua","Rael","Yohan","Adriel","Ben","David","Levi","Anton","Elias","Oscar","Bruno","Kalu","Enrico","Isaac","Luciam","Martim","Tadeu","Tobias","Vicent","Xavier","Jordan","Jonas","Gaspar","Fausto"};
    //extraídos de 
    //https://www.dicionariodenomesproprios.com.br/
    //        nomes-de-bebe-para-meninos-e-meninas/
    int matriculas2[120];
    int N2 = 120;
    //for (int i = 0; i < N2; i++) {
    //    matriculas2[i] = 100 + i;
    //}

};

TEST_F(TestesSelecao, SelecaoNome) {
    Aluno *t1 = turma(nomes1, matriculas1, N1);
    Aluno *t2 = turma(nomes2, matriculas2, N2);
    structures::ArrayList<Aluno> lista1 = vetor2lista(t1, N1);
    structures::ArrayList<Aluno> lista2 = vetor2lista(t2, N2);
    structures::ArrayList<Aluno> sn1 = selecao_nome(lista1, 'A');
    int j = 0;
    for (int i = 0; i < N1; i++) {
        if (nomes1[i][0] == 'A') {
            ASSERT_EQ(nomes1[i], sn1[j].devolveNome());
            j++;
        }
    }
    structures::ArrayList<Aluno> sn2 = selecao_nome(lista2, 'B');
    j = 0;
    for (int i = 0; i < N2; i++) {
        if (nomes2[i][0] == 'B') {
            ASSERT_EQ(nomes2[i], sn2[j].devolveNome());
            j++;
        }
    }
    delete [] t1;
    delete [] t2;
}

TEST_F(TestesSelecao, SelecaoAmostra) {
    Aluno *t1 = turma(nomes1, matriculas1, N1);
    Aluno *t2 = turma(nomes2, matriculas2, N2);
    structures::ArrayList<Aluno> lista1 = vetor2lista(t1, N1);
    structures::ArrayList<Aluno> lista2 = vetor2lista(t2, N2);
    int k1 = 2;
    int j = 0;
    structures::ArrayList<Aluno> sa1 = selecao_amostra(lista1, k1);
    for (std::size_t i = k1-1; i < lista1.size(); i += k1) {
        ASSERT_EQ(nomes1[i], sa1[j].devolveNome());
        ASSERT_EQ(matriculas1[i], sa1[j].devolveMatricula());
        j++;
    }
    int k2 = 5;
    j = 0;
    structures::ArrayList<Aluno> sa2 = selecao_amostra(lista2, k2);
    for (std::size_t i = k2-1; i < lista2.size(); i += k2) {
        ASSERT_EQ(nomes2[i], sa2[j].devolveNome());
        //ASSERT_EQ(matriculas2[i], sa2[j].devolveMatricula());
        j++;
    }
    delete [] t1;
    delete [] t2;
}
