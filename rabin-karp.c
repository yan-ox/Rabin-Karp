/*Case BOOListe*/
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

uint64_t puissance (uint64_t x, uint64_t n, uint64_t m);
uint64_t hache (char* motif, int n, uint64_t* B);
uint64_t thache (char* motif, int n, uint64_t hache, uint64_t* B);
int rabin_karp (char* motif, char* texte);

const uint64_t base = 256; // Base pour le hachage
const uint64_t premier = 1869461003; // Nombre premier possible

uint64_t puissance(uint64_t x, uint64_t n, uint64_t m){
    if (n == 0){
        return 1;
    }
    else{
        if (n % 2 == 0){
            uint64_t p = puissance(x, n / 2, m) % m;
            return (p * p) % m;
        }
        else {
            uint64_t p = puissance(x, (n - 1) / 2, m) % m;
            return (x * ((p * p) % m)) % m;
        }
    }
}

uint64_t hache(char *motif, int lm, uint64_t* B){
    uint64_t leHache = 0;
    for(int i = 0; i < lm; i ++){
        leHache += motif[i] * B[lm - 1 - i];
    }
    return leHache;
}

uint64_t thache (char* motif, int lm, uint64_t hache, uint64_t* B){
    return ((B[1] * (hache - (B[lm - 1] * motif[-1]))) % premier) + motif[lm - 1];
}

int rabin_karp (char* motif, char* texte){
     /*Recherche les motfis comme un golem*/
    int lm = strlen(motif);
    uint64_t* B = malloc(lm * sizeof(uint64_t));
    for (int i = 0; i < lm; i ++){
        B[i] = puissance(base, i, premier);
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
                printf("trouvé à l'indice: %d\n", i);
                cpt ++;
            }
        }
        i ++;
    }
    free(B);
    return cpt;
}


void main(){
    FILE* fichier;
    fichier = fopen("Verne.txt", "r");
    fseek(fichier, 0, SEEK_END);
    int tl = ftell(fichier);
    char* texte = malloc(tl * sizeof(char));
    fseek(fichier, 0, SEEK_SET);
    for (int i = 0; i < tl; i ++){
        texte[i] = fgetc(fichier);
    }
    fclose(fichier);
    int occ = rabin_karp("environ", texte);
    uint64_t* B = malloc(6 * sizeof(uint64_t));
    for (int i = 0; i < 6; i ++){
        printf("B puissance: %d\n", puissance(base, i, premier));
        B[i] = puissance(base, i, premier);
    }
    printf("char 1:%c\n", (texte + 1)[-1]);
    uint64_t hache1 = hache(texte + 1, 6, B);
    uint64_t hache0 = hache(texte, 6, B);
    uint64_t thache1 = thache(texte + 1, 6, hache0, B) + 1;
    printf("hache0: %lld, hache1: %lld, thache1: %lld\n", hache0, hache1, thache1);
    printf("occurences: %d\n", occ);
}
