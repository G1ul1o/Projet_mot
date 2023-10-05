#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "phrase.h"




int main()
{
    t_tree arbre_nom, arbre_ver, arbre_adj, arbre_adv;

    FILE *dicofile = fopen("C:\\Users\\giuga\\CLionProjects\\Projet mot\\dico_10_lignes.txt", "r");


    t_tree arbre_nom,arbre_ver,arbre_adj,arbre_adv,arbre_abr,arbre_int;
    FILE* dicofile= fopen("C:\\Users\\giuga\\CLionProjects\\Projet mot\\dico_10_lignes.txt", "r");
    char flechie[35];
    char base[35];
    char formes[35];
    char type[35];
    int creation_arbrenom=0;
    int creation_arbreadj=0;
    int creation_arbreadv=0;
    int creation_arbreverb=0;
    int creation_arbreabr=0;
    int creation_arbreint=0;

    char flechie[35];
    char base[35];
    char formes[50];
    char type[50];


    int creation_arbrenom = 0;
    int creation_arbreadj = 0;
    int creation_arbreadv = 0;
    int creation_arbreverb = 0;

    int choix = 0,choix2=0;

    //on crée l'arbre
    if (dicofile != NULL)
    {
        while (fscanf(dicofile, "%s\t%s\t%s", flechie, base, formes) !=
               EOF) //EOF pour end of file et \t pour les tabulations et fscanf nous permet de parcourir le fichier ligne par ligne
        {
            for (int j = 0; j < 3; ++j) {
                type[j] = formes[j]; //on récupère le type de notre mot (Nom,Ver,Adv,Adj)
            }
            type[3]='\0';

            //on va ensuite ajouter le mot à l'arbre correspondant à son type
            if (type[0] == 'N')
            {
                if (creation_arbrenom == 0) {
                    arbre_nom = PremierNoeud(base,type);
                    creation_arbrenom++;
                } else {
                    arbre_nom = AjoutNoeudArbre(arbre_nom, base,type);
                }
            } else if (type[0] == 'V') {
                if (creation_arbreverb == 0) {
                    arbre_ver = PremierNoeud(base,type);
                    creation_arbreverb++;
                } else {
                    arbre_ver = AjoutNoeudArbre(arbre_ver, base,type);
                }
            } else if (type[0] == 'A') {
                if (type[2] == 'v') {
                    if (creation_arbreadv == 0) {
                        arbre_adv = PremierNoeud(base,type);
                        creation_arbreadv++;
                    } else {
                        arbre_adv = AjoutNoeudArbre(arbre_adv, base,type);
                    }

                    else
                    {
                        arbre_adv= createTreeFromNode(arbre_adv,base);
                    }
                }
                else if (type[1]=='j')
                {
                    if (creation_arbreadj==0)
                    {
                        arbre_adj=createfromEmptyTreeFromNode(base);

                } else {
                    if (creation_arbreadj == 0) {
                        arbre_adj = PremierNoeud(base,type);

                        creation_arbreadj++;
                    } else {
                        arbre_adj = AjoutNoeudArbre(arbre_adj, base,type);
                    }
                }
                else
                {
                    if (creation_arbreabr==0)
                    {
                        arbre_abr=createfromEmptyTreeFromNode(base);
                        creation_arbreabr++;
                    }
                    else
                    {
                        arbre_abr= createTreeFromNode(arbre_abr,base);
                    }
                }

            }            else if (type[0]=='I')
            {
                if (creation_arbreint==0)
                {
                    arbre_int=createfromEmptyTreeFromNode(base);
                    creation_arbreint++;
                }
                else
                {
                    arbre_int= createTreeFromNode(arbre_int,base);
                }
            }

        }


    }
    fclose(dicofile);


    //on rentre dans le menu
    printf("Bonjours et bienvenue, veuillez choisir ce que vous voulez faire :\n");

    while(choix != 4) //permet de stopper le programme quand le chiffre est saisie
    {
        do
        {
            choix=0;
            choix2=0;
            printf("Que voulez vous faire ?\n"
                   "1 : Verifier si un mot existe (forme basique)\n"
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
                while(choix2 != 4)
                {
                    do {
                        printf("Que voulez vous generer comme phrase ?\n"
                               "1 : Phrase type 1 (nom verbe adjectif nom) ?\n"
                               "2 : Phrase type 2 (nom qui verbe verbe adjectif nom adjectif) ?\n"
                               "3 : Phrase type 3 (nom verbe adverbe adjectif) ?\n"
                               "4 : Quitter\n");

                        scanf("%d", &choix2);
                        if (choix2 == 1) {
                            phrase_modele1(arbre_nom, arbre_ver, arbre_adj);
                        } else if (choix2 == 2) {
                            phrase_modele2(arbre_nom, arbre_ver, arbre_adj);
                        } else if (choix2 == 3) {
                            phrase_modele3(arbre_nom, arbre_ver, arbre_adj, arbre_adv);
                        }
                    } while (choix2 != (1, 2, 3,4));
                }

            }
            else if (choix == 3)
            {
                while(choix2 != 5)
                {
                    do
                    {
                        printf ("Que voulez vous chercher ?\n"
                                "1 : Chercher un nom ?\n"
                                "2 : Chercher un verbe ?\n"
                                "3 : Chercher un adj ?\n"
                                "4 : Chercher un adv ?\n"
                                "5 : Quitter\n");
                        scanf("%d", &choix2);
                        char lemot[35];

                        if(choix2!=5)
                        {
                            printf("Veuillez saisir un mot : \n");
                            scanf("%s", &lemot);
                        }

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
                    }while (choix2 != (1, 2, 3,4,5));
                }
            }
        }while(choix!=(1,2,3,4)); //saisir sécurisée
    }

    return 0;
}
