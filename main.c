#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "phrase.h"




int main()
{
    t_tree arbre_nom, arbre_ver, arbre_adj, arbre_adv;

    FILE *dicofile = fopen("C:\\Users\\giuga\\CLionProjects\\Projet mot\\dico_10_lignes.txt", "r");

    char flechie[35];
    char base[35];
    char formes[50];
    char type[50];

    int creation_arbrenom = 0;
    int creation_arbreadj = 0;
    int creation_arbreadv = 0;
    int creation_arbreverb = 0;

    if (dicofile != NULL)
    {
        while (fscanf(dicofile, "%s\t%s\t%s", flechie, base, formes) !=
               EOF) //EOF pour end of file et \t pour les tabulations
            // char *base_arbre=(char*)malloc(35*sizeof(char));
        {
            for (int j = 0; j < 3; ++j) {
                type[j] = formes[j];
            }
            type[3]='\0';
            if (type[0] == 'N') {
                if (creation_arbrenom == 0) {
                    arbre_nom = createfromEmptyTreeFromNode(base,type);
                    creation_arbrenom++;
                } else {
                    arbre_nom = createTreeFromNode(arbre_nom, base,type);
                }
            } else if (type[0] == 'V') {
                if (creation_arbreverb == 0) {
                    arbre_ver = createfromEmptyTreeFromNode(base,type);
                    creation_arbreverb++;
                } else {
                    arbre_ver = createTreeFromNode(arbre_ver, base,type);
                }
            } else if (type[0] == 'A') {
                if (type[2] == 'v') {
                    if (creation_arbreadv == 0) {
                        arbre_adv = createfromEmptyTreeFromNode(base,type);
                        creation_arbreadv++;
                    } else {
                        arbre_adv = createTreeFromNode(arbre_adv, base,type);
                    }
                } else {
                    if (creation_arbreadj == 0) {
                        arbre_adj = createfromEmptyTreeFromNode(base,type);
                        creation_arbreadj++;
                    } else {
                        arbre_adj = createTreeFromNode(arbre_adj, base,type);
                    }
                }

            }
            //printf("%s\n",base);
        }

    }
    fclose(dicofile);

    int choix = 0,choix2=0;

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
            if (choix == 1) {
                printf("Veuillez saisir un mot (sous forme basique): \n");
                char lemot[35];
                scanf("%s", &lemot); //on demande à l'utilisateur de saisir un mot
                type_mot(lemot, arbre_nom, arbre_adj, arbre_ver, arbre_adv); //on fait entrer le mot saisie dans la fonction
            }
            else if (choix == 2)
            {
                do {
                    printf ("Que voulez vous faire ?\n"
                            "1 : Phrase type 1 (nom verbe adjectif nom) ?\n"
                            "2 : Phrase type 2 (nom qui verbe verbe adjectif nom adjectif) ?\n"
                            "3 : Phrase type 3 (nom verbe adverbe adjectif) ?\n"
                            "4 : Quitter\n");

                    scanf("%d", &choix2);
                    if(choix2==1)
                    {
                        type1(arbre_nom,arbre_ver,arbre_adj);
                    }
                    else if (choix2==2)
                    {
                        type2(arbre_nom,arbre_ver,arbre_adj);
                    }
                    else if (choix2==3)
                    {
                        type3(arbre_nom,arbre_ver,arbre_adj,arbre_adv);
                    }
                } while (choix2!=(1,2,3));


            }
            else if (choix == 3)
            {
                printf ("Que voulez vous faire ?\n"
                       "1 : Chercher un nom ?\n"
                       "2 : Chercher un verbe ?\n"
                       "3 : Chercher un adj ?\n"
                       "4 : Chercher un adv ?\n"
                       "5 : Quitter\n");

                scanf("%d", &choix2);

                char lemot[35];
                printf("Veuillez saisir un mot : \n");
                scanf("%s", &lemot);

                if(choix2==1)
                {
                    recherche_flechie(arbre_nom,lemot);
                }
                else if (choix2==2)
                {
                    recherche_flechie(arbre_ver,lemot);
                }
                else if (choix2==3)
                {
                    recherche_flechie(arbre_adj,lemot);
                }
                else if(choix2==4)
                {
                    recherche_flechie(arbre_adv, lemot);
                }

            }
        }while(choix!=(1,2,3,4)); //saisir sécurisée
    }

    return 0;
}