/*
** EPITECH PROJECT, 2020
** display_symbol
** File description:
** display_symbol
*/

#include <stdio.h>

#include "nm_tt.h"

void display_32_symbol(symbol32_t *symbol_list)
{
    for (int i = 0; symbol_list; symbol_list = symbol_list->next) {
        if (symbol_list->flag != 'U' && symbol_list->flag != 'w')
            printf("%08lx", symbol_list->symbol);
        else
            printf("        ");
        printf(" %c", symbol_list->flag);
        printf(" %s\n", symbol_list->name);
    }
}
