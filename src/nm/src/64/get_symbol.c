/*
** EPITECH PROJECT, 2020
** get_symbol
** File description:
** get_symbol
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "nm_sf.h"

symbol64_t *get_64_syms(int i, Elf64_Shdr *header, Elf64_Ehdr *elf,
symbol64_t *symbol_list)
{
    Elf64_Sym *sym = (Elf64_Sym *)((char *)elf + header[i].sh_offset);
    int strtab_offset;
    int name_offset;
    char *name;

    for (int j = 0; j < header[i].sh_size / header[i].sh_entsize; j++) {
        strtab_offset = (&header[(&header[i])->sh_link])->sh_offset;
        name_offset = (&((Elf64_Sym *)((char *)elf +
            (&header[i])->sh_offset))[j])->st_name;
        name = (char *)elf + strtab_offset + name_offset;
        if ((sym[j].st_value != 0 && strcmp(name, "") != 0 &&
        sym[j].st_info != STT_SECTION && sym[j].st_info != STT_FILE) ||
        (strcmp(name, "") != 0 && sym[j].st_info != STT_SECTION &&
        sym[j].st_info != STT_FILE))
            !symbol_list ? symbol_list = create_64_first_node(sym[j].st_value,
            get_64_flag(sym[j], header), name, symbol_list) : create_64_node(
            sym[j].st_value, get_64_flag(sym[j], header), name, symbol_list);
    }
    return symbol_list;
}

symbol64_t *get_64_symbol(Elf64_Ehdr *elf, symbol64_t *symbol_list)
{
    Elf64_Shdr *header = get_64_elf_sheader(elf);
    Elf64_Sym *syms;

    for (int i = 0; i < elf->e_shnum; i++) {
        if (header[i].sh_type == SHT_SYMTAB) {
            symbol_list = get_64_syms(i, header, elf, symbol_list);
            sort_64_struct(symbol_list);
            display_64_symbol(symbol_list);
        }
    }
}