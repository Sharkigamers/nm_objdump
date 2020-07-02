/*
** EPITECH PROJECT, 2020
** create_linked_list
** File description:
** create_linked_list
*/

#include <stdlib.h>

#include "nm_sf.h"

symbol64_t *create_64_first_node(unsigned long symbol, char flag, char *name,
symbol64_t *symbol_list)
{
    symbol64_t *new_node = malloc(sizeof(symbol64_t));

    new_node->symbol = symbol;
    new_node->flag = flag;
    new_node->name = name;
    new_node->next = NULL;
    return new_node;
}

void create_64_node(unsigned long symbol, char flag, char *name,
symbol64_t *symbol_list)
{
    symbol64_t *temporary = symbol_list;
    symbol64_t *new_node = malloc(sizeof(symbol64_t));

    new_node->symbol = symbol;
    new_node->flag = flag;
    new_node->name = name;
    new_node->next = NULL;
    for (; temporary->next; temporary = temporary->next);
    temporary->next = new_node;
}