#include "../../headers/core/scheduling.h"

void init_scheduling(scheduling *scheduling)
{
    scheduling->first = (queue *)malloc(sizeof(queue));
    scheduling->second = (queue *)malloc(sizeof(queue));
    scheduling->third = (queue *)malloc(sizeof(queue));
    scheduling->fourth = (queue *)malloc(sizeof(queue));

    init_queue(scheduling->first);
    init_queue(scheduling->second);
    init_queue(scheduling->third);
    init_queue(scheduling->fourth);
}

void do_scheduling(scheduling *scheduling, int index, int priority)
{
    switch (priority)
    {
    case 0:
        to_queue(scheduling->first, index);
        break;
    case 1:
        to_queue(scheduling->second, index);
        break;
    case 2:
        to_queue(scheduling->third, index);
        break;
    case 3:
        to_queue(scheduling->fourth, index);
    default:
        break;
    }
}

int dequeue_scheduling(scheduling *scheduling)
{
    if (!verify_if_is_empty(scheduling->first))
    {
        return dequeue(scheduling->first);
    }
    else if (!verify_if_is_empty(scheduling->second))
    {
        return dequeue(scheduling->second);
    }
    else if (!verify_if_is_empty(scheduling->third))
    {
        return dequeue(scheduling->third);
    }
    else if (!verify_if_is_empty(scheduling->fourth))
    {
        return dequeue(scheduling->fourth);
    }
    else
    {
        return UNDEFINED;
    }
}