#include <mm.h>

void init_satp() 
{
	int num = 0;
    write_csr_enum(csr_satp, set_field(read_csr_enum(csr_satp), SATP_VALUE, 1));
	num += 1;
}   

void init_sstatus()
{
	write_csr_enum(csr_sstatus, set_field(read_csr_enum(csr_sstatus), 1 << 18, 1));
}

uint64_t read_memory(uint64_t* p)
{
    return ((uint64_t)(*p));
}

void write_memory(uint64_t* p, uint64_t v)
{
    *p = v;
}

uint64_t read_truncate_num(uint64_t num, int l, int r)
{
	uint64_t t = 1;
	return (num >> l) & ((t << (r - l + 1)) - 1);
	// return (MID_BITS(num, l, r + 1));
}

uint64_t write_truncate_num(uint64_t num, uint64_t w_num, int l, int r)
{
	for(int i = l;i <= r;i++) 
		num &= ~(1 << i);
	num |= w_num << l;
	return num;
}

uint64_t get_page_addr(uint64_t v_page_num, int level)
{
	uint64_t va = v_page_num << 12;
	uint64_t vpn2 = read_truncate_num(va, 30, 38);
	uint64_t vpn1 = read_truncate_num(va, 21, 29);
	if (level == 2)
	{
		if (vpn2 == 0)
			return (PAGE_START + 0X1000);
		else // va = 0x8000xxxx, vpn2 = 2
			return (PAGE_START + 0x22000);	// 0x22000 = 34 * 0x1000
	}
	else if(level == 3)
	{
		if (vpn2 == 0)
			return (PAGE_START + 0X2000 + 0X1000 * vpn1);
		else // va = 0x8000xxxx, vpn2 = 2
			return (PAGE_START + 0X23000);  // 0X23000 = 35 * 0X1000		
	}
	else
	{
		;	// throw exception
	}
}

void create_mapping(uint64_t v_page_num, uint64_t p_page_num, int x, int w, int r)
{
	// first level page
	uint64_t va = v_page_num << 12;
	uint64_t pa = p_page_num << 12;
	uint64_t vpn2 = read_truncate_num(va, 30, 38);
    uint64_t vpn1 = read_truncate_num(va, 21, 29);
	if (vpn2 == 0 && vpn1 >= 3 && v_page_num != 0x1002 && v_page_num != 0x2004 && v_page_num != 0x200B) return;	// mark
    uint64_t first_page_addr = PAGE_START + (read_truncate_num(va, 30, 38) << 3);
    uint64_t first_page_content = 0x0;
	first_page_content = write_truncate_num(first_page_content, get_page_addr(v_page_num, 2) >> 12, 10, 53);
    first_page_content = write_truncate_num(first_page_content, 0x1, 0, 0);
    // first_page_content = write_truncate_num(first_page_content, 0x3, 6, 7);
    write_memory((uint64_t*)first_page_addr, first_page_content);
    uint64_t first_pte = read_memory((uint64_t*)first_page_addr);
    // second level page
    uint64_t second_page_addr = (read_truncate_num(first_pte, 10, 53) << 12) | (read_truncate_num(va, 21, 29) << 3);
    uint64_t second_page_content = 0x0;
    second_page_content = write_truncate_num(second_page_content, get_page_addr(v_page_num, 3) >> 12, 10, 53);
    second_page_content = write_truncate_num(second_page_content, 0x1, 0, 0);
    // second_page_content = write_truncate_num(second_page_content, 0x3, 6, 7);
    write_memory((uint64_t*)second_page_addr, second_page_content);
    uint64_t second_pte = read_memory((uint64_t*)second_page_addr);
    // third level page
    uint64_t third_page_addr = (read_truncate_num(second_pte, 10, 53) << 12) | (read_truncate_num(va, 12, 20) << 3);
    uint64_t third_page_content = 0x0;
    third_page_content = write_truncate_num(third_page_content, pa >> 12, 10, 53);
	uint64_t w_num = x * 8 + w * 4 + r * 2 + 1;	// may cause an error
	third_page_content = write_truncate_num(third_page_content, w_num, 0, 3);
    // third_page_content = write_truncate_num(third_page_content, 0x3, 6, 7);
    write_memory((uint64_t*)third_page_addr, third_page_content);
    uint64_t third_pte = read_memory((uint64_t*)third_page_addr);
    // physical addr
}

int test_rwx()
{
	uint64_t content = 0x0;
	uint64_t write_content = 0x1234567812345678;
	uint64_t* text_addr = (uint64_t*)0x3000;
	uint64_t* rodata_addr = (uint64_t*)0x7000;
	uint64_t* other_addr = (uint64_t*)0xb000;
	// test text section
	content = read_memory(text_addr);
	write_memory(text_addr, write_content);
	//  asm volatile ("la ra, 0x3000");
	// asm volatile ("jr ra");
	// test read only section
	content = read_memory(rodata_addr);
	write_memory(rodata_addr, write_content);
	// asm volatile ("la ra, 0x7000");
	// asm volatile ("jr ra");
	// test other section
	content = read_memory(other_addr);
	write_memory(other_addr, write_content);
	asm volatile("la ra, 0xb000");
	asm volatile("jr ra");
	return 1;
}

void total_mapping()
{
	int i = 4096 - 1;
	for (;i >= 0;i--)
	{
		if (i >= 0 && i < 4)
			create_mapping(i + 2, 0x80000 + i, 1, 0, 1);
		else if (i >= 4 && i < 8)
			create_mapping(i + 2, 0x80000 + i, 0, 0, 1);
		else
			create_mapping(i + 2, 0x80000 + i, 0, 1, 1);
	}

	create_mapping(0x80000, 0x80000, 1, 1, 1);
	create_mapping(0x80001, 0x80001, 1, 1, 1);
	create_mapping(0x80002, 0x80002, 1, 1, 1);
	create_mapping(0x0, 0x0, 1, 1, 1);
	create_mapping(0x1002, 0x10000, 1, 1, 1);
	create_mapping(0x2004, 0x2004, 1, 1, 1);
	create_mapping(0x200B, 0x200B, 1, 1, 1);
}
