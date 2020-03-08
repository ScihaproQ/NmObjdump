/*
** EPITECH PROJECT, 2020
** nm.h
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

void bubble_sort(size_t *, int, char *);

Elf64_Shdr *get_strtab(Elf64_Ehdr *, Elf64_Shdr *, char *);

void get_symbols(Elf64_Shdr *, void *, Elf64_Shdr *, Elf64_Shdr *);

int get_sections(void *, Elf64_Ehdr *, Elf64_Shdr *, char *);
#endif //PSU_NMOBJDUMP_2019_NM_H
