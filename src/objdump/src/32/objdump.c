/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** objdump
*/

#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <ar.h>

#include "my_objdump_tt.h"

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

int my_32_objdump(const char *filepath)
{
    Elf32_Ehdr *elf = get_32_elf(filepath);

    if (!elf)
        return 84;
    printf("\n%s:     file format %s\n", filepath, "elf32-i386");
    display_32_header(elf, filepath);
    get_32_section(elf);
    return 0;
}
