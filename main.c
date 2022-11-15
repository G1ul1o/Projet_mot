#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "phrases.h"



int main() {
    t_tree arbre_nom, arbre_ver, arbre_adj, arbre_adv;
    FILE *dicofile = fopen("C:\\Users\\maxim\\OneDrive\\Documents\\C\\Projet_mot\\dico_10_lignes.txt", "r");
    char flechie[35];
    char base[35];
    char formes[50];
    char type[50];
    int creation_arbrenom = 0;
    int creation_arbreadj = 0;
    int creation_arbreadv = 0;
    int creation_arbreverb = 0;

    if (dicofile != NULL) {
        while (fscanf(dicofile, "%s\t%s\t%s", flechie, base, formes) !=
               EOF) //EOF pour end of file et \t pour les tabulations
        {
            for (int j = 0; j < 3; ++j) {
                type[j] = formes[j];
            }
            if (type[0] == 'N') {
                if (creation_arbrenom == 0) {
                    arbre_nom = createfromEmptyTreeFromNode(base);
                    creation_arbrenom++;
                } else {
                    arbre_nom = createTreeFromNode(arbre_nom, base);
                }
            } else if (type[0] == 'V') {
                if (creation_arbreverb == 0) {
                    arbre_ver = createfromEmptyTreeFromNode(base);
                    creation_arbreverb++;
                } else {
                    arbre_ver = createTreeFromNode(arbre_ver, base);
                }
            } else if (type[0] == 'A') {
                if (type[2] == 'v') {
                    if (creation_arbreadv == 0) {
                        arbre_adv = createfromEmptyTreeFromNode(base);
                        creation_arbreadv++;
                    } else {
                        arbre_adv = createTreeFromNode(arbre_adv, base);
                    }
                } else {
                    if (creation_arbreadj == 0) {
                        arbre_adj = createfromEmptyTreeFromNode(base);
                        creation_arbreadj++;
                    } else {
                        arbre_adj = createTreeFromNode(arbre_adj, base);
                    }
                }

            }



            //printf("%s\n",base);
        }

    }
    fclose(dicofile);

    /*int choix = 0;
    printf("Bonjours et bienvenue, veuillez choisir ce que vous voulez faire :\n");
    while(choix != 4) //permet de stopper le programme quand le chiffre est saisie
    {
        do
        {
            printf("Que voulez vous faire ?\n"
                   "1 : Verifier si un mot existe\n"
                   "2 : Generer une phrase\n"
                   "3 : Chercher une forme flechie\n"
                   "4 : Quitter\n");
            scanf("%d", &choix);
            choix=1;
            if (choix == 1) {
                printf("Veuillez saisir un mot : \n");
                char lemot[35];
                scanf("%s", &lemot); //on demande à l'utilisateur de saisir un mot
                type_mot(lemot, arbre_nom, arbre_adj, arbre_ver, arbre_adv); //on fait entrer le mot saisie dans la fonction

            }
            else if (choix == 2)
                printf("On sait pas encore faire ce truc, deso pas deso\n");
            else if (choix == 3)
                printf("On sait pas encore faire ce truc, deso pas deso\n");
        }while(choix!=(1,2,3,4)); //saisir sécurisée
    }*/

    /*char* basique = extractinatorbase(arbre_ver);
    p_cell flechies = forme_flechie(arbre_ver, basique);
    printf("\n%s -> %s",flechies->mot, flechies->type);
    char** temp= temps(flechies);*/

    char *info = "PPas+Mas+PL";
    char **all_type;
    char **all_per = (char **) malloc(sizeof(char *));

    all_type = secateurstring(info, ':');
    int i = 0;
    int cpt = 0;
    while (all_type[i][0] != '~') {
        char **temp;
        temp = secateurstring(all_type[i], '+');
        if (temp[0] == "PPas") {
            all_per[i] = temp[3];
        } else
            all_per[i] = temp[2];
        i++;
    }
    all_per[i] = "~";  //probleme d'indentation qqpart : all_per[0]="~"
    i = 0;
    while (all_per[i][0] != '~') {
        printf("\n%s",all_per[i]);
        i++;
    }
    return 0;
}