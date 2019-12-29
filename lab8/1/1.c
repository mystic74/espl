#include "../0/c/examine.h"
#include <elf.h>
#include <stdio.h>

#define SEC_P_FORMAT "[%2d] %20s %15x %10d %10d \n"
#define SEC_HEAD "[%2s] %20s %15s %10s %10s \n", "ID", "Name", "Address", "Offset", "Size"

union test { 
    char* mapped_file;
    Elf32_Ehdr* elfHeader;
}; 
  
/* [index] section_name section_address section_offset section_size */
void print_sctions(char *mapped_file, Elf32_Ehdr *elf_header,
                   Elf32_Shdr *section_headers, int section_headers_num)
{
    char *section_str_table = mapped_file + section_headers[elf_header->e_shstrndx].sh_offset;

    printf(SEC_HEAD);

    int i;
    for (i = 0; i < section_headers_num; i++)
    {
        printf(SEC_P_FORMAT,
               i,
               section_str_table + section_headers[i].sh_name,
               section_headers[i].sh_addr,
               section_headers[i].sh_offset,
               section_headers[i].sh_size);
    }
}

int main(int argc, char** argv)
{
    union test my_uni;
    char* file_path = (char *)argv[1];

    if (map_file(file_path, &(my_uni.mapped_file)) != 0)
        return 1;

    if (verify_elf_magic(my_uni.elfHeader) != 0)
        return 1;

     Elf32_Shdr* section_headers = get_section_headers(my_uni.elfHeader, my_uni.mapped_file);

     print_sctions(my_uni.mapped_file, my_uni.elfHeader, section_headers, get_section_header_number(my_uni.elfHeader));
    return 0;
}