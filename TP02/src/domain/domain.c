#include "../../headers/domain/domain.h"
#include "../../headers/log/log.h"
#include "../../headers/components/virtual_memory.h"

void init_domain(domain *process_manager_domain)
{
    generate();
    generate_address();
    make_empty_list(&(process_manager_domain->allocation_algorithms));

    int algorithm_option, continue_input;

    do
    {
        menu_main_memory();
        scanf("%d", &algorithm_option);

        if (algorithm_option != 1 && algorithm_option != 2 && algorithm_option != 3 && algorithm_option != 4)
        {
            logger("\nError! Invalid input!\n", ERROR_COLOR);
            printf("----------> ");
        }

        if (element_already_exists(&(process_manager_domain->allocation_algorithms), algorithm_option))
        {
            logger("\nError! You already chose this option!\n", ERROR_COLOR);
        }
        else
        {
            key tmp;
            tmp.value = algorithm_option;
            insert_in_list(&(process_manager_domain->allocation_algorithms), tmp);
        }

        printf("\nDo you want to choose one more algorithm? (1) yes; (2) no: ");
        scanf("%d", &continue_input);
    } while (continue_input != 2);

    pointer_list aux_pointer_list;
    aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;
    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == FIRST_FIT)
        {
            process_manager_domain->memory_first_fit = init_main_memory();
            initialize_metrics(&process_manager_domain->memory_metrics_first_fit);
            init_queue_custom(&process_manager_domain->denied_process_first_fit);
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            process_manager_domain->memory_next_fit = init_main_memory();
            initialize_metrics(&process_manager_domain->memory_metrics_next_fit);
            init_queue_custom(&process_manager_domain->denied_process_next_fit);
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
           
            process_manager_domain->memory_best_fit = init_main_memory();
            initialize_metrics(&process_manager_domain->memory_metrics_best_fit);
            init_queue_custom(&process_manager_domain->denied_process_best_fit);
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
           
            process_manager_domain->memory_worst_fit = init_main_memory();
            initialize_metrics(&process_manager_domain->memory_metrics_worst_fit);
            init_queue_custom(&process_manager_domain->denied_process_worst_fit);
           
        }

        aux_pointer_list = aux_pointer_list->next;
    }

    process_manager_domain->next_fit_index = 0;
}

void allocation_algorithms_used(domain *process_manager_domain)
{
    printf("==============================================================\n");
    printf("|                 \e[1;93mALLOCATION ALGORITHMS USED\033[0m                 |\n");
    printf("==============================================================\n");

    pointer_list aux_pointer_list;
    aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;
    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == FIRST_FIT)
        {
            printf("|                     \033[38;5;196m  (1) \e[1;97m - FIRST FIT                     |\n");
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            printf("|                     \033[38;5;196m  (2) \e[1;97m - NEXT FIT                      |\n");
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
            printf("|                     \033[38;5;196m  (3) \e[1;97m - BEST FIT                      |\n");
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
            printf("|                     \033[38;5;196m  (4) \e[1;97m - WORST FIT                     |\n");
        }

        aux_pointer_list = aux_pointer_list->next;
    }

    printf("==============================================================\n");
}

void allocate_new_process(domain *process_manager_domain, process_table *new_process, int process_index, int first_process)
{
    int highest_value = highest_value_by_allocation_algorithms(process_manager_domain, first_process == TRUE ? FALSE : TRUE);

    int process_size = 1 + rand() % highest_value;

    printf("\033[38;5;3m");
    printf("==================================\n");
    printf("      NEW PROCESS SIZE => %d\n", process_size);
    printf("==================================\n");
    printf("\033[0m");

    pointer_list aux_pointer_list;
    aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;
    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == FIRST_FIT)
        {

            int possible_process_index = first_fit(
                process_manager_domain->memory_first_fit,
                &process_manager_domain->memory_metrics_first_fit,
                &process_manager_domain->denied_process_first_fit,
                process_index,
                process_size);

            if (possible_process_index == -1)
            {
                new_process->state = ADMISSION;
            }
            else
            {
                new_process->memory_index[0] = possible_process_index;
            }

            add_external_fragment(
                &process_manager_domain->memory_metrics_first_fit,
                external_fragments(process_manager_domain->memory_first_fit));
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            int possible_process_index = next_fit(
                process_manager_domain->memory_next_fit,
                &process_manager_domain->memory_metrics_next_fit,
                &process_manager_domain->denied_process_next_fit,
                process_index,
                process_size,
                &process_manager_domain->next_fit_index);

            if (possible_process_index == -1)
            {
                new_process->state = ADMISSION;
            }
            else
            {
                new_process->memory_index[1] = possible_process_index;
            }

            add_external_fragment(
                &process_manager_domain->memory_metrics_next_fit,
                external_fragments(process_manager_domain->memory_next_fit));
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
            int possible_process_index = best_fit(
                process_manager_domain->memory_best_fit,
                &process_manager_domain->memory_metrics_best_fit,
                &process_manager_domain->denied_process_best_fit,
                process_index,
                process_size);

            if (possible_process_index == -1)
            {
                new_process->state = ADMISSION;
            }
            else
            {
                new_process->memory_index[2] = possible_process_index;
            }

            add_external_fragment(
                &process_manager_domain->memory_metrics_best_fit,
                external_fragments(process_manager_domain->memory_best_fit));
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
            int possible_process_index = worst_fit(
                process_manager_domain->memory_worst_fit,
                &process_manager_domain->memory_metrics_worst_fit,
                &process_manager_domain->denied_process_worst_fit,
                process_index,
                process_size);

            if (possible_process_index == -1)
            {
                new_process->state = ADMISSION;
            }
            else
            {
                new_process->memory_index[3] = possible_process_index;
            }

            add_external_fragment(
                &process_manager_domain->memory_metrics_worst_fit,
                external_fragments(process_manager_domain->memory_worst_fit));
        }

        aux_pointer_list = aux_pointer_list->next;
    }
}

void print_memories(domain *process_manager_domain)
{
    pointer_list aux_pointer_list;
    aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;
    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == FIRST_FIT)
        {
            print_main_memory(process_manager_domain->memory_first_fit, FIRST_FIT);
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            print_main_memory(process_manager_domain->memory_next_fit, NEXT_FIT);
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
            print_main_memory(process_manager_domain->memory_best_fit, BEST_FIT);
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
            print_main_memory(process_manager_domain->memory_worst_fit, WORST_FIT);
        }

        aux_pointer_list = aux_pointer_list->next;
    }
}

void print_metrics(domain *process_manager_domain)
{
    pointer_list aux_pointer_list;
    aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;
    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == FIRST_FIT)
        {
            print_memory_with_metrics(
                process_manager_domain->memory_first_fit,
                &process_manager_domain->memory_metrics_first_fit,
                FIRST_FIT);
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            print_memory_with_metrics(
                process_manager_domain->memory_next_fit,
                &process_manager_domain->memory_metrics_next_fit,
                NEXT_FIT);
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
            print_memory_with_metrics(
                process_manager_domain->memory_best_fit,
                &process_manager_domain->memory_metrics_best_fit,
                BEST_FIT);
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
            print_memory_with_metrics(
                process_manager_domain->memory_worst_fit,
                &process_manager_domain->memory_metrics_worst_fit,
                WORST_FIT);
        }

        aux_pointer_list = aux_pointer_list->next;
    }

    print_legend_memory_with_metrics();
}

int highest_value_by_allocation_algorithms(domain *process_manager_domain, int using_40_percent)
{
    int value = 0;

    pointer_list aux_pointer_list;
    aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;
    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == FIRST_FIT)
        {
            value = highest_value_in_memory(process_manager_domain->memory_first_fit, using_40_percent);
            break;
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            value = highest_value_in_memory(process_manager_domain->memory_next_fit, using_40_percent);
            break;
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
            value = highest_value_in_memory(process_manager_domain->memory_best_fit, using_40_percent);
            break;
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
            value = highest_value_in_memory(process_manager_domain->memory_worst_fit, using_40_percent);
            break;
        }

        aux_pointer_list = aux_pointer_list->next;
    }

    return value;
}

void relocate_process(domain *process_manager_domain, process_table *new_process)
{
    if (
        !verify_if_is_empty_custom(&process_manager_domain->denied_process_first_fit) ||
        !verify_if_is_empty_custom(&process_manager_domain->denied_process_next_fit) ||
        !verify_if_is_empty_custom(&process_manager_domain->denied_process_best_fit) ||
        !verify_if_is_empty_custom(&process_manager_domain->denied_process_worst_fit))
    {
        // o processo precisa saber o index
        pointer_list aux_pointer_list;
        aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;

        int dequeue_values[2];

        while (aux_pointer_list != NULL)
        {
            if (aux_pointer_list->content.value == FIRST_FIT && !verify_if_is_empty_custom(&process_manager_domain->denied_process_first_fit))
            {
                dequeue_custom(&process_manager_domain->denied_process_first_fit, dequeue_values);

                first_fit(
                    process_manager_domain->memory_first_fit,
                    &process_manager_domain->memory_metrics_first_fit,
                    &process_manager_domain->denied_process_first_fit,
                    dequeue_values[0],
                    dequeue_values[1]);

                add_external_fragment(
                    &process_manager_domain->memory_metrics_first_fit,
                    external_fragments(process_manager_domain->memory_first_fit));
            }
            if (aux_pointer_list->content.value == NEXT_FIT && !verify_if_is_empty_custom(&process_manager_domain->denied_process_next_fit))
            {
                dequeue_custom(&process_manager_domain->denied_process_next_fit, dequeue_values);

                next_fit(
                    process_manager_domain->memory_next_fit,
                    &process_manager_domain->memory_metrics_next_fit,
                    &process_manager_domain->denied_process_next_fit,
                    dequeue_values[0],
                    dequeue_values[1],
                    &process_manager_domain->next_fit_index);

                add_external_fragment(
                    &process_manager_domain->memory_metrics_next_fit,
                    external_fragments(process_manager_domain->memory_next_fit));
            }
            if (aux_pointer_list->content.value == BEST_FIT && !verify_if_is_empty_custom(&process_manager_domain->denied_process_best_fit))
            {
                dequeue_custom(&process_manager_domain->denied_process_best_fit, dequeue_values);

                best_fit(
                    process_manager_domain->memory_best_fit,
                    &process_manager_domain->memory_metrics_best_fit,
                    &process_manager_domain->denied_process_best_fit,
                    dequeue_values[0],
                    dequeue_values[1]);

                add_external_fragment(
                    &process_manager_domain->memory_metrics_best_fit,
                    external_fragments(process_manager_domain->memory_best_fit));
            }
            if (aux_pointer_list->content.value == WORST_FIT && !verify_if_is_empty_custom(&process_manager_domain->denied_process_worst_fit))
            {
                dequeue_custom(&process_manager_domain->denied_process_worst_fit, dequeue_values);

                worst_fit(
                    process_manager_domain->memory_worst_fit,
                    &process_manager_domain->memory_metrics_worst_fit,
                    &process_manager_domain->denied_process_worst_fit,
                    dequeue_values[0],
                    dequeue_values[1]);

                add_external_fragment(
                    &process_manager_domain->memory_metrics_worst_fit,
                    external_fragments(process_manager_domain->memory_worst_fit));
            }

            aux_pointer_list = aux_pointer_list->next;
        }
    }
    else
    {
        return;
    }
}

void deallocate_process_domain(domain *process_manager_domain, process_table *new_process, int executing_state)
{
    pointer_list aux_pointer_list;
    aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;

    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == FIRST_FIT)
        {
            if (new_process[executing_state].memory_index[0] != -1)
            {
                deallocate(process_manager_domain->memory_first_fit, executing_state);
                new_process[executing_state].memory_index[0] = -1;
            }
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            if (new_process[executing_state].memory_index[1] != -1)
            {
                deallocate(process_manager_domain->memory_next_fit, executing_state);
                new_process[executing_state].memory_index[1] = -1;
            }
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
            if (new_process[executing_state].memory_index[2] != -1)
            {
                deallocate(process_manager_domain->memory_best_fit, executing_state);
                new_process[executing_state].memory_index[2] = -1;
            }
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
            if (new_process[executing_state].memory_index[3] != -1)
            {
                deallocate(process_manager_domain->memory_worst_fit, executing_state);
                new_process[executing_state].memory_index[3] = -1;
            }
        }

        aux_pointer_list = aux_pointer_list->next;
    }
}

void print_queue_denied_process(domain *process_manager_domain)
{
    printf("==============================================================\n");
    printf("|                       \e[1;93mDENIED PROCESS\033[0m                       |\n");
    printf("==============================================================\n");

    pointer_list aux_pointer_list;
    aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;

    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == FIRST_FIT)
        {
            printf("\033[38;5;196m  (1) \e[1;97m - FIRST FIT => ");
            print_queue_custom(&process_manager_domain->denied_process_first_fit);
            printf("\n");
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            printf("\033[38;5;196m  (2) \e[1;97m - NEXT FIT => ");
            print_queue_custom(&process_manager_domain->denied_process_next_fit);
            printf("\n");
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
            printf("|                     \033[38;5;196m  (3) \e[1;97m - BEST FIT => ");
            print_queue_custom(&process_manager_domain->denied_process_best_fit);
            printf("\n");
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
            printf("|                     \033[38;5;196m  (4) \e[1;97m - WORST FIT => ");
            print_queue_custom(&process_manager_domain->denied_process_worst_fit);
            printf("\n");
        }

        aux_pointer_list = aux_pointer_list->next;
    }

    printf("\n\n");
}