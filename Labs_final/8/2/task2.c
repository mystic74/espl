#include <stdlib.h>
#include<string.h>
#include "../0/c/examine.h"
#include <elf.h>
#include <stdio.h>

union file_convert { 
    char* p_mapped_file;
    Elf32_Ehdr* elfHeader;
}; 
  

#define SYM_P_FORMAT "[%2d] %15x %8d %10s %40s \n"
#define SYM_HEAD "[%2s] %15s %8s %10s %40s \n", "ID", "Value", "Sec ID", "Sec name", "Symbol name"


void p_sym_table(Elf32_Shdr *cur_section, char *mapped_file, Elf32_Shdr *str_table,
                     int section_index, char *section_name)
{
    int num_of_symbols = cur_section->sh_size / cur_section->sh_entsize;
    Elf32_Sym cur_symbol;

    int index;
    for (index = 0; index < num_of_symbols; index++)
    {
        cur_symbol = *(Elf32_Sym *)(mapped_file + cur_section->sh_offset + index * cur_section->sh_entsize);

        printf("[%2d] %8x %10x %15s %40s \n",
               index,
               cur_symbol.st_value,
               section_index,
               section_name,
               mapped_file + cur_symbol.st_name + str_table->sh_offset);
    }
}

void print_tables(union file_convert elfUnion)
{
    int i;
    Elf32_Shdr* section_headers = get_section_headers(elfUnion.elfHeader, elfUnion.p_mapped_file);
    char* section_str_table     = elfUnion.p_mapped_file + section_headers[get_shstrtab_index(elfUnion.elfHeader)].sh_offset;
    char* curr_name             = NULL;
   
    printf("[%2s] %8s %10s %15s %40s \n", "ID", "Value", "Sec ID", "Sec name", "Symbol name");
    for (i = 0; i < get_section_header_number(elfUnion.elfHeader); i++)
    {
        curr_name = section_str_table + section_headers[i].sh_name;

        if ((section_headers[i].sh_type == SHT_SYMTAB) || (section_headers[i].sh_type == SHT_DYNSYM))       
        {
            p_sym_table(&(section_headers[i]), elfUnion.p_mapped_file, &(section_headers[section_headers[i].sh_link]), i, curr_name);
        }
    }

    free(section_headers);
}

int main(int argc, char const *argv[])
{
    union file_convert my_uni;
    char* file_path = (char *)argv[1];

    if (map_file(file_path, &(my_uni.p_mapped_file)) != 0)
        return 1;

    if (verify_elf_magic(my_uni.elfHeader) != 0)
        return 1;

    Elf32_Shdr *section_headers = get_section_headers(my_uni.elfHeader, my_uni.p_mapped_file);

    print_tables(my_uni);

    free(section_headers);
    return 0;
}