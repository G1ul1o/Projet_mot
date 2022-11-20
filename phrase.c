//
// Created by giuga on 16/11/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "phrase.h"
#include "liste.h"

char* extractinatorbase(t_tree tree){
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

    if (pn->fin_mot != 0)
    {
        mot[i]=pn->value;
        mot[i+1]='\0';
        return mot;
    }

    if (pn->fin_mot != 0 && pn->nombre_pointeur != 0)
    {
        int decideur = rand() % 2;

        if (decideur == 0)

        {
            mot[i]=pn->value;
            mot[i+1]='\0';
            return mot;
        }

        else
        {
            nb_enfant = pn->nombre_pointeur;
            mot[i] = pn->value;
            random = rand() % nb_enfant;
            pn = pn->lettres[random];
            mot=miniextractinatorbase(pn, mot, i+1);
        }
    }

    else

    {
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
        if (temp2==NULL)
        {
            i++;
        }
        else
        {
            temp=temp2;
            i++;
        }
    }
    flechies=temp->pointeur;
    return flechies;
}


void type1(t_tree nom, t_tree vb, t_tree adj)
{
    srand((unsigned) time(NULL));
    char temp_conjugaison[4];
    char temp_nombre[3];
    char *nom1=(char *) malloc(35*sizeof(char ));
    char *nom2=(char *) malloc(35*sizeof(char ));
    char *verbe=(char *) malloc(35*sizeof(char ));
    char *adjectif=(char *) malloc(35*sizeof(char ));
    char *phrase = NULL;
    char *type_nom1=(char *) malloc(50*sizeof(char ));
    char *type_nom2=(char *) malloc(50*sizeof(char ));
    nom1 = extractinatorbase(nom);
    nom2 = extractinatorbase(nom);
    verbe = extractinatorbase(vb);
    adjectif = extractinatorbase(adj);
    p_cell temp;
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
        type_nom1 = nom1fl->type;
    }

    i=1;

    if (nom2fl!=NULL)
    {
        while (i != 0)
        {
            if (nom1fl->next==NULL)
            {
                i = 0;
            }
            else
            {
                nom1fl = nom1fl->next;
                i = rand() % 2;
            }
        }
        nom2 = nom2fl->mot;
        type_nom2=nom2fl->type;
    }

    int j=0,x=0;

    for ( i = 0; type_nom1[i]!='\0' ; i++)
    {
        if(type_nom1[i]!='+')
        {
            if(i<=2)
            {
                temp_conjugaison[j]=type_nom1[i];
                j++;
            }
            else
            {
                temp_conjugaison[i]='\0';
                temp_nombre[x]=type_nom1[i];
                x++;
            }
        }
    }
    temp_nombre[x]='\0';


    t_std_list forme_flechie_verb;
    forme_flechie_verb.head=NULL;
    p_cell tmp = NULL;
    int premier_trouve=0,compteur_ver=0;

    while(compteur_ver==0)
    {
        temp=verbefl;
        while(temp!=NULL)
        {
            for ( i = 0;temp->type[i]!='\0' ; i++)
            {

                if(temp->type[i]==temp_nombre[0])
                {
                    if(temp->type[i+1]==temp_nombre[1])
                    {
                        for ( x = 0;temp->type[x]!='\0' ; x++)
                        {
                            if(temp->type[x]=='3')
                            {
                                if(premier_trouve==0)
                                {
                                    forme_flechie_verb.head=temp;
                                    tmp=forme_flechie_verb.head;
                                    forme_flechie_verb.head->next=NULL;
                                    tmp->next=NULL;
                                    premier_trouve=1;
                                    compteur_ver+=1;
                                }
                                else
                                {
                                    tmp->next=temp;
                                    tmp=tmp->next;
                                    tmp->next=NULL;
                                    compteur_ver+=1;
                                }

                            }
                        }
                    }
                }
            }
            temp=temp->next;
        }

        if(compteur_ver==0)
        {
            verbe = extractinatorbase(vb);
            verbefl = forme_flechie(vb, verbe);
        }
    }

    t_std_list forme_flechie_adj;
    forme_flechie_adj.head=NULL;
    premier_trouve=0;
    int ajoutinvariable=0;
    int compteur_adj=0;

    while(compteur_adj==0) {

        temp = adjectif_fl;

        while (temp != NULL)
        {
            for (i = 0; temp->type[i] != '\0'; i++) {

                if ((temp->type[i] == temp_nombre[0]) || (temp->type[i] == 'I')) {
                    if (temp->type[i + 1] == temp_nombre[1] || (temp->type[i + 1] == 'n')) {
                        for (x = 0; temp->type[x] != '\0'; x++) {
                            if (temp->type[x] == temp_conjugaison[0]) {
                                if (temp->type[x + 1] == temp_conjugaison[1]) {
                                    if (premier_trouve == 0) {
                                        forme_flechie_adj.head = temp;
                                        tmp = forme_flechie_adj.head;
                                        forme_flechie_adj.head->next = NULL;
                                        tmp->next = NULL;
                                        premier_trouve = 1;
                                        compteur_adj += 1;
                                    } else {
                                        tmp->next = temp;
                                        tmp = tmp->next;
                                        tmp->next = NULL;
                                        compteur_adj += 1;
                                    }
                                }
                            } else if (temp->type[i + 2] == 'v' && ajoutinvariable == 0) {
                                if (premier_trouve == 0) {
                                    forme_flechie_adj.head = temp;
                                    tmp = forme_flechie_adj.head;
                                    forme_flechie_adj.head->next = NULL;
                                    tmp->next = NULL;
                                    premier_trouve = 1;
                                    compteur_adj += 1;
                                } else {
                                    tmp->next = temp;
                                    tmp = tmp->next;
                                    tmp->next = NULL;
                                    compteur_adj += 1;
                                }
                                ajoutinvariable = 1;
                            }
                        }
                    }
                }
            }
            temp = temp->next;
        }
        if (compteur_adj == 0) {
            adjectif = extractinatorbase(adj);
            adjectif_fl = forme_flechie(adj, adjectif);
        }
    }

    if(compteur_ver==1)
    {

        if(compteur_adj==1)
        {
            printf("%s %s %s %s\n",nom1,forme_flechie_verb.head->mot,forme_flechie_adj.head->mot,nom2);
            return;
        }
        else
        {
            tmp=forme_flechie_adj.head;
            int y=rand()%compteur_adj;
            for (int k = 0; k < y; k++)
            {
                tmp=tmp->next;
            }
            printf("%s %s %s %s\n",nom1,forme_flechie_verb.head->mot,tmp->mot,nom2);
            return;
        }
    }
    else if(compteur_adj==1)
    {
        tmp=forme_flechie_verb.head;
        int y=rand()%compteur_ver;
        for (int k = 0; k < y; k++)
        {
            tmp=tmp->next;
        }
        printf("%s %s %s %s\n",nom1,tmp->mot,forme_flechie_adj.head->mot,nom2);
        return;
    }
    else
    {
        tmp=forme_flechie_verb.head;
        int y=rand()%compteur_ver;
        for (int k = 0; k < y; k++)
        {
            tmp=tmp->next;
        }

        p_cell tmp2=forme_flechie_adj.head;
        int r=rand()%compteur_adj;
        for (int k = 0; k < r; k++)
        {
            tmp2=tmp2->next;
        }
        printf("%s %s %s %s\n",nom1,tmp->mot,tmp2->mot,nom2);
    }
}

void type2(t_tree nom, t_tree vb, t_tree adj)
{
    char temp_conjugaison[4];
    char temp_nombre[3];
    char temp_conjugaison_mot2[4];
    char temp_nombre_mot2[3];
    char *nom1=(char *) malloc(35*sizeof(char ));
    char *nom2=(char *) malloc(35*sizeof(char ));
    char *verbe=(char *) malloc(35*sizeof(char ));
    char *verbe2=(char *) malloc(35*sizeof(char ));
    char *adjectif=(char *) malloc(35*sizeof(char ));
    char *adjectif2=(char *) malloc(35*sizeof(char ));
    char *type_nom1=(char *) malloc(50*sizeof(char ));
    char *type_nom2=(char *) malloc(50*sizeof(char ));
    nom1 = extractinatorbase(nom);
    nom2 = extractinatorbase(nom);
    verbe = extractinatorbase(vb);
    verbe2 = extractinatorbase(vb);
    adjectif = extractinatorbase(adj);
    adjectif2 = extractinatorbase(adj);
    p_cell temp;
    p_cell verbefl = forme_flechie(vb, verbe);
    p_cell verbefl2 = forme_flechie(vb, verbe2);
    p_cell adjectif_fl = forme_flechie(adj, adjectif);
    p_cell adjectif_fl2 = forme_flechie(adj, adjectif2);
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
        type_nom1 = nom1fl->type;
    }

    i=1;

    if (nom2fl!=NULL)
    {
        while (i != 0)
        {
            if (nom1fl->next==NULL)
            {
                i = 0;
            }
            else
            {
                nom1fl = nom1fl->next;
                i = rand() % 2;
            }
        }
        nom2 = nom2fl->mot;
        type_nom2=nom2fl->type;
    }

    int j=0,x=0;

    for ( i = 0; type_nom1[i]!='\0' ; i++)
    {
        if(type_nom1[i]!='+')
        {
            if(i<=2)
            {
                temp_conjugaison[j]=type_nom1[i];
                j++;
            }
            else
            {
                temp_conjugaison[i]='\0';
                temp_nombre[x]=type_nom1[i];
                x++;
            }
        }
    }
    temp_nombre[x]='\0';
    j=0;
    x=0;
    for ( i = 0; type_nom2[i]!='\0' ; i++)
    {
        if(type_nom2[i]!='+')
        {
            if(i<=2)
            {
                temp_conjugaison_mot2[j]=type_nom2[i];
                j++;
            }
            else
            {
                temp_conjugaison_mot2[j]='\0';
                temp_nombre_mot2[x]=type_nom2[i];
                x++;
            }
        }
    }
    temp_nombre_mot2[x]='\0';

    temp=verbefl;
    t_std_list forme_flechie_verb;
    forme_flechie_verb.head=NULL;
    p_cell tmp = NULL;
    int premier_trouve=0,compteur_ver=0;

    while(compteur_ver==0)
    {
        temp=verbefl;
        while(temp!=NULL)
        {
            for ( i = 0;temp->type[i]!='\0' ; i++)
            {

                if(temp->type[i]==temp_nombre[0])
                {
                    if(temp->type[i+1]==temp_nombre[1])
                    {
                        for ( x = 0;temp->type[x]!='\0' ; x++)
                        {
                            if(temp->type[x]=='3')
                            {
                                if(premier_trouve==0)
                                {
                                    forme_flechie_verb.head=temp;
                                    tmp=forme_flechie_verb.head;
                                    forme_flechie_verb.head->next=NULL;
                                    tmp->next=NULL;
                                    premier_trouve=1;
                                    compteur_ver+=1;
                                }
                                else
                                {
                                    tmp->next=temp;
                                    tmp=tmp->next;
                                    tmp->next=NULL;
                                    compteur_ver+=1;
                                }

                            }
                        }
                    }
                }
            }
            temp=temp->next;
        }

        if(compteur_ver==0)
        {
            verbe = extractinatorbase(vb);
            verbefl = forme_flechie(vb, verbe);
        }
    }

    temp=verbefl2;
    t_std_list forme_flechie_verb2;
    forme_flechie_verb2.head=NULL;
    tmp = NULL;
    premier_trouve=0;
    int compteur_ver2=0;
    int ajouter=0;

    while(compteur_ver2==0)
    {
        temp=verbefl2;
        while(temp!=NULL)
        {
            for ( i = 0;temp->type[i]!='\0' ; i++)
            {

                if(temp->type[i]==temp_nombre[0])
                {
                    if(temp->type[i+1]==temp_nombre[1])
                    {
                        for ( x = 0;temp->type[x]!='\0' ; x++)
                        {
                            if(temp->type[x]=='3' && ajouter==0)
                            {
                                if(premier_trouve==0)
                                {
                                    forme_flechie_verb2.head=temp;
                                    tmp=forme_flechie_verb2.head;
                                    forme_flechie_verb2.head->next=NULL;
                                    tmp->next=NULL;
                                    premier_trouve=1;
                                    compteur_ver2+=1;
                                    ajouter=1;
                                }
                                else
                                {
                                    tmp->next=temp;
                                    tmp=tmp->next;
                                    tmp->next=NULL;
                                    compteur_ver2+=1;
                                    ajouter=1;
                                }

                            }
                        }
                    }
                }
            }
            temp=temp->next;
            ajouter=0;
        }

        if(compteur_ver2==0)
        {
            verbe2 = extractinatorbase(vb);
            verbefl2 = forme_flechie(vb, verbe2);
        }
    }

    temp=adjectif_fl;
    t_std_list forme_flechie_adj;
    forme_flechie_adj.head=NULL;
    premier_trouve=0;
    int compteur_adj=0;
    ajouter=0;

    while(compteur_adj==0)
    {
        temp=adjectif_fl;
        while(temp!=NULL)
        {
            for ( i = 0;temp->type[i]!='\0' ; i++)
            {

                if(temp->type[i]==temp_nombre[0])
                {
                    if(temp->type[i+1]==temp_nombre[1])
                    {
                        for ( x = 0;temp->type[x]!='\0' ; x++)
                        {
                            if(temp->type[x]==temp_conjugaison[0])
                            {
                                if(temp->type[x+1]==temp_conjugaison[1] && ajouter==0)
                                {
                                    if(premier_trouve==0)
                                    {
                                        forme_flechie_adj.head=temp;
                                        tmp=forme_flechie_adj.head;
                                        forme_flechie_adj.head->next=NULL;
                                        tmp->next=NULL;
                                        premier_trouve=1;
                                        compteur_adj+=1;
                                        ajouter=1;
                                    }
                                }
                                else
                                {
                                    tmp->next=temp;
                                    tmp=tmp->next;
                                    tmp->next=NULL;
                                    compteur_adj+=1;
                                    ajouter=1;
                                }
                            }
                        }
                    }
                }
            }
            temp=temp->next;
            ajouter=0;
        }

        if(compteur_adj==0)
        {
            adjectif = extractinatorbase(adj);
            adjectif_fl = forme_flechie(adj, adjectif);
        }
    }


    temp=adjectif_fl2;
    t_std_list forme_flechie_adj2;
    forme_flechie_adj2.head=NULL;
    premier_trouve=0;
    int compteur_adj2=0;
    ajouter=0;

    while(compteur_adj2==0)
    {
        temp=adjectif_fl2;
        while(temp!=NULL)
        {
            for ( i = 0;temp->type[i]!='\0' ; i++)
            {

                if(temp->type[i]==temp_nombre_mot2[0])
                {
                    if(temp->type[i+1]==temp_nombre_mot2[1])
                    {
                        for ( x = 0;temp->type[x]!='\0' ; x++)
                        {
                            if(temp->type[x]==temp_conjugaison_mot2[0])
                            {
                                if(temp->type[x+1]==temp_conjugaison_mot2[1] && ajouter==0)
                                {
                                    if(premier_trouve==0)
                                    {
                                        forme_flechie_adj2.head=temp;
                                        tmp=forme_flechie_adj2.head;
                                        forme_flechie_adj2.head->next=NULL;
                                        tmp->next=NULL;
                                        premier_trouve=1;
                                        compteur_adj2+=1;
                                        ajouter=1;
                                    }
                                }
                                else
                                {
                                    tmp->next=temp;
                                    tmp=tmp->next;
                                    tmp->next=NULL;
                                    compteur_adj2+=1;
                                    ajouter=1;
                                }
                            }
                        }
                    }
                }
            }
            temp=temp->next;
            ajouter=0;
        }

        if(compteur_adj2==0)
        {
            adjectif2 = extractinatorbase(adj);
            adjectif_fl2 = forme_flechie(adj, adjectif2);
        }
    }

    if(compteur_ver==1)
    {
        if(compteur_adj==1)
        {
            if(compteur_adj2==1)
            {
                if(compteur_ver2==1)
                {
                    printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,forme_flechie_verb2.head->mot,forme_flechie_adj.head->mot,nom2,forme_flechie_adj2.head->mot);
                    return;
                }
                else
                {
                    tmp=forme_flechie_verb2.head;
                    int y= rand()%compteur_ver2;
                    for (int k = 0; k < y; k++)
                    {
                        tmp=tmp->next;
                    }
                    printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,tmp->mot,forme_flechie_adj.head->mot,nom2,forme_flechie_adj2.head->mot);
                    return;
                }

            }
            else
            {
                tmp=forme_flechie_adj2.head;
                int y= rand()%compteur_adj2;
                for (int k = 0; k < y; k++)
                {
                    tmp=tmp->next;
                }
                if(compteur_ver2==1)
                {
                    printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,forme_flechie_verb2.head->mot,forme_flechie_adj.head->mot,nom2,tmp->mot);
                    return;
                }
                else
                {
                    p_cell tmp2=forme_flechie_verb2.head;
                    int y= rand()%compteur_ver2;
                    for (int k = 0; k < y; k++)
                    {
                        tmp2=tmp2->next;
                    }
                    printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,tmp2->mot,forme_flechie_adj.head->mot,nom2,tmp->mot);
                    return;
                }

            }

        }
        else
        {
            tmp=forme_flechie_adj.head;
            int y=rand()%compteur_adj;
            for (int k = 0; k < y; k++)
            {
                tmp=tmp->next;
            }
            if(compteur_adj2==1)
            {
                if(compteur_ver2==1)
                {
                    printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,forme_flechie_verb2.head->mot,forme_flechie_adj.head->mot,nom2,forme_flechie_adj2.head->mot);
                    return;
                }
                else
                {
                    tmp=forme_flechie_verb2.head;
                    int y= rand()%compteur_ver2;
                    for (int k = 0; k < y; k++)
                    {
                        tmp=tmp->next;
                    }
                    printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,tmp->mot,forme_flechie_adj.head->mot,nom2,forme_flechie_adj2.head->mot);
                    return;
                }

            }
            else
            {
                p_cell tmp2=forme_flechie_adj2.head;
                int y= rand()%compteur_adj2;
                for (int k = 0; k < y; k++)
                {
                    tmp2=tmp2->next;
                }
                if(compteur_ver2==1)
                {
                    printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,forme_flechie_verb2.head->mot,tmp->mot,nom2,tmp2->mot);
                    return;
                }
                else
                {
                    p_cell tmp3=forme_flechie_verb2.head;
                    int y= rand()%compteur_ver2;
                    for (int k = 0; k < y; k++)
                    {
                        tmp3=tmp3->next;
                    }
                    printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,tmp3->mot,tmp->mot,nom2,tmp->mot);
                    return;
                }

            }
        }
    }
    else
    {
        tmp=forme_flechie_verb.head;
        int y=rand()%compteur_ver;
        for (int k = 0; k < y; k++)
        {
            tmp=tmp->next;
        }
        if(compteur_adj==1)
            {
                if(compteur_adj2==1)
                {
                    if(compteur_ver2==1)
                    {
                        printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,forme_flechie_verb2.head->mot,forme_flechie_adj.head->mot,nom2,forme_flechie_adj2.head->mot);
                        return;
                    }
                    else
                    {
                        tmp=forme_flechie_verb2.head;
                        int y= rand()%compteur_ver2;
                        for (int k = 0; k < y; k++)
                        {
                            tmp=tmp->next;
                        }
                        printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,tmp->mot,forme_flechie_adj.head->mot,nom2,forme_flechie_adj2.head->mot);
                        return;
                    }

                }
                else
                {
                    p_cell tmp2=forme_flechie_adj2.head;
                    int y= rand()%compteur_adj2;
                    for (int k = 0; k < y; k++)
                    {
                        tmp=tmp->next;
                    }
                    if(compteur_ver2==1)
                    {
                        printf("%s qui  %s %s %s %s %s\n",nom1,tmp->mot,forme_flechie_verb2.head->mot,forme_flechie_adj.head->mot,nom2,tmp2->mot);
                        return;
                    }
                    else
                    {
                        p_cell tmp2=forme_flechie_verb2.head;
                        int y= rand()%compteur_ver2;
                        for (int k = 0; k < y; k++)
                        {
                            tmp2=tmp2->next;
                        }
                        printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,tmp2->mot,forme_flechie_adj.head->mot,nom2,tmp->mot);
                        return;
                    }

                }

            }
        else
            {
                p_cell tmp2=forme_flechie_adj.head;
                int y=rand()%compteur_adj;
                for (int k = 0; k < y; k++)
                {
                    tmp=tmp->next;
                }
                if(compteur_adj2==1)
                {
                    if(compteur_ver2==1)
                    {
                        printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,forme_flechie_verb2.head->mot,forme_flechie_adj.head->mot,nom2,forme_flechie_adj2.head->mot);
                        return;
                    }
                    else
                    {
                        tmp=forme_flechie_verb2.head;
                        int y= rand()%compteur_ver2;
                        for (int k = 0; k < y; k++)
                        {
                            tmp=tmp->next;
                        }
                        printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,tmp->mot,forme_flechie_adj.head->mot,nom2,forme_flechie_adj2.head->mot);
                        return;
                    }

                }
                else
                {
                    p_cell tmp2=forme_flechie_adj2.head;
                    int y= rand()%compteur_adj2;
                    for (int k = 0; k < y; k++)
                    {
                        tmp2=tmp2->next;
                    }
                    if(compteur_ver2==1)
                    {
                        printf("%s qui  %s %s %s %s %s\n",nom1,tmp->mot,forme_flechie_verb2.head->mot,tmp->mot,nom2,tmp2->mot);
                        return;
                    }
                    else
                    {
                        p_cell tmp3=forme_flechie_verb2.head;
                        int y= rand()%compteur_ver2;
                        for (int k = 0; k < y; k++)
                        {
                            tmp3=tmp3->next;
                        }
                        printf("%s qui  %s %s %s %s %s\n",nom1,forme_flechie_verb.head->mot,tmp3->mot,tmp->mot,nom2,tmp->mot);
                        return;
                    }

                }
            }
    }
}

void type3(t_tree nom, t_tree vb, t_tree adj,t_tree adv)
{
    char temp_conjugaison[4];
    char temp_nombre[3];
    char *nom1=(char *) malloc(35*sizeof(char ));
    char *adverbe=(char *) malloc(35*sizeof(char ));
    char *verbe=(char *) malloc(35*sizeof(char ));
    char *adjectif=(char *) malloc(35*sizeof(char ));
    char *type_nom1=(char *) malloc(50*sizeof(char ));
    nom1 = extractinatorbase(nom);
    verbe = extractinatorbase(vb);
    adjectif = extractinatorbase(adj);
    adverbe = extractinatorbase(adv);
    p_cell temp;
    p_cell verbefl = forme_flechie(vb, verbe);
    p_cell adjectif_fl = forme_flechie(adj, adjectif);
    p_cell nom1fl = forme_flechie(nom, nom1);

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
        type_nom1 = nom1fl->type;
    }

    i=1;

    int j=0,x=0;

    for ( i = 0; type_nom1[i]!='\0' ; i++)
    {
        if(type_nom1[i]!='+')
        {
            if(i<=2)
            {
                temp_conjugaison[j]=type_nom1[i];
                j++;
            }
            else
            {
                temp_conjugaison[i]='\0';
                temp_nombre[x]=type_nom1[i];
                x++;
            }
        }
    }
    temp_nombre[x]='\0';
    j=0;
    x=0;

    temp=verbefl;
    t_std_list forme_flechie_verb;
    forme_flechie_verb.head=NULL;
    p_cell tmp = NULL;
    int premier_trouve=0,compteur_ver=0;

    while(compteur_ver==0)
    {
        temp=verbefl;
        while(temp!=NULL)
        {
            for ( i = 0;temp->type[i]!='\0' ; i++)
            {

                if(temp->type[i]==temp_nombre[0])
                {
                    if(temp->type[i+1]==temp_nombre[1])
                    {
                        for ( x = 0;temp->type[x]!='\0' ; x++)
                        {
                            if(temp->type[x]=='3')
                            {
                                if(premier_trouve==0)
                                {
                                    forme_flechie_verb.head=temp;
                                    tmp=forme_flechie_verb.head;
                                    forme_flechie_verb.head->next=NULL;
                                    tmp->next=NULL;
                                    premier_trouve=1;
                                    compteur_ver+=1;
                                }
                                else
                                {
                                    tmp->next=temp;
                                    tmp=tmp->next;
                                    tmp->next=NULL;
                                    compteur_ver+=1;
                                }

                            }
                        }
                    }
                }
            }
            temp=temp->next;
        }

        if(compteur_ver==0)
        {
            verbe = extractinatorbase(vb);
            verbefl = forme_flechie(vb, verbe);
        }
    }


    temp=adjectif_fl;
    t_std_list forme_flechie_adj;
    forme_flechie_adj.head=NULL;
    premier_trouve=0;
    int compteur_adj=0;
     int ajouter=0;

    while(compteur_adj==0)
    {
        temp=adjectif_fl;
        while(temp!=NULL)
        {
            for ( i = 0;temp->type[i]!='\0' ; i++)
            {

                if(temp->type[i]==temp_nombre[0])
                {
                    if(temp->type[i+1]==temp_nombre[1])
                    {
                        for ( x = 0;temp->type[x]!='\0' ; x++)
                        {
                            if(temp->type[x]==temp_conjugaison[0])
                            {
                                if(temp->type[x+1]==temp_conjugaison[1] && ajouter==0)
                                {
                                    if(premier_trouve==0)
                                    {
                                        forme_flechie_adj.head=temp;
                                        tmp=forme_flechie_adj.head;
                                        forme_flechie_adj.head->next=NULL;
                                        tmp->next=NULL;
                                        premier_trouve=1;
                                        compteur_adj+=1;
                                        ajouter=1;
                                    }
                                }
                                else
                                {
                                    tmp->next=temp;
                                    tmp=tmp->next;
                                    tmp->next=NULL;
                                    compteur_adj+=1;
                                    ajouter=1;
                                }
                            }
                        }
                    }
                }
            }
            temp=temp->next;
            ajouter=0;
        }

        if(compteur_adj==0)
        {
            adjectif = extractinatorbase(adj);
            adjectif_fl = forme_flechie(adj, adjectif);
        }
    }

    if(compteur_ver==1)
    {

        if(compteur_adj==1)
        {
            printf("%s %s %s %s\n",nom1,forme_flechie_verb.head->mot,adverbe,forme_flechie_adj.head->mot);
            return;
        }
        else
        {
            tmp=forme_flechie_adj.head;
            int y=rand()%compteur_adj;
            for (int k = 0; k < y; k++)
            {
                tmp=tmp->next;
            }
            printf("%s %s %s %s\n",nom1,forme_flechie_verb.head->mot,adverbe,tmp->mot);
            return;
        }
    }

    else if(compteur_adj==1)
    {
        if (compteur_ver!=1)
        {
            tmp=forme_flechie_verb.head;
            int y=rand()%compteur_ver;
            for (int k = 0; k < y; k++)
            {
                tmp=tmp->next;
            }
            printf("%s %s %s %s\n",nom1,tmp->mot,adverbe,forme_flechie_adj.head->mot);
            return;
        }

    }
    else
    {
        tmp=forme_flechie_verb.head;
        int y=rand()%compteur_ver;
        for (int k = 0; k < y; k++)
        {
            tmp=tmp->next;
        }

        p_cell tmp2=forme_flechie_adj.head;
        int r=rand()%compteur_adj;
        for (int k = 0; k < r; k++)
        {
            tmp2=tmp2->next;
        }
        printf("%s %s %s %s\n",nom1,tmp->mot,adverbe,tmp2->mot);
    }
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
