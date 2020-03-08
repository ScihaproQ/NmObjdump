/*
** EPITECH PROJECT, 2020
** 
** File description:
** TODO: Add description
*/

#ifndef PSU_NMOBJDUMP_2019_NM_H
#define PSU_NMOBJDUMP_2019_NM_H

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <zconf.h>
#include <sys/mman.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

typedef struct {
    int value;
    char c;
} type_t;

typedef struct {
    unsigned int info;
    unsigned int type;
    unsigned int flag;
    char c;
} map;

char get_flags(Elf64_Sym *symbol, Elf64_Shdr *shdr);

void bubbleSort(size_t *addresses, int n, char *str);

Elf64_Shdr *get_strtab(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *tab);

void get_symbols(Elf64_Shdr *sec, void *data, Elf64_Shdr *strtab,
                 Elf64_Shdr *shdr);

int get_sections(void *data, Elf64_Ehdr *elf, Elf64_Shdr *shdr,
                 char *filename);
#endif //PSU_NMOBJDUMP_2019_NM_H
