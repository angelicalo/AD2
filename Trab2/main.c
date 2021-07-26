/*
Integrante:
Angelica Lourenço Oliveira
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TriePrefix.h"

int main() {
    printf("\nCriando uma Arvore...\n");
    Trie* tr = criaTrie();

    printf("\nInserindo palavra(s) na Arvore...\n");
    insereTrie(tr, "amor");
    insereTrie(tr, "b");
    insereTrie(tr, "bonita");
    insereTrie(tr, "fantastico");
    insereTrie(tr, "ola");
    insereTrie(tr, "telecena");
    insereTrie(tr, "telegran");
    insereTrie(tr, "olavo");

    printf("\nImprimindo todas as palavras da Arvore\n");
    imprimeTrie(tr);

    printf("\nBuscando palavra(s) na Arvore...\n");
    printf("\nBuscando por 'ola'....:");
    if (buscaTrie(tr,"ola"))
        printf("'ola' encontrada:\n");
    else
        printf("'ola' nao encontrada:\n");


    printf("Buscando por 'voce'....:");
    if (buscaTrie(tr,"voce"))
        printf("'voce' encontrada:\n");
    else
        printf("'voce' nao encontrada:\n");

    printf("\nBuscando palavra(s) na Arvore utilizando Prefixos\n");
    printf("\nPalavras iniciadas com 'tel'\n");
    autocompletarTrie(tr,"tel");
    printf("\nPalavras iniciadas com 'a'\n");
    autocompletarTrie(tr,"a");
    printf("\nPalavras iniciadas com 'b'\n");
    autocompletarTrie(tr,"b");
    printf("\nPalavras iniciadas com 'o'\n");
    autocompletarTrie(tr,"o");

    printf("\nPalavras na Arvore:\n");
    imprimeTrie(tr);

    printf("\nRemovendo palavras da Arvore...\n");
    printf("\nRemovendo olavo...");
    removeTrie(tr, "olavo");
    printf("\nRemovendo telecena...");
    removeTrie(tr, "telecena");
    printf("\nRemovendo b...");
    removeTrie(tr, "b");
    printf("\nRemovendo bagunca...\n");
    removeTrie(tr, "bagunca");

    printf("\nPalavras removidas da Arvore:");
    printf("\nb\ntelecena\nolavo\n");

    printf("\nArvore apos remocoes\n");
    imprimeTrie(tr);

    printf("\nPalavras iniciadas com 'o'\n");
    autocompletarTrie(tr,"o");

    printf("\nLiberando arvore...\n");
    liberaTrie(tr);

    printf("\nIniciando com dados oficiais do Trabalho\n");

    char palavra[50];
    Trie* t = criaTrie();
    FILE *arq;
    arq = fopen("palavras.txt","r");
    int flat = 0;
    while(!flat){
        fscanf(arq,"%s",palavra);
        insereTrie(t,palavra);
        flat = feof(arq);
        if(flat){
            break;
        }
    }

    printf ("\nPalavras iniciadas com 'ya'\n");
    autocompletarTrie(t,"ya");

    printf ("\nPalavras iniciadas com 'y'\n");
    autocompletarTrie(t,"y");

    printf ("\nPalavras iniciadas com 'mor'\n");
    autocompletarTrie(t,"MoR");
    liberaTrie(t);
    return 0;
}
