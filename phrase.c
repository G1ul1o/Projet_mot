#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "phrase.h"
#include "liste.h"

//permet d'extraire un noeud depuis le root, il prend en paramètre l'arbre
char* extractinatorbase(t_tree tree)
{
    char* mot = (char *)malloc(sizeof (char));

    int nb_enfant = tree.nombre_pointeurs;

    int random= rand()%nb_enfant; //choix aléatoire d'une lettre depuis le root

    p_node temp=tree.root[random];
    mot[0]=temp->value;
    mot = miniextractinatorbase(temp, mot, 0);
    return mot;
}

//permet d'extraire un mot depuis l'arbre,il prend en paramètre le noeud, le mot et l'indice
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

//permet d'extraire la cellule "head" de la liste du pointeur noeud,il prend en paramètre l'arbre et le mot sous forme de base
p_cell forme_flechie(t_tree tree, char* base){
    p_cell flechies;
    p_node temp,temp2;
    int i=0;

    temp = CherchelettreRoot(tree,base[i],i); //On cherche la première lettre dans le root de l'arbre
    i++;

    while(base[i]!='\0')
    {
        temp2 = Cherchelettre(temp, base[i],0); // on, cherche la lettre suivante dans les enfants du noeud où on se situe

        if (temp2!=NULL) // si un enfant contenant la i lettre de base existe on déplace dans se noeud et on cherche le suivant
        {
            temp=temp2;
            i++;
        }
    }
    flechies=temp->pointeur; //on donne le pointeur à fléchies qui sera la cellule contenant le mot flechies et le type
    return flechies;
}

//fonction qui permet de générer une phrase du premier modèle, il prend en paramètre les arbres nom, verbe et adjectif
void phrase_modele1(t_tree nom, t_tree vb, t_tree adj)
{
    srand((unsigned) time(NULL)); //fonction random

    char temp_conjugaison[4];
    char temp_nombre[3];
    int i = 1;

    //on alloue de la mémoire au différentes variables
    char *nom1=(char *) malloc(35*sizeof(char ));
    char *nom2=(char *) malloc(35*sizeof(char ));
    char *verbe=(char *) malloc(35*sizeof(char ));
    char *adjectif=(char *) malloc(35*sizeof(char ));

    char *type_nom1=(char *) malloc(50*sizeof(char ));
    char *type_nom2=(char *) malloc(50*sizeof(char ));

    //On extrait aléatoirement des mots à partir de l'arbre de leur type
    nom1 = extractinatorbase(nom);
    nom2 = extractinatorbase(nom);
    verbe = extractinatorbase(vb);
    adjectif = extractinatorbase(adj);

    //cellule temporaire
    p_cell temp;

    //On récupère les formes fléchies
    p_cell verbefl = forme_flechie(vb, verbe);
    p_cell adjectif_fl = forme_flechie(adj, adjectif);
    p_cell nom1fl = forme_flechie(nom, nom1);
    p_cell nom2fl = forme_flechie(nom, nom2);


    //On prends une forme fléchie aléatoire du premier nom
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

    //On prends une forme fléchie aléatoire du deuxième nom
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

    //On sépare le type (Mas,Fem) avec leurs nombres(Mas,Pl) du premier nom car c'est sur lui que vont se conjuger le verbe et l'adjectif
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


    t_std_list forme_flechie_verb;//liste contenant toutes les formes des verbes pouvant convenir
    forme_flechie_verb.head=NULL;
    p_cell tmp = NULL;
    int premier_trouve=0,compteur_ver=0;

    //tant qu'il n'a pas trouver une forme convenable il va continuer
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
                                if(premier_trouve==0) //on teste si c'est le premier à être ajouté à la liste
                                {
                                    //ajoute les verbes de bonnes formes
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

        //on change de verbe si on ne trouve pas de bonne forme
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

    //tant qu'il n'a pas trouver une forme convenable il va continuer
    while(compteur_adj==0) {

        temp = adjectif_fl;

        while (temp != NULL)
        {
            for (i = 0; temp->type[i] != '\0'; i++) {

                if ((temp->type[i] == temp_nombre[0]) || (temp->type[i] == 'I')) //(temp->type[i] == 'I') pour le cas où c'est un adjectif invariable
                {
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
                                }

                                else
                                {
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

    // s'il n'y a qu'un seul choix en print directement sinon on va choisir aléatoirement entre les formes qui convienne
    if(compteur_ver==1)
    {

        if(compteur_adj==1)
        {
            printf("%s %s %s %s\n",nom1,forme_flechie_verb.head->mot,forme_flechie_adj.head->mot,nom2);
            return;
        }
        else
        {
            //choix aléatoire
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
        //choix aléatoire
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
        //choix aléatoire
        tmp=forme_flechie_verb.head;
        int y=rand()%compteur_ver;
        for (int k = 0; k < y; k++)
        {
            tmp=tmp->next;
        }

        //choix aléatoire
        p_cell tmp2=forme_flechie_adj.head;
        int r=rand()%compteur_adj;
        for (int k = 0; k < r; k++)
        {
            tmp2=tmp2->next;
        }
        printf("%s %s %s %s\n",nom1,tmp->mot,tmp2->mot,nom2);
    }
}

//fonction qui permet de générer une phrase du deuxième modèle, il prend en paramètre les arbres nom, verbe et adjectif
void phrase_modele2(t_tree nom, t_tree vb, t_tree adj)
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

//fonction qui permet de générer une phrase du troisième modèle, il prend en paramètre les arbres nom, verbe, adverbe et adjectif
void phrase_modele3(t_tree nom, t_tree vb, t_tree adj,t_tree adv)
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
