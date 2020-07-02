/*
** EPITECH PROJECT, 2020
** nm
** File description:
** nm
*/

#ifndef NM_TT_H_
#define NM_TT_H_

#include <elf.h>

typedef struct symbol_list_32
{
    unsigned long symbol;
    char flag;
    char *name;
    struct symbol_list_32 *next;
} symbol32_t;

static inline Elf32_Shdr *get_32_elf_sheader(Elf32_Ehdr *hdr) {
    return (Elf32_Shdr *)((uint64_t)hdr + hdr->e_shoff);
}

int my_32_nm(const char *filepath, int ac);
symbol32_t *get_32_symbol(Elf32_Ehdr *elf, symbol32_t *symbol_list);
void sort_32_struct(symbol32_t *symbol_list);

symbol32_t *create_32_first_node(unsigned long symbol, char flag, char *name,
symbol32_t *symbol_list);
void create_32_node(unsigned long symbol, char flag, char *name,
symbol32_t *symbol_list);

void display_32_symbol(symbol32_t *symbol_list);

static inline char get_32_flag(Elf32_Sym sym, Elf32_Shdr *shdr)
{
    char  flag;

    if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        flag = 'u';
    else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK &&
    ELF32_ST_TYPE(sym.st_info) == STT_OBJECT) {
        flag = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            flag = 'v';
    } else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK) {
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
    if (ELF32_ST_BIND(sym.st_info) == STB_LOCAL && flag != '?')
        flag += 32;
    if (flag == '?')
        flag = 't';
    return flag;
}

#endif /* !NM_TT_H_ */
