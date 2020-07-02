/*
** EPITECH PROJECT, 2020
** nm
** File description:
** nm
*/

#ifndef NM_SF_H_
#define NM_SF_H_

#include <elf.h>

typedef struct symbol_list_64
{
    unsigned long symbol;
    char flag;
    char *name;
    struct symbol_list_64 *next;
} symbol64_t;

static inline Elf64_Shdr *get_64_elf_sheader(Elf64_Ehdr *hdr) {
    return (Elf64_Shdr *)((uint64_t)hdr + hdr->e_shoff);
}

int my_64_nm(const char *filepath, int ac);
symbol64_t *get_64_symbol(Elf64_Ehdr *elf, symbol64_t *symbol_list);
void sort_64_struct(symbol64_t *symbol_list);

symbol64_t *create_64_first_node(unsigned long symbol, char flag, char *name,
symbol64_t *symbol_list);
void create_64_node(unsigned long symbol, char flag, char *name,
symbol64_t *symbol_list);

void display_64_symbol(symbol64_t *symbol_list);

static inline char get_64_flag(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char  flag;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        flag = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
    ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) {
        flag = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            flag = 'v';
    } else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
        flag = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            flag = 'w';
    } else if (sym.st_shndx == SHN_UNDEF)
        flag = 'U';
    else if (sym.st_shndx == SHN_ABS)
        flag = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        flag = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS &&
    shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        flag = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
    shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        flag = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
    shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        flag = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
    shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        flag = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        flag = 'D';
    else
        flag = '?';
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && flag != '?')
        flag += 32;
    if (flag == '?')
        flag = 't';
    return flag;
}

#endif /* !NM_SF_H_ */
