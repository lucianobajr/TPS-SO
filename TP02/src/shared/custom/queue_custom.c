#include "../../../headers/shared/custom/queue_custom.h"

void init_queue_custom(queue_custom *queue)
{
    queue->front = (pointer_custom)malloc(sizeof(node_custom));
    queue->back = queue->front;
    queue->front->next = NULL;
}

int verify_if_is_empty_custom(queue_custom *queue)
{
    return (queue->front == queue->back);
}

int to_queue_custom(queue_custom *queue, int index, int size)
{
    pointer_custom aux;
    aux = (pointer_custom)malloc(sizeof(node_custom));
    if (aux == NULL)
    {
        return 0;
    }

    aux->index = index;
    aux->size = size;
    aux->next = NULL;

    queue->back->next = aux;
    queue->back = aux;

    return 1;
}

void dequeue_custom(queue_custom *queue, int *value)
{
    pointer_custom aux;
    if (verify_if_is_empty_custom(queue))
    {
        value[0] = -1;
        value[1] = -1;
    }

    aux = queue->front;
    queue->front = queue->front->next;

    value[0] = queue->front->index;
    value[1] = queue->front->size;
    free(aux);
}

void print_queue_custom(queue_custom *queue)
{
    pointer_custom aux;

    aux = queue->front->next;
    while (aux != NULL)
    {
        printf("%d ", aux->size);

        aux = aux->next;
    }
}