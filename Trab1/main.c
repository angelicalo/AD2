#include <stdio.h>
#include <stdlib.h>
#include "TabelaHash.h"

/*
Integrantes:
Angélica Lourenço Oliveira  - 11711GIN061
Gabriel Alexandre Gonçalves - 11411GIN047
Murilo Andrade Ferreira     - 11611GIN047
Thiago de Oliveira Borges   - 11621GIN021
*/

typedef struct aluno{
    int matricula;
    char nome[30];
    int n1,n2,n3;
}Aluno;

int main(){
    int M, N, tipoChave, tipoSond;
    char caminho[10] = "alunos.txt";

    printf("\n------------------Criando a tabela------------------\n");
    printf("\nEntre com tamanho inicial da tabela (M): ");
    scanf("%d",&M);
    printf("Entre com tamanho da estrutura (N): (struct Aluno N=48)-> ");
    scanf("%d",&N);
    //N = 48;
    Hash *ha = criaHash(M,N);

    printf("\n--------Caracteristicas de inserção da tabela--------\n");
    printf("\n(0) - Hash Divisao\n(1) - Hash Multiplicacao\n(2) - Hash Dobra\nEscolha um tipo: ");
    scanf("%d", &tipoChave);
    if (tipoChave !=0 && tipoChave !=1 && tipoChave !=2)
        printf ("Valor invalido! Tomada Chave Dobra\n");

    printf("\n(0) - sondagem Linear\n(1) - sondagem Quadratica\n(2) - duplo Hash\nEscolha um tipo: ");
    scanf("%d", &tipoSond);
    if (tipoSond !=0 && tipoSond !=1 && tipoSond !=2)
        printf ("Valor invalido! Tomada Duplo Hash\n");

    printf("\n------------------Inserindo alunos------------------\n");
    Aluno alunos[2287];
    FILE *arq;
    arq = fopen(caminho,"r");//Lendo o arquivo de alunos
    int chave;
    int flat = 0;
    int i = 0;
    printf("\nTamanho inicial da tabela: M=%d.\n",M);
    while (!flat) {
        fscanf(arq,"%d %s %d %d %d", &alunos[i].matricula, &alunos[i].nome, &alunos[i].n1, &alunos[i].n2, &alunos[i].n3);
        flat = feof(arq);//atingir o fim do arquivo
        if(flat){
            printf ("\nFinal do arquivo atingido. Inseridos %d alunos.\n",load_fator(ha));
            break;
        }
        if (load_fator(ha) >= M * 0.75){
            printf("\nTamanho da tabela: M=%d. load_factor=%d\n",M,load_fator(ha));
            printf("Atingido 75 por cento.\nDobra-se o tamanho da tabela para ");
            liberaHash(ha);
            M = 2*M;
            printf("M=%d.\n",M);
            Hash *ha = criaHash(M,N);
            printf("Realocando os alunos lidos na tabela...", M, load_fator(ha));
            for(int j=0; j < i; j++){
                chave = alunos[j].matricula;
                Aluno *al = &alunos[j];
                insereHash(ha, chave, &al, tipoChave, tipoSond);
                }
            printf("\n%d alunos realocados.\n",load_fator(ha));
            } //realocou os dados da outra tabela e inseriu na nova tabela criada
        Aluno *al = &alunos[i];
        chave = al->matricula;
        insereHash(ha, chave, &al, tipoChave, tipoSond); //inserindo alunos na tabela
        i++;
        }
    /*
    //Imprime os dados dos alunos lidos e salvos na lista de estrutura do tipo alunos
    Int SN;
    printf("Deseja listar os dados dos alunos?\nSe sim aperte 1: ");
    scanf("%d", &SN);
    if (SN){
        printf("\nMatricula \t Nome e notas\n");
        for (i = 0; i < (load_fator(ha)); i++){
            Aluno al = alunos[i];
            printf("%d \t\t %s %d %d %d\n", al.matricula, al.nome, al.n1, al.n2, al.n3);
        }
    }*/

    printf("\n------------------Buscando alunos-------------------\n");
    flat = 1;
    while (flat){
        printf("\nDigite o numero de matricula: ");
        int mat;
        scanf("%d",&mat);
        Aluno *alu;
        int enc = buscaHash(ha,mat,&alu,tipoChave,tipoSond);
        Aluno *alun = &alu;
        if(enc==0){
            printf("\nAluno não encontrado!\n");
        }else{
            printf("\nAluno encontrado! Pos na Hashtable=%d",enc);
            printf("\nMatricula  \t Nome e notas\n");
            printf("%d\t\t %s %d %d %d\n", alu->matricula, alu->nome, alu->n1, alu->n2, alu->n3);
            }
        printf("\nBuscar mais? (1) Sim (0) Nao: ");
        scanf("%d",&flat);
    }

    liberaHash(ha);
    return 0;

}
