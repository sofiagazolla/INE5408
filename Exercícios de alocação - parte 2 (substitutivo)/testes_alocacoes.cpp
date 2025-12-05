/* Copyright [2025] <Alexandre Gonçalves Silva> */
#include <stdexcept>
#include <string>
#include "gtest/gtest.h"
#include "./alocacoes.h"

Aluno *turma(std::string nomes[], int matriculas[], int N) {
    Aluno *t = new Aluno[N];
    for (int i = 0; i < N; i++) {
        t[i].escreveNome(nomes[i]);
        t[i].escreveMatricula(matriculas[i]);
    }
    return t;
}

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//! comment
class TestesAlocacoes: public ::testing::Test {
 protected:
    //! comment
    std::string nomes1[6] =
        {"Alana", "Arthur", "Lorena", "Maria", "Pedro", "Olivia"};
    int matriculas1[6] = {11, 22, 33, 44, 55};
    int N1 = 6;

    std::string nomes2[3] = {"Maria", "Pedro", "Olivia"};
    int matriculas2[3] = {33, 44, 55};
    int N2 = 3;

    int matriculas3[3] = {55};

    // A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    int A[26] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0};
    int B[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0};

    std::string nomes4[9] = {"Alana", "Arthur", "Lorena", "Maria", "Pedro", "Olivia", "Adriano", "Lucas", "Milton"};
    int matriculas4[9] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    int N4 = 9;

    std::string nomes5[120] = {"Antonella","Lia","Ava","Pietra","Bia","Cecilia","Camila","Heloise","Jade","Kesia","Kamala","Livia","Liz","Melinda","Maite","Rayka","Raabe","Sol","Zara","Zoe","Alice","Alana","Giovanna","Greta","Mayra","Maira","Livia","Vicky","Giovanna","Emma","Gabriela","Nina","Yasmin","Flora","Leona","Camila","Anne","Layla","Sasha","Eva","Rebeca","Eloa","Luna","Elisa","Kiara","Safira","Charlotte","Mariah","Dominique","Aylla","Ravena","Iris","Louise","Alba","Leonor","Jade","Naomi","Olga","Ava","Vicky","Anthony","Bento","Xavier","Benicio","Dante","Dom","Matteo","Milo","Kalel","Kael","Lorenzo","Lucca","Oliver","Ruan","Skyler","Arlo","Sebastian","Vicente","Uriel","Yuri","Benjamin","Bento","Dominic","Levi","Noah","Otto","Otavio","Pietro","Rian","Zyan","Valentino","Micah","Dilan","Felix","Estevao","Yohan","Kaua","Rael","Yohan","Adriel","Ben","David","Levi","Anton","Elias","Oscar","Bruno","Kalu","Enrico","Isaac","Luciam","Martim","Tadeu","Tobias","Vicent","Xavier","Jordan","Jonas","Gaspar","Fausto"};
    //extraídos de 
    //https://www.dicionariodenomesproprios.com.br/
    //        nomes-de-bebe-para-meninos-e-meninas/
    int matriculas5[120];
    int N5 = 120;
    //for (int i = 0; i < N5; i++) {
    //    matriculas5[i] = 100 + i;
    //}

    // A B C D E F G H I J K L M N O P 
    // Q R S T U V W X Y Z
    int A2[26] = {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1, 1, 
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    int B2[26] = {12,  7,  4,  6,  7,  3,  5,  1,  2,  4,  7, 14,  9,  3,  5,  2,
                   0,  7,  5,  2,  1,  5,  0,  2,  4,  3};
    
};

TEST_F(TestesAlocacoes, TurmaFiltra) {
    Aluno *t1 = turma(nomes1, matriculas1, N1);
    Aluno *t2 = turma(nomes2, matriculas2, N2);
    Aluno *tf1 = turma_filtra(t1, N1, 33);
    for (int i = 0; i < 3; i++) {
        ASSERT_EQ(matriculas2[i], tf1[i].devolveMatricula());
    }
    Aluno *tf2 = turma_filtra(t2, N2, 50);
    for (int i = 0; i < 1; i++) {
        ASSERT_EQ(matriculas3[i], tf2[i].devolveMatricula());
    }
    delete [] t1;
    delete [] t2;
    delete [] tf1;
    delete [] tf2;
}

TEST_F(TestesAlocacoes, TurmaConta) {
    Aluno *t1 = turma(nomes1, matriculas1, N1);
    Aluno *t2 = turma(nomes2, matriculas2, N2);
    int *c1 = turma_conta(t1, N1);
    int *c2 = turma_conta(t2, N2);

    for (int i = 0; i < 26; i++) {
        ASSERT_EQ(A[i], c1[i]);
    }
    for (int i = 0; i < 26; i++) {
        ASSERT_EQ(B[i], c2[i]);
    }
    delete [] t1;
    delete [] t2;
    delete [] c1;
    delete [] c2;
}

TEST_F(TestesAlocacoes, GruposPorIniciais) {
    Aluno *t1 = turma(nomes4, matriculas4, N4);
    Aluno *t2 = turma(nomes5, matriculas5, N5);
    
    Aluno **g1 = grupos_por_iniciais(t1, N4);
    Aluno **g2 = grupos_por_iniciais(t2, N5);

    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < A2[k]; i++) {
            ASSERT_EQ('A'+k, g1[k][i].devolveNome()[0]);
        }
    }

    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < B2[k]; i++) {
            ASSERT_EQ('A'+k, g2[k][i].devolveNome()[0]);
        }
    }

    for (int k = 0; k < 26; k++) {
        delete [] g1[k];
        delete [] g2[k];
    }
    
    delete [] g1;
    delete [] g2;
    delete [] t1;
    delete [] t2;
}
