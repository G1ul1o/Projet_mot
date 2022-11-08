//
// Created by giuga on 07/11/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include "node.h"

p_node createNode(char lettre)
{
    p_node nouv;

    nouv = (p_node)malloc(sizeof(t_node));
    nouv->value = lettre;
    nouv->lettres[0]=NULL;
    nouv->nombre_pointeur=0;
    nouv->pointeur=NULL;
    nouv->nombre_forme_flechies=0;
    return nouv;
}

p_node Cherchelettre(p_node pn,char lettre,int i)
{
    p_node temp;
    temp=pn;
    if(pn->lettres[i]==NULL)
    {
        return NULL;
    }
    if(pn->lettres[i]->value==lettre)
    {
        return pn->lettres[i] ;
    }

    if(i+1< pn->nombre_pointeur)
    {
        temp= Cherchelettre(pn->lettres[i+1],lettre,i+1);
        if(temp!=NULL)
        {
            return temp;
        }
        else
        {
            return NULL;
        }
    }


    return NULL;
}

