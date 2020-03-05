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

#define BFD_NO_FLAGS    0x00
#define HAS_RELOC       0x01
#define EXEC_P          0x02
#define HAS_LINENO      0x04
#define HAS_DEBUG       0x08
#define HAS_SYMS        0x10
#define HAS_LOCALS      0x20
#define DYNAMIC         0x40
#define WP_TEXT         0x80
#define D_PAGED         0x100

typedef struct {
    int key;
    char *str;
} map_t;

int dump(char *filename, void *data);

void print_bytes(unsigned long position, FILE *fp,
        unsigned long size, int *i);

char *machine_name(Elf64_Ehdr *elf);

void read_at_position(unsigned long address, unsigned long position,
        unsigned long size, char *file);

#endif //PSU_NMOBJDUMP_2019_OBJDUMP_H
