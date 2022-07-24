#include "../headers/components/main_memory.h"
#include "../headers/metrics/metrics.h"
#include "../headers/log/log.h"
#include "../headers/components/virtual_memory.h"

int main (){
	
    generate_address();
    main_memory *memory = init_main_memory();
	made_address(memory);
    bool allocated = true;

    FILE *fd;
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

	fd = fopen("data/address.txt", "r");
    if (fd == NULL){
		printf("File failed to open\n");
		exit(0);
	}

	//printf("Value\tPageNum\tOffset\n ");	
	for (int i = 0; i < SIZE; i++){
        if (memory[i].allocated == 0)
        {
            allocated = false;
        }else{
		    find_page(memory[i].address, page_table, &tlb, (char*)phy_mem, &open_frame, &page_faults, &TLB_hits);
        }
        
	}

    return 0;
}