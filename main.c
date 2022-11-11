#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

int main()
{

    t_tree arbre_nom,arbre_ver,arbre_adj,arbre_adv;
    FILE* dicofile= fopen("C:\\Users\\giuga\\CLionProjects\\Projet mot\\dico_10_lignes.txt", "r");
    char flechie[35];
    char base[35];
    char formes[35];
    char type[35];
    int creation_arbrenom=0;
    int creation_arbreadj=0;
    int creation_arbreadv=0;
    int creation_arbreverb=0;

    if (dicofile != NULL)
    {

        while(fscanf(dicofile,"%s\t%s\t%s", flechie,base,formes) != EOF) //EOF pour end of file et \t pour les tabulations
        {
            for (int j = 0; j < 3; ++j)
            {
                type[j]=formes[j];
            }
            if (type[0]=='N')
            {
                if (creation_arbrenom==0)
                {
                    arbre_nom=createfromEmptyTreeFromNode(base);
                    creation_arbrenom++;
                }
                else
                {
                    arbre_nom= createTreeFromNode(arbre_nom,base);
                }
            }
            else if (type[0]=='V')
            {
                if (creation_arbreverb==0)
                {
                    arbre_ver=createfromEmptyTreeFromNode(base);
                    creation_arbreverb++;
                }
                else
                {
                    arbre_ver= createTreeFromNode(arbre_ver,base);
                }
            }
            else if (type[0]=='A')
            {
                if (type[1]=='v')
                {
                    if (creation_arbreadv==0)
                    {
                        arbre_adv=createfromEmptyTreeFromNode(base);
                        creation_arbreadv++;
                    }
                    else
                    {
                        arbre_adv= createTreeFromNode(arbre_adv,base);
                    }
                }
                else
                {
                    if (creation_arbreadj==0)
                    {
                        arbre_adj=createfromEmptyTreeFromNode(base);
                        creation_arbreadj++;
                    }
                    else
                    {
                        arbre_adj= createTreeFromNode(arbre_adj,base);
                    }
                }

            }



            printf("%s\n",base);
        }
    }
    fclose(dicofile);
    return 0;
}