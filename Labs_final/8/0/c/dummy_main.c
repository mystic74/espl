#include "examine.h"
#include <stdio.h>

union file_convert { 
    char* p_mapped_file;
    Elf32_Ehdr* elfHeader;
}; 

int main(int argc, char** argv)
{
	union file_convert my_uni;
    char* file_path = (char *)argv[1];

    if (map_file(file_path, &(my_uni.p_mapped_file)) != 0)
        return 1;

    if (verify_elf_magic(my_uni.elfHeader) != 0)
        return 1;

    printf("Entry point : %lx \n" ,get_entrypoint(my_uni.elfHeader));
    printf("File offset : %x \n", get_section_header_offset(my_uni.elfHeader));
    printf("number of sections : %x \n", get_section_header_number(my_uni.elfHeader));
    printf("index of shstrtab : %x \n",get_shstrtab_index(my_uni.elfHeader));
}