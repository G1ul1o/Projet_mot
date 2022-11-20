//
// Created by giuga on 07/11/2022.
//

#ifndef PROJET_MOT_LISTE_H
#define PROJET_MOT_LISTE_H
#include "cell.h"

typedef struct s_std_list
{
    p_cell head;
} t_std_list;


t_std_list CreeListeFlechie();



t_std_list ajoutlisteflechie(t_std_list,char [30],char [30]);

#endif //PROJET_MOT_LISTE_H
