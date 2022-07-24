#include "../headers/domain/domain.h"
#include "../headers/log/log.h"

int main(int argc, char const *argv[])
{
    domain process_manager_domain;

    init_domain(&process_manager_domain);
    allocation_algorithms_used(&process_manager_domain);

    

    for (int i = 0; i < 6; i++)
    {
        allocate_new_process(&process_manager_domain);
    }

    print_memories(&process_manager_domain);
    print_metrics(&process_manager_domain);

    return 0;
}