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
//            generate_address(1);
            process_manager_domain->memory_first_fit = init_main_memory();
            initialize_metrics(&process_manager_domain->memory_metrics_first_fit);
            init_queue(&process_manager_domain->denied_process_first_fit);
        //    made_address(process_manager_domain->memory_first_fit);
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
//            generate_address(2);
            process_manager_domain->memory_next_fit = init_main_memory();
            initialize_metrics(&process_manager_domain->memory_metrics_next_fit);
            init_queue(&process_manager_domain->denied_process_next_fit);
        //    made_address(process_manager_domain->memory_next_fit);
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
//            generate_address(3);
            process_manager_domain->memory_best_fit = init_main_memory();
            initialize_metrics(&process_manager_domain->memory_metrics_best_fit);
            init_queue(&process_manager_domain->denied_process_best_fit);
        //    made_address(process_manager_domain->memory_best_fit);
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
//            generate_address(4);
            process_manager_domain->memory_worst_fit = init_main_memory();
            initialize_metrics(&process_manager_domain->memory_metrics_worst_fit);
            init_queue(&process_manager_domain->denied_process_worst_fit);
        //    made_address(process_manager_domain->memory_worst_fit);
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

void allocate_new_process(domain *process_manager_domain, process_table *new_process, int first_process)
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
            new_process->memory_index[0] = first_fit(
                process_manager_domain->memory_first_fit,
                &process_manager_domain->memory_metrics_first_fit,
                &process_manager_domain->denied_process_first_fit,
                process_size);

            add_external_fragment(
                &process_manager_domain->memory_metrics_first_fit,
                external_fragments(process_manager_domain->memory_first_fit));
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            new_process->memory_index[1] = next_fit(
                process_manager_domain->memory_next_fit,
                &process_manager_domain->memory_metrics_next_fit,
                &process_manager_domain->denied_process_next_fit,
                process_size,
                &process_manager_domain->next_fit_index);

            add_external_fragment(
                &process_manager_domain->memory_metrics_next_fit,
                external_fragments(process_manager_domain->memory_next_fit));
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
            new_process->memory_index[2] = best_fit(
                process_manager_domain->memory_best_fit,
                &process_manager_domain->memory_metrics_best_fit,
                &process_manager_domain->denied_process_best_fit,
                process_size);

            add_external_fragment(
                &process_manager_domain->memory_metrics_best_fit,
                external_fragments(process_manager_domain->memory_best_fit));
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
            new_process->memory_index[3] = worst_fit(
                process_manager_domain->memory_worst_fit,
                &process_manager_domain->memory_metrics_worst_fit,
                &process_manager_domain->denied_process_worst_fit,
                process_size);

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

void relocate_process(domain *process_manager_domain)
{
    // o processo precisa saber o index

    pointer_list aux_pointer_list;
    aux_pointer_list = process_manager_domain->allocation_algorithms.first->next;
    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == FIRST_FIT)
        {
            first_fit(
                process_manager_domain->memory_first_fit,
                &process_manager_domain->memory_metrics_first_fit,
                &process_manager_domain->denied_process_first_fit,
                dequeue(&process_manager_domain->denied_process_first_fit));

            add_external_fragment(
                &process_manager_domain->memory_metrics_first_fit,
                external_fragments(process_manager_domain->memory_first_fit));
        }
        if (aux_pointer_list->content.value == NEXT_FIT)
        {
            next_fit(
                process_manager_domain->memory_next_fit,
                &process_manager_domain->memory_metrics_next_fit,
                &process_manager_domain->denied_process_next_fit,
                dequeue(&process_manager_domain->denied_process_next_fit),
                &process_manager_domain->next_fit_index);

            add_external_fragment(
                &process_manager_domain->memory_metrics_next_fit,
                external_fragments(process_manager_domain->memory_next_fit));
        }
        if (aux_pointer_list->content.value == BEST_FIT)
        {
            best_fit(
                process_manager_domain->memory_best_fit,
                &process_manager_domain->memory_metrics_best_fit,
                &process_manager_domain->denied_process_best_fit,
                dequeue(&process_manager_domain->denied_process_best_fit));

            add_external_fragment(
                &process_manager_domain->memory_metrics_best_fit,
                external_fragments(process_manager_domain->memory_best_fit));
        }
        if (aux_pointer_list->content.value == WORST_FIT)
        {
            worst_fit(
                process_manager_domain->memory_worst_fit,
                &process_manager_domain->memory_metrics_worst_fit,
                &process_manager_domain->denied_process_worst_fit,
                dequeue(&process_manager_domain->denied_process_worst_fit));

            add_external_fragment(
                &process_manager_domain->memory_metrics_worst_fit,
                external_fragments(process_manager_domain->memory_worst_fit));
        }

        aux_pointer_list = aux_pointer_list->next;
    }
}