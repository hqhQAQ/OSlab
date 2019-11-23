#ifndef MM_H
#define MM_H
#include <csr.h>
#include <machine.h>

#define SATP_VALUE 0x8000000000080020
#define PAGE_START 0x80020000

uint64_t get_pc();
void init_satp();
uint64_t read_memory(uint64_t* p);
void write_memory(uint64_t* p, uint64_t v);
uint64_t read_truncate_num(uint64_t num, int l, int r);
uint64_t write_truncate_num(uint64_t num, uint64_t w_num, int l, int r);
uint64_t get_page_addr(uint64_t v_page_num, int level);
void create_mapping(uint64_t v_page_num, uint64_t p_page_num, int x, int w, int r);
void total_mapping();

#endif
