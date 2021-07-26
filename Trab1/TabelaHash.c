#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabelaHash.h"

//Definição do tipo Hash
typedef struct hash Hash;
struct hash{
    int qtd, TABLE_SIZE, TAMANHO_TIPO, *chaveBusca;
    void **itens;
    };

Hash* criaHash(int TABLE_SIZE, int TAMANHO_TIPO){
    Hash* ha = (Hash*) malloc(sizeof(Hash));
    if(ha != NULL){
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->TAMANHO_TIPO = TAMANHO_TIPO;

        ha->itens = (void**) malloc(TABLE_SIZE * TAMANHO_TIPO);
        ha->chaveBusca = (int *) malloc(TABLE_SIZE * TAMANHO_TIPO);

        if(ha->itens == NULL){
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for(i=0; i < ha->TABLE_SIZE; i++)
            ha->itens[i] = NULL;
            ha->chaveBusca[i] = NULL;
    }
    return ha;
}
void liberaHash(Hash* ha){
    ha->TABLE_SIZE=0;
    if(ha != NULL){
        free(ha->itens);
        int i;
        for(i=0; i < ha->TABLE_SIZE; i++){
            if(ha->itens[i] != NULL){
                free(&(ha->itens[i]));
                free(&(ha->chaveBusca[i]));
            }
        }
        free(ha);
    }
}
//HashDivisao
int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}
//HashDobra
int chaveDobra(int chave, int TABLE_SIZE){
    int num_bits = 10;
    int parte1 = chave >> num_bits;
    int parte2 = chave & (TABLE_SIZE-1);
    return (parte1 ^ parte2);
}
//HashMultiplicação
int chaveMultiplicacao(int chave, int TABLE_SIZE){
    double A = 0.6180339887; // constante: 0 < A < 1
    double val = chave * A;
    val = val - (int) val;
    return (int) (TABLE_SIZE * val);
}

//==================================================================//
// Inserção e busca com tratamento de colisão: Endereçamento Aberto //
//==================================================================//
int sondagemLinear(int pos, int i, int TABLE_SIZE){
    return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}
int sondagemQuadratica(int pos, int i, int TABLE_SIZE){
    pos = pos + 2*i + 5*i*i;
    return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}
int duploHash(int H1, int chave, int i, int TABLE_SIZE){
    int H2 = chaveDivisao(chave,TABLE_SIZE-1) + 1;
    return ((H1 + i*H2) & 0x7FFFFFFF) % TABLE_SIZE;
}

int insereHash(Hash* ha, int chave, void * dados, int tipoChave, int tipoSond){
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE)
        return 0;

    int i, pos, newPos;
    switch (tipoChave){
        case 0:
            pos = chaveDivisao(chave,ha->TABLE_SIZE);
        break;
        case 1:
            pos = chaveMultiplicacao(chave,ha->TABLE_SIZE);
        break;
        case 2:
            pos = chaveDobra(chave,ha->TABLE_SIZE);
        break;
        default :
            pos = chaveDobra(chave,ha->TABLE_SIZE);
        }
    for(i=0; i < ha->TABLE_SIZE; i++){
        switch (tipoSond){
            case 0:
                newPos = sondagemLinear(pos,i,ha->TABLE_SIZE);
            break;
            case 1:
                newPos = sondagemQuadratica(pos,i,ha->TABLE_SIZE);
            break;
            case 2:
                newPos = duploHash(pos,chave,i,ha->TABLE_SIZE);
            break;
            default:
                newPos = duploHash(pos,chave,i,ha->TABLE_SIZE);
        }
        if(ha->itens[newPos] == NULL){
            ha->chaveBusca[newPos] = malloc(sizeof(int));
            ha->chaveBusca[newPos] = chave;
            memcpy(&(ha->itens[newPos]), dados, sizeof(dados));
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

int buscaHash(Hash* ha, int chave, void * dados, int tipoChave, int tipoSond){
    if(ha == NULL)
        return 0;
    int i, pos, newPos;
    switch(tipoChave){
        case 0:
            pos = chaveDivisao(chave,ha->TABLE_SIZE);
        break;
        case 1:
            pos = chaveMultiplicacao(chave,ha->TABLE_SIZE);
        break;
        case 2:
            pos = chaveDobra(chave,ha->TABLE_SIZE);
        break;
        default:
            pos = chaveDobra(chave,ha->TABLE_SIZE);
        }

    for(i=0; i < ha->TABLE_SIZE; i++){
        switch (tipoSond){
            case 0:
                newPos = sondagemLinear(pos,i,ha->TABLE_SIZE);
            break;
            case 1:
                newPos = sondagemQuadratica(pos,i,ha->TABLE_SIZE);
            break;
            case 2:
                newPos = duploHash(pos,chave,i,ha->TABLE_SIZE);
            break;
            default:
                newPos = duploHash(pos,chave,i,ha->TABLE_SIZE);
        }
        if(ha->itens[newPos] == NULL){
            return 0;
        }else{
            if(ha->chaveBusca[newPos] == chave){
                memcpy(dados, &(ha->itens[newPos]), sizeof(dados));
                return newPos;
            }
        }
    }
    return 0;
}
int load_fator (Hash* ha){
    return ha->qtd;
}
