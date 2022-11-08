//
// Created by giuga on 31/10/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

t_tree CreateEmptyTree()
{
    t_tree arbre;
    for (int i = 0; i < 26; ++i) {
        arbre.root[i]=NULL;
    }

    return arbre;
}

p_node CherchelettreRoot(t_tree pn,char lettre,int i)
{
    t_tree temp;
    temp=pn;
    p_node tempnode;
    if(temp.root[i]==NULL)
    {
        return NULL;
    }
    if(temp.root[i]->value==lettre)
    {
        return temp.root[i];
    }

    if(i+1< temp.nombre_pointeurs)
    {
        tempnode= CherchelettreRoot(pn,lettre,i+1);
        if(tempnode!=NULL)
        {
            return tempnode;
        }
        else
        {
            return NULL;
        }
    }


    return NULL;
}