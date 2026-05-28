/*Case BOOListe*/
#include <stdint.h>
#include <string.h>

uint64_t puissance (uint64_t x, uint64_t n, uint64_t m);
uint64_t hache (char* motif, int n);
uint64_t thache (char* motif, int n, uint64_t hache);
int rabin_karp (char* motif, char* texte);

const uint64_t base = 256; // Base pour le hachage
const uint64_t base = 1869461003; // Base pour le hachage

uint64_t puissance(uint64_t x, uint64_t n, uint64_t m){
    if (n==0){
        return 1;
    }
    else{
        if (n%2 == 0){
            return (puissance(x,n/2,m) * puissance(x,n/2,m)) % m;
        }
        else {
            return (x * puissance(x,(n-1)/2,m) * puissance(x,(n-1)/2,m)) % m;
        }
    }
}

int rabin_karp (char* motif, char* texte){
     /*Recherche les motfis comme un golem*/
    int n = strlen(motif);
    int cpt = 0; 
    uint64_t base_hache = hache(motif, n);
    uint64_t p_hache = hache(texte, n);
    int i = 0;
    while (texte[i] != '\0'){
        if (i != 0){
            p_hache = thache(texte + i, n, p_hache);
        }
        if (base_hache == p_hache){
            int j = 0;
            while (motif[j] != '\0' && texte[i + j] != '\0' && motif[j] == texte[i + j]) {
                j ++;
            }
            if (motif[j] == '\0'){
                //si motif trouvé, on le stocke dans la liste chainée
                printf("trouvé à l'indice: %d", i);
                cpt ++;
            }
        }
        i ++;
    }
    return cpt;
}