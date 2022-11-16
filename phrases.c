//
// Created by giuga on 16/11/2022.
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
    if (pn->fin_mot != 0) {
        mot[i]=pn->value;
        mot[i+1]='\0';
        return mot;
    }
    if (pn->fin_mot != 0 && pn->nombre_pointeur != 0) {
        int decideur = rand() % 2;
        if (decideur == 0) {
            mot[i]=pn->value;
            mot[i+1]='\0';
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
    //printf("mot a test plusing %s\n",forme->mot);
    char *info = forme->type;
    //printf("type plu_sing %s\n",info);
    //printf("plu_sing debut\n");
    char **all_type=(char **) malloc(sizeof(char *));
    char **all_plu = (char **) malloc(sizeof(char *));
    char **temp=NULL;

    all_type = secateurstring(info, ':');
    //printf("all_type %s\n",all_type[0]);

    int i = 0;
    int cpt = 0;
    while (all_type[i][0] != '~')
    {
        //printf("plu_sing debut boucle\n");


        temp = secateurstring(all_type[i], '+');
        //printf("temp apres secateur %s\n",temp[1]);

        if (temp[0][2] == 'a') {
            all_plu[i] = temp[2];
        }else
            all_plu[i] = temp[1];
        //printf("char all_type fini %c\n",all_type[i][0]);
        i++;
        //printf("plu_sing fin boucle\n");

    }
    all_plu[i]="~";
    //printf("plu_sing fin\n");
    i=0;
    while (all_plu[i][0]!='~')
        //printf("%s\n",all_plu[i++]);
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
        if (temp[0][3] == 's') {
            all_per[i] = "no_pers";
        } else
            all_per[i] = temp[2];
        i++;
    }
    all_per[i] = "~";
    return all_per;
}


char* genre(p_cell forme){
    char *info = forme->type;
    char * genre = (char *) malloc(sizeof(char ));
    int i = 0;
    int cpt = 0;
    while (info[i] != '\0') {
        char **temp;
        temp = secateurstring(info, '+');
        if (temp[0][3] == 's') {
            genre = temp[1];
        } else
            genre = temp[0];
        i++;
    }
    return genre;
}


char* type1(t_tree nom, t_tree vb, t_tree adj) {
    srand((unsigned)time(NULL));
    char *nom1=(char *) malloc(sizeof(char ));
    char *nom2=(char *) malloc(sizeof(char ));
    char *verbe=(char *) malloc(sizeof(char ));
    char *adjectif=(char *) malloc(sizeof(char ));
    char *phrase = NULL;
    nom1 = extractinatorbase(nom);
    nom2 = extractinatorbase(nom);
    verbe = extractinatorbase(vb);
    adjectif = extractinatorbase(adj);
    p_cell verbefl = forme_flechie(vb, verbe);
    p_cell adjectif_fl = forme_flechie(adj, adjectif);
    p_cell nom1fl = forme_flechie(nom, nom1);
    p_cell nom2fl = forme_flechie(nom, nom2);


    int i = 1;
    if (nom1fl!=NULL){
        while (i != 0) {
            if (nom1fl->next==NULL) {
                i = 0;
            }else {
                nom1fl = nom1fl->next;
                i = rand() % 2;
            }
        }
        nom1 = nom1fl->mot;
    }
    i=1;
    if (nom2fl!=NULL){
        while (i != 0) {
            if (nom1fl->next==NULL) {
                i = 0;
            }else {
                nom1fl = nom1fl->next;
                i = rand() % 2;
            }
        }
        nom2 = nom2fl->mot;
    }

    char** nb_nom1=plu_sing(nom1fl);
    char* genre_nom1= genre(nom1fl);
    char** nb_nom2=plu_sing(nom2fl);
    char* genre_nom2= genre(nom2fl);

    char** nb_verbe=(char **) malloc(sizeof(char*));
    char** per_verbe=(char**) malloc(sizeof(char*));
    char* temp=(char *) malloc(sizeof(char ));
    verbe="~";

    do{
        //printf("pipi\n");
        nb_verbe= plu_sing(verbefl);
        //printf("%s\n",verbefl->mot);
        per_verbe= personne(verbefl);
        //printf("dodo\n");

        int j=0;
        while (nb_verbe[j][0]!='~')
        {

            ////printf("%c\n",nb_verbe[1][0]);
            if ((nb_verbe[j][0]==nb_nom1[0][0]) && (per_verbe[j][1]=='3')){
                temp=verbefl->mot;
                //printf("%c\n",nb_verbe[j][0]);
                i = rand() % 3;
                if (i!=0)
                {
                    verbe=verbefl->mot;
                    //printf("%s\n",verbe);

                }
            }
            //printf("pas dans le 3\n");
            j++;
            //printf("crash \n");
        }
        //printf("caca\n");
        if (verbefl->next!=NULL) {
            //printf("verbfl next %s\n", verbefl->next->mot);
        } else
            //printf("NULLLLLLLL\n");
        verbefl=verbefl->next;
        //printf("caca2\n");
    } while (verbefl!=NULL);

    //printf("mange t mort\n");
    if (verbe[0]=='~')
        verbe=temp;

    char* genre_adj;
    char** nb_adj;
    do{
        genre_adj= genre(adjectif_fl);
        nb_adj= plu_sing(adjectif_fl);
        if ((genre_adj[0]==genre_nom1[0]) && (nb_adj[0][0]==nb_nom1[0][0])){
            adjectif=adjectif_fl->mot;
        }
        adjectif_fl=adjectif_fl->next;
    } while (adjectif_fl->next!=NULL);
    //printf("adj crée\n");


    if (nb_nom1[0][0]=='P'){
        phrase=concatenation("Les", nom1);
    }else if (genre_nom1[0]=='M'){
        phrase=concatenation("Le", nom1);
    }else if (genre_nom1[0]=='F'){
        phrase=concatenation("La", nom1);
    }
    phrase= concatenation(phrase,adjectif);
    //printf("%s\n",phrase);
    phrase= concatenation(phrase, verbe);
    //printf("%s\n",phrase);

    if (nb_nom2[0][0]=='P'){
        phrase=concatenation(phrase, "les");
        phrase=concatenation(phrase, nom2);
    }else if (genre_nom2[0]=='M'){
        phrase=concatenation(phrase, "le");
        phrase=concatenation(phrase, nom2);
    }else if (genre_nom2[0]=='F'){
        phrase=concatenation(phrase, "la");
        phrase=concatenation(phrase, nom2);
    }


    return phrase;
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
    temp[j]='\0';
    output[cpt]=temp;
    cpt++;
    output[cpt]="~";
    return output;
}

char* concatenation(char* bout1, char* bout2){
    int i;
    char *output = (char *)malloc(sizeof (char));

    for (i=0;bout1[i]!='\0';i++){
        output[i]=bout1[i];
    }
    output[i]=' ';
    i++;
    for (int j=0;bout2[j]!='\0';j++, i++){
        output[i]=bout2[j];
    }
    output[i]='\0';

    return output;
}