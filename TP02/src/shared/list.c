#include "../../headers/shared/list.h"

void make_empty_list(list *linked_list)
{
    linked_list->first = (pointer)malloc(sizeof(pointer));
    linked_list->last = linked_list->first;
    linked_list->first->next = NULL;
}

int list_is_empty(list linked_list)
{
    return (linked_list.first == linked_list.last);
}

void insert_in_list(list *linked_list, key content)
{
    linked_list->last->next = (pointer)malloc(sizeof(node));
    linked_list->last = linked_list->last->next;
    linked_list->last->content = content;
    linked_list->last->next = NULL;
}

void print_list(list *linked_list)
{
    pointer aux_pointer;
    aux_pointer = linked_list->first->next;
    while (aux_pointer != NULL)
    {
        printf("%d\n", aux_pointer->content.value);
        aux_pointer = aux_pointer->next;
    }
}

int lenght(list *linked_list)
{
    int lenght = 0;

    pointer aux_pointer;
    aux_pointer = linked_list->first->next;
    while (aux_pointer != NULL)
    {
        lenght++;
    }

    return lenght;
}