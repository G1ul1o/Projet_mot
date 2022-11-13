#ifndef PROJET_MOT_NODE_H
#define PROJET_MOT_NODE_H
#include "cell.h"

struct s_node
{
    char value;
    struct s_node *lettres[26];   //appelle le pointeur[le numéro]
    p_cell pointeur;
    int nombre_forme_flechies;
    int fin_mot;
    int nombre_pointeur;
};

typedef struct s_node t_node, *p_node;

p_node createNode(char);

p_node Cherchelettre(p_node,char,int);

p_node Creearbre(p_node,char[35],int);

int trouver_mot(p_node pn, char* cara, int numero_lettre);

int compteur(p_node pn, char cara[35]);



#endif //PROJET_MOT_NODE_H