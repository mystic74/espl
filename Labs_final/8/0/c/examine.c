#include "examine.h"
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sysexits.h>

#define ELFDATANONE_STR "Invalid data encoding"
#define ELFDATA2LSB_STR "Two's complement, little-endian"
#define ELFDATA2MSB_STR "Two's complement, big endian"

int calc_file_size(int fd)
{
    struct stat st;
    fstat(fd, &st);
    return st.st_size;
}


int verify_elf_magic(Elf32_Ehdr* elfHeader)
{
    if (memcmp(elfHeader->e_ident, ELFMAG, SELFMAG) == 0) {
       return EX_OK;
    }
    return 1;
}

uint64_t get_entrypoint(Elf32_Ehdr* elfHeader)
{
    return elfHeader->e_entry;
}

char get_data_encoding_format(Elf32_Ehdr* elfHeader)
{
    return elfHeader->e_ident[EI_DATA];
}

char* data_enc_format_to_str(unsigned char ei_data)
{
    if (ei_data == ELFDATANONE)
        return ELFDATANONE_STR;

    if (ei_data == ELFDATA2LSB)
        return ELFDATA2LSB_STR;
    
    if (ei_data == ELFDATA2MSB)
        return ELFDATA2MSB_STR;

    return NULL;
}

uint16_t get_section_header_offset(Elf32_Ehdr* elf_header)
{
    return elf_header->e_shentsize;
}

uint16_t get_section_header_number(Elf32_Ehdr* elf_header)
{
    return elf_header->e_shnum;
}

/* The index of the shstrtab in the section header. */
uint16_t get_shstrtab_index(Elf32_Ehdr* elf_header)
{
    return elf_header->e_shstrndx;
}
/*
int map_file(char* file_path, char** out_map_file, int file_size)
{
    int fd = open(file_path, O_RDONLY, 0);
    if (fd == -1)
    {
        printf("Failed to open %s\n", file_path);
        return 1;
    }

    (*out_map_file) = (char *)mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (*out_map_file == MAP_FAILED)
    {
        printf("Failed to Map %s\n", file_path);
        return 1;
    }

    return 0;
}*/


int map_file(char *file_path, char** mapped_file_p)
{
    int fd = open(file_path, O_RDONLY, 0);
    if (fd == -1)
    {
        printf("Failed to open %s\n", file_path);
        return 1;
    }

    int file_size = calc_file_size(fd);

    (*mapped_file_p) = (char *)mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (*mapped_file_p == MAP_FAILED)
    {
        printf("Failed to Map %s\n", file_path);
        return 1;
    }

    return EX_OK;
}

Elf32_Shdr* get_section_headers(Elf32_Ehdr* elfHeader, char* mapped_file)
{
    Elf32_Shdr* section_headers = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr) * elfHeader->e_shnum);

    int index;
    int cur_offset = elfHeader->e_shoff;
    for (index = 0; index < get_section_header_number(elfHeader); index++)
    {
        section_headers[index] = *(Elf32_Shdr *)(mapped_file + cur_offset);
        cur_offset += sizeof(Elf32_Shdr);
    }

    return section_headers;
}

