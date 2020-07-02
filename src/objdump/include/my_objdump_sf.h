/*
** EPITECH PROJECT, 2020
** my_objdump
** File description:
** my_objdump
*/

#ifndef MY_OBJDUMP_SF_H_
#define MY_OBJDUMP_SF_H_

#define NO_FLAGS    0x00
#define HAS_RELOC   0x01
#define EXEC_P      0x02
#define HAS_DEBUG   0x08
#define HAS_SYMS    0x10
#define HAS_LOCALS  0x20
#define DYNAMIC     0x40
#define D_PAGED     0x100

#define HEXA(x) ((x) % 16)
#define QUADRA(x) ((x) % 4)

#define PADDING(size) (((int)strlen(my_itoa(size)) > 4) ?\
    (int)strlen(my_itoa(size)) : 4)

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(*array))

#include <elf.h>

#include <stddef.h>

static inline Elf64_Shdr *get_64_elf_sheader(Elf64_Ehdr *hdr) {
    return (Elf64_Shdr *)((uint64_t)hdr + hdr->e_shoff);
}

static inline Elf64_Shdr *get_64_elf_section(Elf64_Ehdr *hdr, int idx) {
    return &get_64_elf_sheader(hdr)[idx];
}

static inline char *get_64_elf_str_table(Elf64_Ehdr *hdr) {
    if (hdr->e_shstrndx == SHN_UNDEF)
        return NULL;
    return (char *)hdr + get_64_elf_section(hdr, hdr->e_shstrndx)->sh_offset;
}

static inline char *get_64_elf_lookup_string(Elf64_Ehdr *hdr, int offset) {
    char *strtab = get_64_elf_str_table(hdr);
    if (strtab == NULL)
        return NULL;
    return strtab + offset;
}

typedef struct map_of_define_64 {
    int key;
    char *value;
} map64_t;

typedef struct blacklisted_section_64 {
    char *value;
} blacklist64_t;

int my_64_objdump(const char *);
void display_64_header(Elf64_Ehdr *elf, const char *filepath);
void get_64_section(Elf64_Ehdr *elf);

char *my_itoa(int number);

#endif /* !MY_OBJDUMP_SF_H_ */
