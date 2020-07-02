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

#include "my_objdump_sf.h"

void *get_64_elf(const char *file)
{
    void *buf;
    struct stat status_info;
    Elf64_Ehdr *elf = NULL;
    int fd = open(file, O_RDONLY);

    if (fd != -1) {
        fstat(fd, &status_info);
        buf = mmap(NULL, status_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (buf != (void *)-1)
            elf = buf;
        else
            perror("mmap");
        close(fd);
        if (strncmp(elf->e_ident, ELFMAG, 4) != 0) {
            fprintf(stderr, "objdump: %s: file format not recognized\n", file);
            return NULL;
        }
    } else
        fprintf(stderr, "objdump: '%s': No such file\n", file);
    return elf;
}

int my_64_objdump(const char *filepath)
{
    Elf64_Ehdr *elf = get_64_elf(filepath);

    if (!elf)
        return 84;
    printf("\n%s:     file format %s\n", filepath, "elf64-x86-64");
    display_64_header(elf, filepath);
    get_64_section(elf);
    return 0;
}
