#ifndef PROJET_MOT_PHRASES_H
#define PROJET_MOT_PHRASES_H
#include "tree.h"

char* extractinatorbase(t_tree); //Récupère un mot sous forme basique
char* miniextractinatorbase(p_node, char*,int); //complémente exctractinatorbase pour la structure p_node
p_cell forme_flechie(t_tree , char*);  // renvoie la structure fléchie d'un mot dans un arbre donné


void phrase_modele1(t_tree, t_tree, t_tree); // forme le type de phrase : Nom Adjectif Verbe Nom
void phrase_modele2(t_tree, t_tree, t_tree); // forme le type de phrase : Nom qui Verbe Verbe Nom Adjectif
void phrase_modele3(t_tree, t_tree, t_tree,t_tree); // forme le type de phrase : Jean-Louis le Adjectif Verbe Nom Adjectif


#endif //PROJET_MOT_PHRASES_H
