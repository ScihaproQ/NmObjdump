/*
** EPITECH PROJECT, 2020
** oui
** File description:
** TODO: Add description
*/

#include "nm.h"

int remove_underscore(const char *str)
{
    int c = 0;

    for (int i = 0;str[i] && str[i] == '_'; ++i)
        c++;
    return c;
}

void swap(size_t *xp, size_t *yp)
{
    size_t temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort(size_t *addresses, int n, char *str)
{
    Elf64_Sym *a;
    Elf64_Sym *b;
    int offset_a = 0;
    int offset_b = 0;
    char *stra = NULL;
    char *strb = NULL;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            a = (Elf64_Sym *) addresses[j];
            b = (Elf64_Sym *) addresses[j + 1];
            offset_a = remove_underscore(&str[a->st_name]);
            offset_b = remove_underscore(&str[b->st_name]);
            stra = &str[a->st_name] + offset_a;
            strb = &str[b->st_name] + offset_b;
            if (strcasecmp(stra, strb) >= 0)
                swap(&addresses[j], &addresses[j + 1]);
        }
    }
}
