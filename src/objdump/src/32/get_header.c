/*
** EPITECH PROJECT, 2020
** get_header
** File description:
** get_header
*/

#include <inttypes.h>
#include <stdint.h>

#include <stdio.h>

#include <elf.h>

#include "my_objdump_tt.h"

void print_32_flags(unsigned short flags)
{
    const static map32_t needed_flags[] = {{NO_FLAGS, "NO_FLAGS"},
    {HAS_RELOC, "HAS_RELOC"}, {EXEC_P, "EXEC_P"}, {HAS_DEBUG, "HAS_DEBUG"},
    {HAS_SYMS, "HAS_SYMS"}, {HAS_LOCALS, "HAS_LOCALS"}, {DYNAMIC, "DYNAMIC"},
    {D_PAGED, "D_PAGED"}};

    for (short i = 0; i < ARRAY_LENGTH(needed_flags); ++i) {
        if (needed_flags[i].key & flags) {
            printf("%s", needed_flags[i].value);
            flags -= needed_flags[i].key;
            if (flags != 0)
                printf(", ");
            else
                printf("\n");
        }
    }
}

char *get_32_architecture(int architecture)
{
    static const map32_t machines[] = {{EM_NONE, "None"}, {EM_M32, "WE32100"},
    {EM_SPARC, "Sparc"}, {EM_386, "i386"}, {EM_68K, "MC68000"},
    {EM_88K, "MC88000"}, {EM_860, "Intel 80860"}, {EM_MIPS, "MIPS R3000"},
    {EM_PARISC, "HPPA"}, {EM_SPARC32PLUS, "Sparc v8+"}, {EM_PPC, "PowerPC"},
    {EM_PPC64, "PowerPC64"}, {EM_S390, "IBM S/390"}, {EM_ARM, "ARM"},
    {EM_SH, "Renesas / SuperH SH"}, {EM_SPARCV9, "Sparc v9"},
    {EM_IA_64, "Intel IA-64"}, {EM_X86_64, "i386:x86-64"}};

    for (int i = 0; i < ARRAY_LENGTH(machines); ++i) {
        if (machines[i].key == architecture)
            return machines[i].value;
    }
    return "i386:x86-64";
}

unsigned short get_32_flags(Elf32_Ehdr *elf)
{
    unsigned short flag = NO_FLAGS;
    Elf32_Shdr *head = (Elf32_Shdr *) ((char *)elf + elf->e_shoff);

    switch (elf->e_type) {
        case (ET_DYN):
            flag += DYNAMIC + D_PAGED;
            break;
        case (ET_EXEC):
            flag += EXEC_P + D_PAGED;
            break;
        case (ET_REL):
            flag += HAS_RELOC;
            break;
    }
    for (int i = 0; i < elf->e_shnum; ++i) {
        if (head[i].sh_type == SHT_SYMTAB || head[i].sh_type == SHT_DYNSYM)
            return flag + HAS_SYMS;
    }
    return flag;
}

void display_32_header(Elf32_Ehdr *elf, const char *filepath)
{
    unsigned short flags = get_32_flags(elf);

    printf("architecture: %s, flags 0x%08x:\n",
    get_32_architecture(elf->e_machine), flags);
    print_32_flags(flags);
    printf("start address 0x%08" PRIxPTR "\n\n", (uintptr_t)elf->e_entry);
}