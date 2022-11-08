//
// Created by giuga on 31/10/2022.
//

#ifndef PROJET_MOT_TREE_H
#define PROJET_MOT_TREE_H

#include "node.h"

typedef struct s_tree
{
    p_node root[26];
    int nombre_pointeurs;
} t_tree, *p_tree;

t_tree CreateEmptyTree();

p_node CherchelettreRoot(t_tree,char,int);

t_tree createfromEmptyTreeFromNode(char[35]);

t_tree createTreeFromNode(t_tree,char[35]);
#endif //PROJET_MOT_TREE_H