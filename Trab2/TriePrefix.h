typedef struct Trie Trie;

Trie* criaTrie();

int insereTrie(Trie* tr, char *str);
int buscaTrie(Trie* tr, char *str);
int removeTrie(Trie* tr, char *str);

void liberaTrie(Trie* tr);
void imprimeTrie(Trie* tr);
void autocompletarTrie(Trie* tr, char *prefixo);
