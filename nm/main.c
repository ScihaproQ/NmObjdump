/*
** EPITECH PROJECT, 2020
** 
** File description:
** TODO: Add description
*/

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <zconf.h>
#include <sys/mman.h>
#include <string.h>
#include <stdbool.h>

int symbols(char *filename, void *data)
{
    char *strtab = NULL;
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    Elf64_Sym *symtab = NULL;
    long flags = 0;

    if (data == MAP_FAILED)
        return 84;
    elf = (Elf64_Ehdr *) data;
    shdr = (Elf64_Shdr *) (data + elf->e_shoff);
    strtab = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
    for (int i = 0; i < elf->e_shnum; ++i) {
        if (shdr[i].sh_type == SHT_SYMTAB) {
            symtab = (Elf64_Sym *) &shdr[i];
            for (int j = 0; j < sizeof(Elf64_Sym); ++j) {
                printf("Oui: %lx\n", symtab[j].st_value);
            }
        }
    }
    return (0);
}

int main(int ac, char **av)
{
    int fd = 0;
    int filesize = 0;
    void *data = NULL;
    int status = 0;

    for (int i = 1; av[i]; ++i) {
        fd = open(av[i], O_RDONLY);
        if (fd == -1)
            return (84);
        filesize = lseek(fd, 0, SEEK_END);
        data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
        symbols(av[i], data);
    }
}