//
// Created by maxim on 12/11/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "phrases.h"


char* extractinatorbase(t_tree tree){
    srand((unsigned)time(NULL));
    char* mot = (char *)malloc(sizeof (char));

    int nb_enfant = tree.nombre_pointeurs;
    int random= rand()%nb_enfant;
    p_node temp=tree.root[random];
    mot[0]=temp->value;
    mot = miniextractinatorbase(temp, mot, 0);
    return mot;
}

char* miniextractinatorbase(p_node pn, char* mot, int i) {
    int nb_enfant, random;
    if (pn->nombre_pointeur == 0) {
        mot[i]=pn->value;
        mot[i+1]='\0';
        return mot;
    }
    if (pn->nombre_forme_flechies != 0 && pn->nombre_pointeur != 0) {
        int decideur = rand() % 2;
        if (decideur == 0) {
            mot[i]=pn->value;
            return mot;
        } else {
            nb_enfant = pn->nombre_pointeur;
            mot[i] = pn->value;
            random = rand() % nb_enfant;
            pn = pn->lettres[random];
            mot=miniextractinatorbase(pn, mot, i+1);
        }
    }
    else{
        nb_enfant = pn->nombre_pointeur;
        mot[i] = pn->value;
        random = rand() % nb_enfant;
        pn = pn->lettres[random];
        mot=miniextractinatorbase(pn, mot, i+1);
    }
}


p_cell forme_flechie(t_tree tree, char* base){
    p_cell flechies;
    p_node temp;
    for (int j=0; j<tree.nombre_pointeurs;j++){
        if (base[0]==tree.root[j]->value){
            temp=tree.root[j];
        }
    }
    int i=1;
    while (base[i]!='\0'){
        for (int j=0; j<temp->nombre_pointeur;j++){
            if (base[i]==temp->value){
                temp=temp->lettres[j];
                j=0;
            }
        }
    }
    flechies=temp->pointeur;
    return flechies;
}