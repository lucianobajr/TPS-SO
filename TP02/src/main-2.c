#include "../headers/components/main_memory.h"
#include "../headers/log/log.h"
#include "../headers/components/virtual_memory.h"

int main(int argc, char const *argv[])
{
    FILE *fpointer;
    generate();
    generate_address();
    bool allocated = true;
    int open_frame = 0;
    int page_faults = 0;
    int TLB_hits = 0;

    unsigned char page_table[PAGE_TABLE_SIZE];
    memset(page_table, -1, sizeof(page_table));

    TLB tlb;
    memset(tlb.TLB_page, -1, sizeof(tlb.TLB_page));
    memset(tlb.TLB_frame, -1, sizeof(tlb.TLB_frame));
    tlb.ind = 0;

    char phy_mem[PHYS_MEM_SIZE][PHYS_MEM_SIZE];

    fpointer = fopen("data/address.txt", "r");
    if (fpointer == NULL){
        printf("Fail trying to open the file!!!\n");
        exit(0);
    }

    list allocation_algorithms;
    make_empty_list(&allocation_algorithms);

    main_memory *memory_ff; // memória principal first fit

    metrics memory_metrics_ff; // métricas first fit

    queue denied_process_ff; // fila de processos negagod => first fit

    memory_ff = init_main_memory();
    initialize_metrics(&memory_metrics_ff);
    init_queue(&denied_process_ff);

    int highest_value = highest_value_in_memory(memory_ff);

    srand(time(NULL));

    int next_fit_index = 0;

    for (int i = 0; i < 6; i++)
    {
        int process_size = 1 + rand() % highest_value;

        printf("VALOR = %d\n", process_size);

        first_fit(memory_ff, &memory_metrics_ff, &denied_process_ff, process_size);

        add_external_fragment(&memory_metrics_ff, external_fragments(memory_ff));
    }

    print_main_memory(memory_ff);

    print_memory_with_metrics(memory_ff, &memory_metrics_ff);

    printf("\nLIST DE PROCESSOS NEGADOS\n");
    print_queue(&denied_process_ff);

    for (int i = 0; i < SIZE; i++)
    {
        memory_ff[i].allocated == 0 ? allocated = false : find_page(memory_ff[i].address, page_table, &tlb, (char*)phy_mem, &open_frame, &page_faults, &TLB_hits);
    }
    
    return 0;
}