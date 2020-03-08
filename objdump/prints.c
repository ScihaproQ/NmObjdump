/*
** EPITECH PROJECT, 2020
** oui
** File description:
** TODO: Add description
*/

#include "objdump.h"

void print_address(unsigned long position, unsigned long size)
{
    char buffer[10];

    sprintf(buffer, "%lx", position + size);
    if (strlen(buffer) >= 5)
        printf(" %.5lx", position);
    else
        printf(" %.4lx", position);
}

void print_bytes(unsigned long position, FILE *fp, unsigned long size, int *i)
{
    unsigned char word = 0;
    unsigned char d = 0;
    char *ascii = malloc(16);
    char *hex = malloc(35);
    char *t_char = malloc(3);

    print_address(position, size);
    for (int j = 0; j < 16 && j < size; ++j, (*i)++) {
        if (!(j % 4) && j > 0)
            strcat(hex, " ");
        fread(&word, 1, 1, fp);
        sprintf(t_char, "%.2x", word);
        strncat(hex, t_char, 2);
        d = word;
        if (word <= 0x1F || word >= 0x7F)
            d = '.';
        strncat(ascii, &d, 1);
    }
    printf(" %-35s  %-16s\n", hex, ascii);
}
