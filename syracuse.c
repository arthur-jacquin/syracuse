#include <stdio.h>

unsigned long old, new; /* n et son iteration */
unsigned short int nb_iter; /* Nombre d'iterations de Syracuse dans une iteration */
unsigned short int k; /* Indice pour l'ecriture de l'iteration */
unsigned short int i; /* Indice de boucle */

struct { /* ADDr */
    unsigned in1:1; /* Entree 1 */
    unsigned in2:1; /* Entree 2 */
    unsigned in3:1; /* Entree 3 */
    unsigned tmp:1; /* Sortie 1 du premier bloc ADD */
    unsigned out1:1; /* Sortie 1 */
    unsigned out2:1; /* Sortie 2 */
} c;

void ADDr () {
    c.tmp = (c.in2 | c.in3) & (~c.in2 | ~c.in3);
    c.out1 = (c.in1 | c.tmp) & (~c.in1 | ~c.tmp);
    c.out2 = (c.in1 & c.tmp) | (c.in2 & c.in3);
};

struct { /* Suivi de l'ecriture de l'iteration */
    unsigned debute:1;
    unsigned overflow:1;
} bools;

void iter_impair () {
    /* Initialisation des variables */
    c.in1 = 1;
    c.in2 = 1;
    bools.debute = 0;
    k = 0;

    /* Initialisation du resultat */
    nb_iter++;
    nb_iter++;
    new = 0;

    /* Ecriture de l'iteration */
    for (i = 0; i < 8*sizeof(old); i++) {
        c.in3 = old & 1;
        ADDr();
        c.in1 = c.out2;
        c.in2 = old & 1;
        old >>= 1;
        if (bools.debute) {
            new += c.out1 << k;
            k++;
        } else {
            if (c.out1) {
                bools.debute = 1;
            } else {
                nb_iter++;
            }
        }
    }
    c.in3 = 0;
    ADDr();
    new += c.out1 << k;

    /* Detection d'overflow */
    bools.overflow = c.out2;
};

int m (unsigned long n) { /* Retourne 0 en cas d'erreur, m(n) sinon */
    /* Verification n non nul */
    if (n == 0) {
        return 0;
    };

    /* Initialisation des variables */
    nb_iter = 0;
    while (~n & 1) { /* Division par Val2(n) (obtention d'un impair) */ 
        n >>= 1;
        nb_iter++;
    };
    old = n >> 1; /* Suppression du bit de parite */

    /* Iterations */
    while (old) {
        iter_impair();
        old = new;
        if (bools.overflow) {
            return 0;
        };
    };

    /* Resultat */
    return nb_iter;
};

int main () {
    for (int j = 1; j <= 100; j++) {
        printf("%d\n", m(j));
    };

    return 0;
};
