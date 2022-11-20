#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "liste.h"

p_node createNode(char lettre)
{
    p_node nouv;

    nouv = (p_node)malloc(sizeof(t_node));
    nouv->value = lettre;
    for (int i = 0; i < 26; ++i)
    {
        nouv->lettres[i]=NULL;
    }
    nouv->nombre_pointeur=0;
    nouv->pointeur=NULL;
    nouv->fin_mot=0;
    nouv->nombre_forme_flechies=0;
    nouv->mot_base= malloc(sizeof(mot_total));
    return nouv;
}

p_node Cherchelettre(p_node pn,char lettre,int i)
{
    p_node temp;
    temp=pn;
    if(pn->lettres[i]==NULL)
    {
        return NULL;
    }

    if(pn->lettres[i]->value==lettre)
    {
        return pn->lettres[i] ;
    }

    if(i+1 <= pn->nombre_pointeur)
    {
        temp= Cherchelettre(pn,lettre,i+1);
        if(temp!=NULL)
        {
            return temp;
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
}

int trouver_mot(p_node pn, char cara[35], int numero_lettre) {
    if (cara[numero_lettre] == '\0')
    {
        if(pn->fin_mot==1)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    p_node temp = Cherchelettre(pn, cara[numero_lettre], 0);
    int compteur;
    if (temp != NULL)
    {
        compteur = trouver_mot(temp, cara, numero_lettre + 1) + 1;
        return compteur;
    }
}

int compteur(p_node pn, char cara[35])
{
    int j = 0;
    while (cara[j] != '\0')    //on cherche la taille du mot donné
    {
        j++;
    }
    int compteur=trouver_mot(pn,cara,1);
    if (compteur == j-1)     //on regarde si nombre de lettre trouvées = nombre de lettres attendues. Si égale alors le mot trouvé est bon, sinon c'est faux
    {
        return 1;
    }
    else {
        return 0;
    }

}

p_node Creearbre(p_node pn,char mot[35],int indicemot,char type[35])
{
    p_node temp=NULL,temp2;

    if(pn!=NULL)
    {
        if (mot[indicemot]!='\0')
        {

            temp= Cherchelettre(pn,mot[indicemot],0);
            if (temp!=NULL)
            {
                temp=Creearbre(temp,mot,indicemot+1,type);
            }
            else
            {
                p_node px=createNode(mot[indicemot]);
                if(pn->nombre_pointeur==0)
                {
                    pn->lettres[0]=px;
                    pn->nombre_pointeur=pn->nombre_pointeur+1;
                }
                else
                {

                    pn->lettres[pn->nombre_pointeur]=px;
                    pn->nombre_pointeur=pn->nombre_pointeur+1;
                }
                px= Creearbre(px,mot,indicemot+1,type);
            }
        }
        else
        {
            if(temp==NULL)
            {
                t_std_list tempflechie=createt_std_listflechie();
                FILE* dicofile= fopen("C:\\Users\\giuga\\CLionProjects\\Projet mot\\dico_10_lignes.txt", "r");
                char flechie[30];
                char base[30];
                char formes[50];
                int i=0;
                int result=0;
                int nombreflechie=0;
                while(fscanf(dicofile,"%s\t%s\t%s",flechie, base, formes) != EOF) //EOF pour end of file et \t pour les tabulations
                {
                    i=0;
                    while (base[i]!='\0')
                    {
                        if(base[i]==mot[i])
                        {
                            result+=1;
                        }
                        else
                        {
                            result-=1;
                        }
                        i+=1;
                    }

                    int j=0;

                    while(type[j]!='\0')
                    {
                        if(formes[j]!=type[j])
                        {
                            result-=1;
                        }
                        j+=1;
                    }

                    if (result==i)
                    {
                        tempflechie= ajoutlisteflechie(tempflechie,flechie,formes);
                        nombreflechie+=1;
                    }
                    result=0;
                }
                pn->pointeur = tempflechie.head;
                pn->fin_mot=1;
                pn->nombre_forme_flechies=nombreflechie;
                mot_total *motbase=(mot_total *)malloc(sizeof(mot_total));
                i=0;
                while(mot[i]!='\0')
                {
                    motbase->mot_base[i]=mot[i];
                    i++;
                }
                motbase->mot_base[i]='\0';
                pn->mot_base=motbase;
            }
        }
    }
    else
    {
        p_node px=createNode(mot[indicemot]);
        pn=px;
        px= Creearbre(px,mot,indicemot+1,type);
    }
    return pn;

}

p_node trouver_flechie(p_node pn, char mot[25])
{
    int i = 0, taille_mot = 0;
    if(pn->fin_mot != 0)
    {
        p_cell flechie = pn->pointeur;

        while(mot[i]!='\0')
        {
            taille_mot++;
            i++;
        }

        while (flechie != NULL)
        {
            i = 0;
            int cpt = 0;

            while (flechie->mot[i] != '\0')
            {
                if (flechie->mot[i] == mot[i])
                {
                    cpt++;
                }
                else
                {
                    cpt--;
                }
                i++;
            }

            if (cpt == taille_mot)
            {
                return pn;
            }
            else
            {
                flechie = flechie->next;
            }
        }
    }

    for(int j=0; j < pn->nombre_pointeur; j++)
    {
        p_node tmp = trouver_flechie(pn->lettres[j], mot);

        if (tmp != NULL)
        {
            return tmp;
        }
    }
    return NULL;
}
