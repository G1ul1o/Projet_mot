//
// Created by giuga on 07/11/2022.
//

#ifndef PROJET_MOT_CELL_H
#define PROJET_MOT_CELL_H
struct s_cell
{
    char mot[30];
    char type[30];
    struct s_cell *next;
};

typedef struct s_cell t_cell, *p_cell;

struct s2_cell
{
    char mot[30];
    struct s2_cell *next;
};

typedef struct s2_cell t2_cell, *p2_cell;

typedef struct flechie
{
    char mot_flechies[25];
    char type_flechies[50];
} flechies;

p_cell createCellflechie(char [30],char [30]);

p2_cell createCell(char [30]);

#endif //PROJET_MOT_CELL_H
