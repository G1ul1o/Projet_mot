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
    p_node temp,temp2;
    int i=0;
    temp = CherchelettreRoot(tree,base[i],i);
    i++;
    while(base[i]!='\0'){
        temp2 = Cherchelettre(temp, base[i],0);
        if (temp2==NULL){
            i++;
        }else
            temp=temp2;
    }
    flechies=temp->pointeur;
    return flechies;
}

char** temps (p_cell forme){
    char* info=forme->type;
    char** all_type;
    char** all_temps=(char **)malloc(sizeof (char*));

    all_type= secateurstring(info,':');
    int i=0;
    int cpt=0;
    while(all_type[i][0]!='~'){
        char** temp;
        temp= secateurstring(all_type[i],'+');
        all_temps[i]=temp[0];
        i++;
    }
    all_temps[i]="~";
    return all_temps;
}

char** plu_sing(p_cell forme) {
    char *info = forme->type;
    char **all_type;
    char **all_plu = (char **) malloc(sizeof(char *));

    all_type = secateurstring(info, ':');
    int i = 0;
    int cpt = 0;
    while (all_type[i][0] != '~') {
        char **temp;
        temp = secateurstring(all_type[i], '+');
        if (temp[0]=="PPas") {
            all_plu[i] = temp[2];
        }else
            all_plu[i] = temp[1];
        i++;
    }
    all_plu[i]="~";
    return all_plu;
}

char** personne(p_cell forme){
    char *info = forme->type;
    char **all_type;
    char **all_per = (char **) malloc(sizeof(char *));

    all_type = secateurstring(info, ':');
    int i = 0;
    int cpt = 0;
    while (all_type[i][0] != '~') {
        char **temp;
        temp = secateurstring(all_type[i], '+');
        if (temp[0]=="PPas") {
            all_per[i] = temp[3];
        }else
            all_per[i] = temp[2];
        i++;
    }
    all_per[i]="~";
    return all_per;
}


char** secateurstring(char* string,char delim){
    char** output=(char **)malloc(sizeof (char*));
    char* temp= (char *)malloc(sizeof (char));
    int i=0;
    int j=0;
    int cpt=0;
    while(string[i]!= '\0')
    {
        if (string[i] == delim){
            temp[j]='\0';
            output[cpt]=temp;
            temp= (char *)malloc(sizeof (char));
            j=0;
            cpt++;
        }else {
            temp[j]=string[i];
            j++;
        }
        i++;
    }
    if (cpt==0){
        temp[j]='\0';
        output[cpt]=temp;
        temp= (char *)malloc(sizeof (char));
        j=0;
        cpt++;
    }
    output[cpt]="~";
    return output;
}