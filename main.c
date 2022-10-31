#include <stdio.h>

<<<<<<< HEAD
=======
struct s_cell
{
    char *mot;
    char *type;
    struct s_cell *next;
};

typedef struct s_cell t_cell, *p_cell;

typedef struct s_std_list
{
    p_cell head;
} t_std_list;

struct s_node
{
    char value;
    struct s_node   *lettres[26];   //appelle le pointeur[le numéro]
    t_std_list *pointeur;
    int pointeur_occupe;
};

typedef struct s_node t_node, *p_node;

typedef struct s_tree
{
    p_node root;
} t_tree, *p_tree;

>>>>>>> be867e2 (Initial commit)
int main() {
    printf("Hello, World!\n");
    return 0;
}
