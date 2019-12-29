#ifndef _EXAMINE_H_
#define _EXAMINE_H_
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>
int verify_elf_magic(Elf32_Ehdr* elfHeader);
uint64_t get_entrypoint(Elf32_Ehdr* elfHeader);
Elf32_Shdr* get_section_headers(Elf32_Ehdr* elfHeader, char* mapped_file);
/*int map_file(char* file_path, char** out_map_file, int file_size);*/
int map_file(char *file_path, char **mapped_file_p);

uint16_t get_shstrtab_index(Elf32_Ehdr* elf_header);
uint16_t get_section_header_number(Elf32_Ehdr* elf_header);
uint16_t get_section_header_offset(Elf32_Ehdr* elf_header);
char* data_enc_format_to_str(unsigned char ei_data);
char get_data_encoding_format(Elf32_Ehdr* elfHeader);

int calc_file_size(int fd);

#endif