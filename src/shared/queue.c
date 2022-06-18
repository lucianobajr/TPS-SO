#include "../../headers/shared/queue.h"

void init_queue(queue *queue)
{
    queue->front = (pointer)malloc(sizeof(node));
    queue->back = queue->front;
    queue->front->next = NULL;
}

int verify_if_is_empty(queue *queue)
{
    return (queue->front == queue->back);
}

int to_queue(queue *queue, int index)
{
    pointer aux;
    aux = (pointer)malloc(sizeof(node));
    if (aux == NULL)
    {
        return 0;
    }

    aux->index = index;
    aux->next = NULL;

    queue->back->next = aux;
    queue->back = aux;

    return 1;
}

int dequeue(queue *queue)
{
    int value;
    pointer aux;
    if (verify_if_is_empty(queue))
    {
        return -1;
    }

    aux = queue->front;
    queue->front = queue->front->next;

    value = queue->front->index;
    free(aux);

    return index;
}

void print_queue(queue *queue)
{
    pointer aux;

    aux = queue->front->next;
    while (aux != NULL)
    {
        printf("%d ", aux->index);

        aux = aux->next;
    }
    printf("\n");
}

void adjust_queue_values(queue *queue, int value)
{
    pointer aux;

    aux = queue->front->next;
    while (aux != NULL)
    {
        if (value < aux->index)
        {
            aux->index -= 1;
        }
        aux = aux->next;
    }
}