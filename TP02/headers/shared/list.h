#ifndef LIST_h
#define LIST_h

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int value;
} key;

typedef struct node_list *pointer_list;

typedef struct node_list
{
    key content;
    pointer_list next;
} node_list;

typedef struct
{
    pointer_list first, last;
} list;

/*
 * Faz uma Lista Vazia
 */
void make_empty_list(list *linked_list);

/*
 * Insere um valor na lista
 */
void insert_in_list(list *linked_list, key content);

/*
 * remove value in list
 */
void remove_in_list(list *linked_list, key content);

/*
 * Printa a lista
 */
void print_list(list *linked_list);

/*
 * Retorna se a lista está ou não vazia
*/
int list_is_empty(list linked_list);

/*
* Retorna a quantidade de intens na lista
*/
int lenght(list *linked_list);

/*
* Soma dos valores da lista 
*/
int sum(list *linked_list);

#endif