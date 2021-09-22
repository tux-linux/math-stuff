/* MIT License
 * Copyright (C) 2021 Nicolas Mailloux
 * See the LICENSE file for details / Voir le fichier LICENSE pour obtenir plus d'information
*/

/*
 * Calculateur produit-somme
 * Marche seulement avec des nombre positifs (pour l'instant)
 * Usage:
 * ./ps <produit> <somme>
 * La réponse renvoyée ressemblera à ceci, pour une invocation de `./ps 24 10`:
 *
 * 6 * 4 = 10
 * 6 + 4 = 10
 *
 * Expérimental. Limite empirique de 100 000.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char * argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Erreur: spécifier les paramètres de la commande.\n");
        fprintf(stderr, "Utilisation: %s <produit> <somme>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    unsigned long produit = strtol(argv[1], NULL, 10);
    unsigned long somme = strtol(argv[2], NULL, 10);
    unsigned long limit = 100000;

    unsigned long n1 = 0;
    unsigned long n2 = 0;
    unsigned long multires;
    unsigned long addires;
    bool passe1 = false;
    bool passe2 = false;
    for(;;) {
        if(getenv("DEBUG") != NULL) {
            printf("n1: %lu, n2: %lu\n", n1, n2);
            multires = n1 * n2;
            addires = n1 + n2;
            printf("multires: %lu\naddires: %lu\n", multires, addires);
            printf("Produit: %lu | Somme: %lu\n", produit, somme);
            printf("\n");
        }
        if(n1 * n2 == produit && n1 + n2 == somme) {
            printf("%lu * %lu = %lu\n", n1, n2, produit);
            printf("%lu + %lu = %lu\n", n1, n2, somme);
            break;
        }
        else {
            if(passe1 == true) {
                if(passe2 == true) {
                    if(n1 >= limit) {
                        n1 = 0;
                        n2++;
                    }
                    else {
                        n1++;
                    }
                }
                else {
                    n1 = 0;
                    n2 = 0;
                    passe2 = true;
                }
            }
            else {
                n1++;
                n2++;
                if(n1 >= limit && n2 >= limit) {
                    passe1 = true;
                }
            }
        }
    }
}
