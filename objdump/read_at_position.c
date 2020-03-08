/*
** EPITECH PROJECT, 2020
** oui
** File description:
** TODO: Add description
*/

#include "objdump.h"

void read_at_position(unsigned long address, unsigned long position,
        unsigned long size, char *file)
{
    FILE *f = fopen(file, "rb");
    unsigned long tmp_size = size;

    fseek(f, position, SEEK_CUR);
    for (long unsigned int i = 0; i < size; position += 0x10,
            address += 0x10, tmp_size -= 16)
        print_bytes(address, f, tmp_size, &i);
}
