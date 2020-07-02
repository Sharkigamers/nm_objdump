/*
** EPITECH PROJECT, 2020
** nm
** File description:
** nm
*/

#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "nm_tt.h"

void *get_32_elf(const char *file)
{
    struct stat status_info;
    Elf32_Ehdr *elf = NULL;
    int fd = open(file, O_RDONLY);

    if (fd != -1) {
        fstat(fd, &status_info);
        elf = mmap(NULL, status_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (elf == (void *)-1)
            perror("mmap");
        close(fd);
        if (strncmp(elf->e_ident, ELFMAG, 4) != 0) {
            fprintf(stderr, "nm: %s: file format not recognized\n", file);
            return NULL;
        }
    } else
        fprintf(stderr, "nm: '%s': No such file\n", file);
    return elf;
}

int my_32_nm(const char *filepath, int ac)
{
    Elf32_Ehdr *elf = get_32_elf(filepath);
    symbol32_t *symbol_list = NULL;

    if (!elf)
        return 84;
    if (ac > 2)
        printf("\n%s:\n", filepath);
    get_32_symbol(elf, symbol_list);
    return 0;
}
