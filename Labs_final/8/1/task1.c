#include "../0/c/examine.h"
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>

union file_convert { 
    char* p_mapped_file;
    Elf32_Ehdr* elfHeader;
}; 
  
void print_secs(union file_convert elfUnion)
{
    Elf32_Shdr* section_headers = get_section_headers(elfUnion.elfHeader, elfUnion.p_mapped_file);
    char* section_str_table = elfUnion.p_mapped_file + section_headers[get_shstrtab_index(elfUnion.elfHeader)].sh_offset;

    printf("%5s %20s %20s %20s %20s \n",
               "index",
               "section name",
               "section adress",
               "section offset",
               "section size");
    int i;
    for (i = 0; i < get_section_header_number(elfUnion.elfHeader); i++)
    {
        printf("[%5d] %20s %20X %20X %20X \n",
               i,
               section_str_table + section_headers[i].sh_name,
               section_headers[i].sh_addr,
               section_headers[i].sh_offset,
               section_headers[i].sh_size);
    }

    free(section_headers);
}

int main(int argc, char** argv)
{
	union file_convert my_file;

	if (map_file(argv[1],((char**) &(my_file.p_mapped_file))) != 0)
	{
		return 1;
	}

	if (verify_elf_magic(my_file.elfHeader) != 0)
	{
		printf("Invalid magic for elf32, exiting... \n");
		return 1;
	}

	print_secs(my_file);

  return 0;
}