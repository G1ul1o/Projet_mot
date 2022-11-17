//
// Created by giuga on 07/11/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

t_std_list createt_std_listflechie()
{
    t_std_list newlist;
    newlist.head =NULL;
    return newlist;
}

t_std_list2 createt_std_list2()
{
    t_std_list2 newlist;
    newlist.head =NULL;
    return newlist;
}

void showlist(t_std_list2 liste_mot)
{
    p2_cell tmp;
    tmp = liste_mot.head;
    if (tmp != NULL) {
        while (tmp->next != NULL) {
            int i=0;
            while(tmp->mot[i]!='\0')
            {
                printf("%c", tmp->mot[i]);
                i++;
            }
            printf("\n");
            tmp = tmp->next;
        }
        printf("%s\n", tmp->mot);
    }
}

t_std_list ajoutlisteflechie(t_std_list liste_mot,char mot[30],char type[50])
{
    p_cell nouv= createCellflechie(mot,type);
    nouv->next = liste_mot.head;
    liste_mot.head=nouv;
    return liste_mot;
}

t_std_list2 ajoutliste(t_std_list2 liste_mot,char mot[30])
{
    p2_cell nouv= createCell(mot);
    nouv->next = liste_mot.head;
    liste_mot.head=nouv;
    return liste_mot;
}

t_std_list2 recuperation_de_base()
{
    t_std_list2 liste_mot;
    liste_mot= createt_std_list2();
    FILE* dicofile= fopen("C:\\Users\\giuga\\CLionProjects\\untitled9\\dico_10_lignes.txt", "r");
    char flechie[35];
    char base[35];
    char formes[35];
    p2_cell nouv;


    int i=0;

    if (dicofile != NULL)
    {

        while(fscanf(dicofile,"%s\t%s\t%s", flechie,base,formes) != EOF) //EOF pour end of file et \t pour les tabulations
        {
            liste_mot=ajoutliste(liste_mot,base);
            printf("%s\n",base);
        }
    }
    fclose(dicofile);
    return liste_mot;
}