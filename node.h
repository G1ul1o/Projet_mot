#ifndef PROJET_MOT_NODE_H
#define PROJET_MOT_NODE_H
#include "cell.h"

typedef struct mot
{
    char mot_base[35];
}mot_total;

struct s_node
{
    char value;
    struct s_node *lettres[26];   //appelle le pointeur[le numéro]
    p_cell pointeur;
    int nombre_forme_flechies;
    int fin_mot;
    mot_total *mot_base;
    int nombre_pointeur;
};

typedef struct s_node t_node, *p_node;





p_node createNode(char);

p_node Cherchelettre(p_node,char,int);

p_node Creearbre(p_node,char[35],int,char[35]);

int trouver_mot(p_node pn, char* cara, int numero_lettre);

int compteur(p_node pn, char cara[35]);

p_node trouver_flechie(p_node pn, char mot[25]);



#endif //PROJET_MOT_NODE_H