#include "../headers/components/main_memory.h"
#include "../headers/log/log.h"

int main(int argc, char const *argv[])
{
    generate();

    list allocation_algorithms;
    make_empty_list(&allocation_algorithms);

    int input_type, continue_input;

    do
    {
        menu_main_memory();
        scanf("%d", &input_type);

        if (input_type != 1 && input_type != 2 && input_type != 3 && input_type != 4)
        {
            logger("\nError! Invalid input!\n", ERROR_COLOR);
            printf("----------> ");
        }
        else
        {
            if (element_already_exists(&allocation_algorithms, input_type) == 1)
            {
                logger("\nError! You already chose this option!\n", ERROR_COLOR);
                printf("----------> ");
            }
            else
            {
                key tmp;
                tmp.value = input_type;
                insert_in_list(&allocation_algorithms, tmp);
            }
        }

        printf("Do you want to choose one more algorithm? (1) yes; (2) no: ");
        scanf("%d", &continue_input);
    } while (continue_input != 2);

    printf("\n");

    main_memory *memory_ff; // memória principal first fit
    main_memory *memory_nf; // memória principal next fit
    main_memory *memory_bf; // memória principal best fit
    main_memory *memory_wf; // memória principal worst fit

    metrics memory_metrics_ff; // métricas first fit
    metrics memory_metrics_nf; // métricas next fit
    metrics memory_metrics_bf; // métricas best fit
    metrics memory_metrics_wf; // métricas worst fit

    queue denied_process_ff; // fila de processos negagod => first fit
    queue denied_process_nf; // fila de processos negagod => next fit
    queue denied_process_bf; // fila de processos negagod => best fit
    queue denied_process_wf; // fila de processos negagod => worst fit

    pointer_list aux_pointer_list;
    aux_pointer_list = allocation_algorithms.first->next;
    while (aux_pointer_list != NULL)
    {
        if (aux_pointer_list->content.value == 1)
        {
            memory_ff = init_main_memory();
            initialize_metrics(&memory_metrics_ff);
            init_queue(&denied_process_ff);
        }
        if (aux_pointer_list->content.value == 2)
        {
            memory_nf = init_main_memory();
            initialize_metrics(&memory_metrics_nf);
            init_queue(&denied_process_nf);
        }
        if (aux_pointer_list->content.value == 3)
        {
            memory_bf = init_main_memory();
            initialize_metrics(&memory_metrics_bf);
            init_queue(&denied_process_bf);
        }
        if (aux_pointer_list->content.value == 4)
        {
            memory_wf = init_main_memory();
            initialize_metrics(&memory_metrics_wf);
            init_queue(&denied_process_wf);
        }

        aux_pointer_list = aux_pointer_list->next;
    }

    int highest_value = highest_value_in_memory(memory_ff);

    srand(time(NULL));

    int next_fit_index = 0;

    for (int i = 0; i < 6; i++)
    {
        int process_size = 1 + rand() % highest_value;

        printf("VALOR = %d\n", process_size);

        first_fit(memory_ff, &memory_metrics_ff, &denied_process_ff, process_size);
        next_fit(memory_nf, &memory_metrics_nf, &denied_process_nf, process_size, &next_fit_index);
        best_fit(memory_bf, &memory_metrics_bf, &denied_process_bf, process_size);
        worst_fit(memory_wf, &memory_metrics_wf, &denied_process_wf, process_size);

        add_external_fragment(&memory_metrics_ff, external_fragments(memory_ff));
        add_external_fragment(&memory_metrics_nf, external_fragments(memory_nf));
        add_external_fragment(&memory_metrics_bf, external_fragments(memory_bf));
        add_external_fragment(&memory_metrics_wf, external_fragments(memory_wf));
    }

    print_main_memory(memory_ff);
    print_main_memory(memory_nf);
    print_main_memory(memory_bf);
    print_main_memory(memory_wf);

    print_memory_with_metrics(memory_ff, &memory_metrics_ff);
    print_memory_with_metrics(memory_nf, &memory_metrics_nf);
    print_memory_with_metrics(memory_bf, &memory_metrics_bf);
    print_memory_with_metrics(memory_wf, &memory_metrics_wf);

    printf("\nLIST DE PROCESSOS NEGADOS\n");
    print_queue(&denied_process_ff);
    print_queue(&denied_process_bf);
    print_queue(&denied_process_nf);
    print_queue(&denied_process_wf);

    return 0;
}