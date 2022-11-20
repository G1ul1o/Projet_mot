//
// Created by giuga on 07/11/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "cell.h"

p_cell createCellflechie(char mot[30],char type[50])
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

p2_cell createCell(char mot[30])
{
    p2_cell nouv;
    nouv = (p2_cell)malloc(sizeof(t2_cell));
    int i=0;
    while(mot[i]!='\0')
    {
        nouv->mot[i]=mot[i];
        i++;
    }
    nouv->mot[i]='\0';
    nouv->next=NULL;

    return nouv;
}