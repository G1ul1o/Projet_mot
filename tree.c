#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

//crer un arbre vide et elle ne prend rien en paramètre
t_tree CreeArbrevide()
{
    t_tree arbre;
    for (int i = 0; i < 26; ++i) {
        arbre.root[i]=NULL;
    }

    return arbre;
}

//cherche lettre dans le root et elle prend en paramètre le tree, lettre, l'indice du noeud a tester
p_node CherchelettreRoot(t_tree pn,char lettre,int i)
{
    t_tree temp;
    temp=pn;
    p_node tempnode;

    if(temp.root[i]==NULL) //si l'enfant est NULL alors on retourne NULL car l'arbre ne contient pas la lettre
    {
        return NULL;
    }

    if(temp.root[i]->value==lettre)//si l'enfant contient la lettre alors on le retourne
    {
        return temp.root[i];
    }

    if(i+1< temp.nombre_pointeurs)
    {
        tempnode= CherchelettreRoot(pn,lettre,i+1); //on teste le suivant
        if(tempnode!=NULL)
        {
            return tempnode;
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
}

//On ajoute le premier noeud à un arbre vide elle prend en paramètre le mot et le type
t_tree PremierNoeud(char mot[35],char type[35])
{
    t_tree ps;
    ps=CreeArbrevide();
    ps.root[0] = AjoutNoeud(ps.root[0],mot,0,type);
    ps.nombre_pointeurs=1;
    return ps;
}

//On ajoute un noeud à un arbre, elle prends en paramètre l'arbre, le mot et le type
t_tree AjoutNoeudArbre(t_tree t,char mot[35],char type[35])
{
    p_node temp;
    temp= CherchelettreRoot(t,mot[0],0);  //on teste si la première lettre est dans l'arbre
    if (temp!=NULL)
    {
        temp= AjoutNoeud(temp,mot,1,type); //si oui on se déplace dans le noeud
    }
    else
    {
        t.root[t.nombre_pointeurs] = AjoutNoeud(t.root[t.nombre_pointeurs],mot,0,type); //sinon on crée le noeud
        t.nombre_pointeurs+=1;
    }

    return t;
}

//On recherche le fléchie d'un mot, elle prend en paramètre l'arbre et le mot
void recherche_flechie(t_tree arbre, char mot[25])
{
    int i = 0, taille_mot = 0;
    int trouve = 0, num_cell = 0;
    p_node pn;
    p_node temp= CherchelettreRoot(arbre,mot[0],0); //on teste si la première lettre existe et on se place dessus

    if(temp!=NULL)
    {
        pn =trouver_flechie(temp, mot);
    }

    //on teste si le mot existe dans les flèchies de notre cellule
    if(pn!=NULL)
    {
        p_cell cherche_mot = pn->pointeur;


        while(mot[i]!='\0')
        {
            taille_mot++;
            i++;
        }

        while ((cherche_mot != NULL) && trouve != 1)
        {
            i = 0;
            int cpt = 0;
            while (cherche_mot->mot[i] != '\0') {
                if (cherche_mot->mot[i] == mot[i]) {
                    cpt++;
                } else {
                    cpt--;
                }
                i++;
            }

            if (cpt == taille_mot) {
                trouve = 1;
            }
            else
            {
                //printf("flechie suivant\n");
                cherche_mot = cherche_mot->next;
                num_cell ++;
            }
        }
    }



    if(trouve==1)
    {
        p_cell flechie = pn->pointeur;
        for (int indice = 0; indice < num_cell; indice++)
        {
            flechie = flechie->next;
        }
        printf("%s %s %s\n", flechie->mot, flechie->type, pn->mot_base);
    }
    else
    {
        printf("Nous n'avons pas trouver le mot\n");
    }
}

void type_mot(char lemot[35], t_tree arbre_nom, t_tree arbre_adj, t_tree arbre_ver, t_tree arbre_adv)
{
    int lecompteur = 0;
    p_node montemp1,montemp2;

    montemp1 = CherchelettreRoot(arbre_nom,lemot[0],0); //vérifier si la première lettre est dans un arbre (on le fait a chaque fois)
    if (montemp1!=NULL) //pour éviter que la fonction se fasse si la première lettre n'est pas dans un arbre (on le fait à chaque fois)
    {
        lecompteur = compteur(montemp1, lemot); //assigne a lecompteur ce que retourne compteur
        if (lecompteur==1) //si la fonction compteur retourne 1
        {
            printf("Le mot existe et est un nom.\n");
        }
    }

    montemp1 = CherchelettreRoot(arbre_adj,lemot[0],0);
    int lecompteur1=0; //on remet le compteur à 0 pour refaire les tests
    if (montemp1!=NULL)
    {
        lecompteur1 = compteur(montemp1, lemot);
        if (lecompteur1==1)
        {
            printf("Le mot existe et est un adjectif.\n");
        }
    }
    montemp2 = CherchelettreRoot(arbre_ver,lemot[0],0);
    int lecompteur2=0;
    if (montemp2!=NULL)
    {
        lecompteur2 = compteur(montemp2, lemot);
        if (lecompteur2==1)
        {
            printf("Le mot existe et est un verbe.\n");
        }
    }
    montemp2 = CherchelettreRoot(arbre_adv,lemot[0],0);
    int lecompteur3=0;
    if (montemp2!=NULL)
    {
        lecompteur3 = compteur(montemp2, lemot);
        if (lecompteur3==1)
        {
            printf("Le mot existe et est un adverbe.\n");
        }
    }

    if ((lecompteur==0)&&(lecompteur1==0)&&(lecompteur2==0)&&(lecompteur3==0))
    {
        printf("Le mot n'existe pas.\n");
    }

}
