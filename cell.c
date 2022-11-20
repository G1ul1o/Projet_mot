//
// Created by giuga on 07/11/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "cell.h"

//fonction qui permet de créer une cellule contenant le nom fléchie et le type du mot (type veut dire Nom,Verbe,SG,PL ...), elle prend en paramètre le mot à ajouter et son type
p_cell CreationCellFlechie(char mot[30],char type[30])
{
    p_cell nouv;
    nouv = (p_cell)malloc(sizeof(t_cell));
    int i=0;
    while(mot[i]!='\0')
    {
        nouv->mot[i]=mot[i];
        i++;
    }
    nouv->mot[i]='\0';
    i=4; //type veut dire Pluriel etc...
    int j=0;
    while(type[i]!='\0')
    {
            nouv->type[j]=type[i];
            j++;
            i++;
    }
    nouv->type[j]='\0';
    nouv->next=NULL;

    return nouv;
}