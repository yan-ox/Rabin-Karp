/*Case BOOListe*/
#include <stdint.h>
#include <string.h>

uint64_t puissance (uint64_t x, uint64_t n, uint64_t m);
uint64_t hache (char* motif, int n, uint64_t* B);
uint64_t thache (char* motif, int n, uint64_t hache, uint64_t* B);
int rabin_karp (char* motif, char* texte);

const uint64_t base = 256; // Base pour le hachage
const uint64_t premier = 1869461003; // Base pour le hachage

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

uint64_t hache(char *motif, int lm, uint64_t* B){
    uint64_t leHache=0;
    for(int i=0; i<lm; i++){
        leHache += motif[i] * B[i];
    }
    return leHache;
}

uint64_t thache (char* motif, int n, uint64_t hache, uint64_t* B){
    return B[1] * (hache - B[n - 1] * motif[0]) + motif[n - 1];
}

int rabin_karp (char* motif, char* texte){
     /*Recherche les motfis comme un golem*/
    int lm = strlen(motif);
    uint64_t* B = malloc(lm * sizeof(uint64_t));
    for (int i = 0; i < lm; i ++){
        B[i] = puissance(base, lm - 1 - i, premier);
    }
    int cpt = 0; 
    uint64_t base_hache = hache(motif, lm, B);
    uint64_t p_hache = hache(texte, lm, B);
    int i = 0;
    while (texte[i] != '\0'){
        if (i != 0){
            p_hache = thache(texte + i, lm, p_hache, B);
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