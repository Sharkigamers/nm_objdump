/*
** EPITECH PROJECT, 2020
** sort_struct
** File description:
** sort_struct
*/

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "nm_tt.h"

int my_32_special_strcmp(char const *s1, char const *s2, char flag1, char flag2)
{
    int i = 0;
    int j = 0;

    for (; s1[i] == '_' && s1[i] != '\0'; ++i);
    for (; s2[j] == '_' && s2[j] != '\0'; ++j);
    while (s1[i] == s2[j] && (s1[i] != '\0' && s2[j] != '\0')) {
        if (s1[i] == '\0' || s2[j] == '\0')
            return s1[i] - s2[j];
        ++i;
        ++j;
        for (; s1[i] == '_' && s1[i] != '\0'; ++i);
        for (; s2[j] == '_' && s2[j] != '\0'; ++j);
    }
    if (s1[i] == s2[j])
        return tolower(flag1) - tolower(flag2);
    return s1[i] - s2[j];
}

int compare_32_names(const char *s1, const char *s2, char flag1, char flag2)
{
    char *dumped_s1 = strdup(s1);
    char *dumped_s2 = strdup(s2);
    int return_value;

    for (int i = 0; dumped_s1[i]; ++i) {
        if (dumped_s1[i] >= 'A' && dumped_s1[i] <= 'Z')
            dumped_s1[i] = tolower(dumped_s1[i]);
    }
    for (int i = 0; dumped_s2[i]; ++i) {
        if (dumped_s2[i] >= 'A' && dumped_s2[i] <= 'Z')
            dumped_s2[i] = tolower(dumped_s2[i]);
    }
    return_value = my_32_special_strcmp(dumped_s1, dumped_s2, flag1, flag2);
    free(dumped_s1);
    free(dumped_s2);
    return return_value;
}

void swap_linked_32_values(symbol32_t *current_list)
{
    unsigned long save_symbol = current_list->symbol;
    char save_flag = current_list->flag;
    char *save_name;

    save_symbol = current_list->symbol;
    save_flag = current_list->flag;
    save_name = current_list->name;
    current_list->symbol = current_list->next->symbol;
    current_list->flag = current_list->next->flag;
    current_list->name = current_list->next->name;
    current_list->next->symbol = save_symbol;
    current_list->next->flag = save_flag;
    current_list->next->name = save_name;
}

void sort_32_struct(symbol32_t *symbol_list)
{
    symbol32_t *current_list;
    int sorted = 0;

    while (sorted < 2) {
        current_list = symbol_list;
        ++sorted;
        for (; current_list && current_list->next;
        current_list = current_list->next) {
            if (compare_32_names(current_list->name, current_list->next->name,
            current_list->flag, current_list->next->flag) > 0) {
                swap_linked_32_values(current_list);
                sorted = 0;
            }
        }
    }
}