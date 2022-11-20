#ifndef PROJET_MOT_TREE_H
#define PROJET_MOT_TREE_H

#include "node.h"

typedef struct s_tree
{
    p_node root[26];
    int nombre_pointeurs;
} t_tree, *p_tree;

t_tree CreeArbrevide();

p_node CherchelettreRoot(t_tree,char,int);

t_tree PremierNoeud(char[35],char[35]);

t_tree AjoutNoeudArbre(t_tree,char[35],char[35]);

void recherche_flechie(t_tree arbre, char mot[25]);

void type_mot(char lemot[35], t_tree arbre_nom, t_tree arbre_adj, t_tree arbre_ver, t_tree arbre_adv);

#endif //PROJET_MOT_TREE_H
