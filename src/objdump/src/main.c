/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#include "my_objdump_sf.h"
#include "my_objdump_tt.h"

char *my_itoa(int number)
{
    int lenght = 0;
    char *buffer = NULL;

    if (number == 0) {
        buffer = calloc(sizeof(char), 2);
        buffer[0] = '0';
        return (buffer);
    }
    for (int temp = number; temp > 0; temp = temp / 10)
        lenght++;
    buffer = calloc(1, sizeof(char) * (lenght + 1));
    while (lenght--) {
        buffer[lenght] = number % 10  + '0';
        number = number / 10;
    }
    return (buffer);
}

int check_format(const char *file)
{
    struct stat status_info;
    Elf64_Ehdr *elf = NULL;
    int return_value;
    int fd = open(file, O_RDONLY);

    if (fd != -1) {
        fstat(fd, &status_info);
        elf = mmap(NULL, status_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        (elf == (void *)-1) ? perror("mmap") : 0;
        close(fd);
        if (strncmp(elf->e_ident, ELFMAG, 4) != 0) {
            fprintf(stderr, "nm: %s: file format not recognized\n", file);
            exit(84);
        }
        return_value = (elf->e_ident[4] == 1) ? 32 : 64;
    } else {
        fprintf(stderr, "nm: '%s': No such file\n", file);
        exit(84);
    }
    return return_value;
}

int multiple_args(int ac, char **av)
{
    int return_value = 0;

    for (int i = 1; av[i] != NULL; ++i) {
        if (check_format(av[i]) == 32) {
            if (!return_value)
                return_value = my_32_objdump(av[i]);
            else
                my_32_objdump(av[i]);
        } else {
            if (!return_value)
                return_value = my_64_objdump(av[i]);
            else
                my_64_objdump(av[i]);
        }
    }
    return return_value;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        if (check_format("a.out") == 32)
            return my_32_objdump("a.out");
        else
            return my_64_objdump("a.out");
    }
    return multiple_args(ac, av);
}
