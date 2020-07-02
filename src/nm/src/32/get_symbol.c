/*
** EPITECH PROJECT, 2020
** get_symbol
** File description:
** get_symbol
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "nm_tt.h"

symbol32_t *get_32_syms(int i, Elf32_Shdr *header, Elf32_Ehdr *elf,
symbol32_t *symbol_list)
{
    Elf32_Sym *sym = (Elf32_Sym *)((char *)elf + header[i].sh_offset);
    int strtab_offset;
    int name_offset;
    char *name;

    for (int j = 0; j < header[i].sh_size / header[i].sh_entsize; j++) {
        strtab_offset = (&header[(&header[i])->sh_link])->sh_offset;
        name_offset = (&((Elf32_Sym *)((char *)elf +
            (&header[i])->sh_offset))[j])->st_name;
        name = (char *)elf + strtab_offset + name_offset;
        if ((sym[j].st_value != 0 && strcmp(name, "") != 0 &&
        sym[j].st_info != STT_SECTION && sym[j].st_info != STT_FILE) ||
        (strcmp(name, "") != 0 && sym[j].st_info != STT_SECTION &&
        sym[j].st_info != STT_FILE))
            !symbol_list ? symbol_list = create_32_first_node(sym[j].st_value,
            get_32_flag(sym[j], header), name, symbol_list) : create_32_node(
            sym[j].st_value, get_32_flag(sym[j], header), name, symbol_list);
    }
    return symbol_list;
}

symbol32_t *get_32_symbol(Elf32_Ehdr *elf, symbol32_t *symbol_list)
{
    Elf32_Shdr *header = get_32_elf_sheader(elf);
    Elf32_Sym *syms;

    for (int i = 0; i < elf->e_shnum; i++) {
        if (header[i].sh_type == SHT_SYMTAB) {
            symbol_list = get_32_syms(i, header, elf, symbol_list);
            sort_32_struct(symbol_list);
            display_32_symbol(symbol_list);
        }
    }
}