//
// Created by maxim on 12/11/2022.
//

#ifndef PROJET_MOT_PHRASES_H
#define PROJET_MOT_PHRASES_H
#include "tree.h"

char* extractinatorbase(t_tree); //Récupère un mot sous forme basique
char* miniextractinatorbase(p_node, char*,int); //complémente exctractinatorbase pour la structure p_node
p_cell forme_flechie(t_tree , char*);  // renvoie la structure fléchie d'un mot dans un arbre donné

char** temps(p_cell); // récupère les temps d'une forme fléchie
char* genre(p_cell); // récupère le genre d'une forme fléchie
char** plu_sing(p_cell); // récupère les pluriels/singuliers d'une forme fléchie
char** personne(p_cell); // récupère les personnes d'une forme fléchie

char* type1(t_tree, t_tree, t_tree); // forme le type de phrase : Nom Adjectif Verbe Nom
char* type2(t_tree, t_tree, t_tree); // forme le type de phrase : Nom qui Verbe Verbe Nom Adjectif
char* type3(t_tree, t_tree, t_tree); // forme le type de phrase : Jean-Louis le Adjectif Verbe Nom Adjectif

char** secateurstring(char*,char);
char* concatenation(char*, char*);
p_node conjugaison2(char* phrase_base, t_tree nom, t_tree vb, t_tree adj);

#endif //PROJET_MOT_PHRASES_H