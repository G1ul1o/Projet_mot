//
// Created by giuga on 07/11/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

//Crée une liste fléchie vide, ne prends rien en paramètre
t_std_list CreeListeFlechie()
{
    t_std_list newlist;
    newlist.head =NULL;
    return newlist;
}

//Ajoute une cellule en tête de liste, prends en paramètre le mot, la liste à laquelle on va ajouter la cellule et le type du mot
t_std_list ajoutlisteflechie(t_std_list liste_mot,char mot[30],char type[30])
{
    p_cell nouv= CreationCellFlechie(mot,type);
    nouv->next = liste_mot.head;
    liste_mot.head=nouv;
    return liste_mot;
}