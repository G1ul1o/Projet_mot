//
// Created by maxim on 12/11/2022.
//

#ifndef PROJET_MOT_PHRASES_H
#define PROJET_MOT_PHRASES_H
#include "tree.h"

char* extractinatorbase(t_tree);
char* miniextractinatorbase(p_node, char*,int);
p_cell forme_flechie(t_tree , char*);

char** temps(p_cell);
char* genre(p_cell);
char** plu_sing(p_cell);
char** personne(p_cell);

char** secateurstring(char*,char);

#endif //PROJET_MOT_PHRASES_H