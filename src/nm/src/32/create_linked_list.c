/*
** EPITECH PROJECT, 2020
** create_linked_list
** File description:
** create_linked_list
*/

#include <stdlib.h>

#include "nm_tt.h"

symbol32_t *create_32_first_node(unsigned long symbol, char flag, char *name,
symbol32_t *symbol_list)
{
    symbol32_t *new_node = malloc(sizeof(symbol32_t));

    new_node->symbol = symbol;
    new_node->flag = flag;
    new_node->name = name;
    new_node->next = NULL;
    return new_node;
}

void create_32_node(unsigned long symbol, char flag, char *name,
symbol32_t *symbol_list)
{
    symbol32_t *temporary = symbol_list;
    symbol32_t *new_node = malloc(sizeof(symbol32_t));

    new_node->symbol = symbol;
    new_node->flag = flag;
    new_node->name = name;
    new_node->next = NULL;
    for (; temporary->next; temporary = temporary->next);
    temporary->next = new_node;
}