#include "../../headers/components/virtual_memory.h"

void generate_address()
{
    FILE *fptr;

    int num;
    srand(time(0));

    const char *path1 = "data/address.txt";

    fptr = fopen(path1, "w");

    for (int i = 0; i < SIZE; i++)
    {
        num = (rand() % (65536)) + 1;
        i != SIZE - 1 ? fprintf(fptr, "%d\n", (num)) : fprintf(fptr, "%d", (num));
    }

    fclose(fptr);
}

int read_from_disk(int page_num, char *PM, int *OF)
{
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    for (int i = 0; i < PHYS_MEM_SIZE; i++)
    {
        *((PM + (*OF) * PHYS_MEM_SIZE) + i) = buffer[i];
    }

    (*OF)++;

    return (*OF) - 1;
}

int find_page(int logical_addr, char *page_table, TLB *tlb, char *phys_mem, int *OF, int *page_faults, int *TLB_hits)
{

    unsigned char mask = 0xFF;
    unsigned char offset;
    unsigned char page_num;
    bool TLB_hit = false;
    int frame = 0;
    int new_frame = 0;
    int i;

    printf("Virtual adress: %d ->\t", logical_addr);

    page_num = (logical_addr >> 8) & mask;

    offset = logical_addr & mask;
    for (i = 0; i < TLB_SIZE; i++)
    {
        if (tlb->TLB_page[i] == page_num)
        {
            frame = tlb->TLB_frame[i];
            TLB_hit = true;
            (*TLB_hits)++;
        }
    }

    if (TLB_hit == false)
    {
        if (page_table[page_num] != -1)
        {
            printf("Pagehit\t\t");
        }

        else
        {
            // Criação de uma nova moldura
            new_frame = read_from_disk(page_num, phys_mem, OF);
            page_table[page_num] = new_frame;
            (*page_faults)++;
        }
        frame = page_table[page_num];
        tlb->TLB_page[tlb->ind] = page_num;
        tlb->TLB_frame[tlb->ind] = page_table[page_num];
        tlb->ind = (tlb->ind + 1) % TLB_SIZE;
    }
    int index = ((unsigned char)frame * PHYS_MEM_SIZE) + offset;
    printf("Physical address: %d\n", index);

    return 0;
}

int made_address(main_memory *main_memory)
{

    FILE *fpointer;
    int address;
    int i = 0;
    fpointer = fopen("data/address.txt", "r");

    while (!feof(fpointer))
    {
        fscanf(fpointer, "%d", &address);
        main_memory[i].address = address;
        i++;
    }

    fclose(fpointer);

    return 0;
}