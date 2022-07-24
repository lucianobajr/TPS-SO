#include "../../headers/shared/list.h"

void make_empty_list(list *linked_list)
{
    linked_list->first = (pointer_list)malloc(sizeof(pointer_list));
    linked_list->last = linked_list->first;
    linked_list->first->next = NULL;
}

int list_is_empty(list linked_list)
{
    return (linked_list.first == linked_list.last);
}

void insert_in_list(list *linked_list, key content)
{
    linked_list->last->next = (pointer_list)malloc(sizeof(node_list));
    linked_list->last = linked_list->last->next;
    linked_list->last->content = content;
    linked_list->last->next = NULL;
}

int element_already_exists(list *linked_list, int value)
{
    int exists = 0;
    pointer_list aux_pointer_list;
    aux_pointer_list = linked_list->first->next;
    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == value)
        {
            exists = 1;
        }
        
        aux_pointer_list = aux_pointer_list->next;
    }

    return exists;
}

void print_list(list *linked_list)
{
    pointer_list aux_pointer_list;
    aux_pointer_list = linked_list->first->next;
    while (aux_pointer_list != NULL)
    {
        printf("%d\n", aux_pointer_list->content.value);
        aux_pointer_list = aux_pointer_list->next;
    }
}

int lenght(list *linked_list)
{
    int value = 0;

    pointer_list aux_pointer_list;
    aux_pointer_list = linked_list->first->next;
    while (aux_pointer_list != NULL)
    {
        value++;
        aux_pointer_list = aux_pointer_list->next;
    }

    return value;
}

int sum(list *linked_list)
{
    int value = 0;

    pointer_list aux_pointer_list;
    aux_pointer_list = linked_list->first->next;
    while (aux_pointer_list != NULL)
    {
        value += aux_pointer_list->content.value;
        aux_pointer_list = aux_pointer_list->next;
    }

    return value;
}