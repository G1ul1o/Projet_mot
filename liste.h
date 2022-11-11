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

typedef struct s_std_list2
{
    p2_cell head;
} t_std_list2;

t_std_list createt_std_listflechie();

t_std_list2 createt_std_list2();

void showlist(t_std_list2);

t_std_list ajoutlisteflechie(t_std_list,char [30],char [30]);

t_std_list2 ajoutliste(t_std_list2,char[30]);

t_std_list2 recuperation_de_base();
#endif //PROJET_MOT_LISTE_H
