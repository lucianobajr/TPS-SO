#include "../../headers/metrics/metrics.h"

void initialize_metrics(metrics *memory_metrics)
{
    memory_metrics->allocation_request_metrics.total = 0;
    memory_metrics->allocation_request_metrics.denied = 0;

    make_empty_list(&memory_metrics->external_fragmentation);
    make_empty_list(&memory_metrics->nodes_traveled);
}

void add_external_fragment(metrics *memory_metrics, int value)
{
    key fragment;
    fragment.value = value;

    insert_in_list(&memory_metrics->external_fragmentation, fragment);
}

void add_node_traveled(metrics *memory_metrics, int number_of_nodes)
{
    key node_traveled;
    node_traveled.value = number_of_nodes;

    insert_in_list(&memory_metrics->nodes_traveled, node_traveled);
}

void increment_total_allocation_request(metrics *memory_metrics)
{
    memory_metrics->allocation_request_metrics.total++;
}

void increment_denied_allocation_request(metrics *memory_metrics)
{
    memory_metrics->allocation_request_metrics.denied++;
}

int average_number_of_external_fragments(metrics *memory_metrics)
{
    int number_of_external_fragments = lenght(&memory_metrics->external_fragmentation);
    int sum_of_values = sum(&memory_metrics->external_fragmentation);

    return sum_of_values / number_of_external_fragments;
}

int average_allocation_time(metrics *memory_metrics)
{
    int number_of_nodes_traveled = lenght(&memory_metrics->nodes_traveled);
    int sum_of_values = sum(&memory_metrics->external_fragmentation);

    return sum_of_values / number_of_nodes_traveled;
}

int percentage_of_allocation_request_is_denied(metrics *memory_metrics)
{
    return ((memory_metrics->allocation_request_metrics.denied * 100) / memory_metrics->allocation_request_metrics.total);
}