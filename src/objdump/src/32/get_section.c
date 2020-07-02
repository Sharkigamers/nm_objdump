/*
** EPITECH PROJECT, 2020
** 32_get_section
** File description:
** get_section
*/

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "my_objdump_tt.h"

int display_32_tabulation(unsigned int i, bool after_section)
{
    if (after_section && !QUADRA(i + 1))
        printf(" ");
    if (!HEXA(i + 1)) {
        if (after_section)
            printf(" ");
        else
            printf("  ");
        return 1;
    }
    if (!after_section && !QUADRA(i + 1))
        printf(" ");
    return 0;
}

void display_32_second_section(Elf32_Ehdr *elf, Elf32_Shdr header,
unsigned int i)
{
    for (; i < header.sh_size; i++) {
        printf("%02x", (unsigned char) (((char *) elf) + header.sh_offset)[i]);
        if (display_32_tabulation(i, false))
            return;
    }
    if (i >= header.sh_size && HEXA(i)) {
        for (; HEXA(i); i++) {
            printf("  ");
            display_32_tabulation(i, true);
        }
    }
}

void display_32_section(Elf32_Ehdr *elf, Elf32_Shdr header)
{
    unsigned int addr = header.sh_addr;
    unsigned int size = header.sh_size;
    unsigned int i;
    char third_section;

    for (i = 0; i < size; i++) {
        if (!HEXA(i)) {
            printf(" %0*x ", PADDING(size), addr);
            display_32_second_section(elf, header, i);
            addr += 16;
        }
        third_section = (unsigned char) (((char *) elf) + header.sh_offset)[i];
        isprint(third_section) ? printf("%c", third_section) : printf(".");
        !HEXA(i + 1) ? printf("\n") : 0;
    }
    if (HEXA(i)) {
        for (; HEXA(i); ++i)
            printf(" ");
        printf("\n");
    }
}

int blacklist_32_section(char *table, Elf32_Shdr *header, int index)
{
    const static blacklist32_t blacklist[] = {".bss", ".shstrtab",
    ".symtab", ".strtab", ".rela"};

    for (int i = 0; i < ARRAY_LENGTH(blacklist); i++) {
        if (strncmp(table + header[index].sh_name, blacklist[i].value,
        strlen(blacklist[i].value)) == 0 &&
        strcmp(table + header[index].sh_name, ".rela.plt") != 0 &&
        strcmp(table + header[index].sh_name, ".rela.dyn") != 0)
            return 1;
    }
    return 0;
}

void get_32_section(Elf32_Ehdr *elf)
{
    Elf32_Shdr *header = get_32_elf_sheader(elf);
    Elf32_Shdr *section = get_32_elf_section(elf, elf->e_shstrndx);
    char *table = get_32_elf_str_table(elf);
    char *name = get_32_elf_lookup_string(elf, section->sh_offset);

    for (int i = 1; i < elf->e_shnum; i++) {
        if (!blacklist_32_section(table, header, i) && header[i].sh_size > 0) {
            printf("Contents of section %s:\n", table + header[i].sh_name);
            display_32_section(elf, header[i]);
        }
    }
}