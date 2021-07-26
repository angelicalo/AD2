#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TriePrefix.h"

typedef struct Trie Trie;

struct Trie{
    char data;
    int endWord;
    Trie* children[26];
};

Trie* criaTrie(){
    Trie* tr=(Trie*) calloc (1,sizeof(Trie));
    for (int i=0; i<26; i++)
        tr->children[i]=NULL;
    tr->data='\0';
    tr->endWord=0;
    return tr;
};

void liberaTrie(Trie* tr){
    for(int i=0; i<26; i++){
        if (tr->children[i] !=NULL){
            liberaTrie(tr->children[i]);
        }else{
            continue;
        }
    }
    free(tr);
};

int insereTrie(Trie* tr,char* str){
    for (int i=0; str[i] !='\0'; i++){
        Trie* t=criaTrie();
        t->endWord=0;
        t->data=str[i];
        if (tr->children[str[i]-97]==NULL)
            tr->children[str[i]-97]=t;
        tr =tr->children[str[i]-97];
    }
    tr->endWord=1;
    return 1;
};

int buscaTrie(Trie* tr,char* str){
    Trie* tri=tr;
    for(int i=0; str[i]!='\0'; i++){
        int position=str[i]-97;
        if (tri->children[position]==NULL){
            return 0;
        }
        tri=tri->children[position];
    }
    if (tri!=NULL && tri->endWord==1){
        return 1;
    }
    return 0;
};

int removeTrie(Trie* tr,char* str){
    if (!buscaTrie(tr,str))
        return 0;
    Trie* tri=tr;
    int position;
    for(int i=0;str[i]!='\0'; i++){
        if (str[i]>=97 && str[i]<=122){
            position=str[i]-97;
        }else{
            position=str[i]-97+32;
        }
        if (tri->children[position]==NULL){
            return 0;
        }
        tri=tri->children[position];
    }
    if(tri->endWord){
        tri->endWord=0;
        int libera=1;
        for (int i=0;i<26; i++){
            if (tri->children[i]!=NULL){
                libera=0;
            }
        }
        if (libera){
            tri = NULL;
            free(tri);
        }
        return 1;
    }
    return 0;
}

void autocompletarTrie(Trie* tr,char *prefixo){
    Trie* tri=tr;
    int position;
    for(int i=0; prefixo[i]!='\0'; i++){
        if (prefixo[i]>=97 && prefixo[i]<=122){
            position=prefixo[i]-97;
        }else{
            position=prefixo[i]-97+32;
        }
        if (tri->children[position]==NULL){
            break;
        }
        tri=tri->children[position];
    }

    if(tri->endWord){
        for (int i=0;prefixo[i]!='\0';i++)
            if (prefixo[i]<97 || prefixo[i]>122)
                prefixo[i]=prefixo[i]+32;
        printf("%s\n",prefixo);
    }
    for(int i=0;i<26;i++){
        Trie* t=tri->children[i];
        if(t!=NULL){
            const char* str1=prefixo;
            const char* str2=&(t->data);
            int len=strlen(str1)+strlen(str2);
            char str[len];
            memccpy(memccpy(str,str1,'\0',len)-1,str2,'\0',len);
            autocompletarTrie(tr,str);
        }
    }
};

void imprimeTrie(Trie* tr){
    if(!tr){
        return;
    }
    for (int i=0; i<26;i++){
        Trie* tri=tr->children[i];
        if(tri!=NULL){
            autocompletarTrie(tr,&(tri->data));
        }
    }
};
