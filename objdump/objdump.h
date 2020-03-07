/*
** EPITECH PROJECT, 2020
**
** File description:
** TODO: Add description
*/

#ifndef PSU_NMOBJDUMP_2019_OBJDUMP_H
#define PSU_NMOBJDUMP_2019_OBJDUMP_H

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <zconf.h>
#include <sys/mman.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int key;
    char *str;
} map_t;

void dump_flags(unsigned long flags);

int dump_32(char *filename, void *data);

int dump_64(char *filename, void *data);

void print_bytes(unsigned long position, FILE *fp,
        unsigned long size, int *i);

char *machine_name_32(Elf32_Ehdr *elf);

char *machine_name_64(Elf64_Ehdr *elf);

void read_at_position(unsigned long address, unsigned long position,
        unsigned long size, char *file);

#endif //PSU_NMOBJDUMP_2019_OBJDUMP_H
