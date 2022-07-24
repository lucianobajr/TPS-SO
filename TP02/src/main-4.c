#include "../headers/domain/domain.h"
#include "../headers/log/log.h"

int main(int argc, char const *argv[])
{
    domain process_manager_domain;

    init_domain(&process_manager_domain);
    allocation_algorithms_used(&process_manager_domain);

    int highest_value = highest_value_by_allocation_algorithms(&process_manager_domain);

    for (int i = 0; i < 6; i++)
    {
        int process_size = 1 + rand() % highest_value;

        printf("VALOR = %d\n", process_size);
        allocate_new_process(&process_manager_domain, process_size);
    }

    print_memories(&process_manager_domain);
    print_metrics(&process_manager_domain);

    return 0;
}