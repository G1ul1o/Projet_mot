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

t_tree createfromEmptyTreeFromNode(char mot[35])
{
    t_tree ps;
    ps=CreateEmptyTree();
    ps.root[0] = Creearbre(ps.root[0],mot,0);
    ps.nombre_pointeurs=1;
    return ps;
}

t_tree createTreeFromNode(t_tree t,char mot[35])
{
    p_node temp;
    temp= CherchelettreRoot(t,mot[0],0);
    if (temp!=NULL)
    {
        temp= Creearbre(temp,mot,1);
    }
    else
    {
        t.root[t.nombre_pointeurs] = Creearbre(t.root[t.nombre_pointeurs],mot,0);
        t.nombre_pointeurs+=1;
    }

    return t;
}
