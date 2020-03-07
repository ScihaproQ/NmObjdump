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

char *get_name_tab(void *data, Elf64_Shdr *strtab)
{
    static char *name_tab = NULL;
    if (name_tab == NULL)
        name_tab =(char *) ((char *) data + strtab->sh_offset);
    return name_tab;
}

int comp(const void *elem1, const void *elem2)
{
    Elf64_Sym f = *((Elf64_Sym*)elem1);
    Elf64_Sym s = *((Elf64_Sym*)elem2);
    char *str = get_name_tab(NULL, NULL);
    printf("OUIIUZ JDÉZFAFZAV");
    return 0;
}

void fetch_symbol(Elf64_Shdr *sec, void *data, Elf64_Shdr *strtab)
{
    size_t i = 0;
    Elf64_Sym *symtab = (Elf64_Sym *) ((char *) data + sec->sh_offset);
    char *str = get_name_tab(data, strtab);
    for (; i < sec->sh_size / sec->sh_entsize; i++) {
        if (!strcmp(&str[symtab[i].st_name], ""))
            continue;
        if (symtab[i].st_value)
            printf("%.16lx ", symtab[i].st_value);
        else
            printf("%16s ", " ");
        printf("%-40s ", &str[symtab[i].st_name]);
        printf("%.16lx\t", symtab[i].st_size);
        if (symtab[i].st_info & STB_GLOBAL)
            printf("GLOBAL %.2x\n", symtab[i].st_info);
        else
            printf("LOCAL %.2x\n", symtab[i].st_info);
    }
}

int fetch_section(void *data, Elf64_Ehdr *elf, Elf64_Shdr *shdr)
{
    char *tab = NULL;
    Elf64_Shdr *strtab = NULL;

    tab = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
    for (int i = 1; i < elf->e_shnum; i++) {
        if (shdr[i].sh_size > 0 && !strcmp(&tab[shdr[i].sh_name], ".strtab")) {
            strtab = (Elf64_Shdr *) &shdr[i];
            break;
        }
    }
    for (int i = 1; i < elf->e_shnum; i++) {
        if (shdr[i].sh_size > 0 && !strcmp(&tab[shdr[i].sh_name], ".symtab")) {
            fetch_symbol(&shdr[i], data, strtab);
            break;
        }
    }
    return (0);
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void bubbleSort(int arr[], int n)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

int symbols(void *data)
{
//    char *strtab = NULL;
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
//    Elf64_Sym *symtab = NULL;

    if (data == MAP_FAILED)
        return 84;
    elf = (Elf64_Ehdr *) data;
    shdr = (Elf64_Shdr *) (data + elf->e_shoff);
//    strtab = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
//    symtab = (Elf64_Sym *)((char *)data + shdr->sh_offset);
    fetch_section(data, elf, shdr);
    return (0);
}

int main(int ac, char **av)
{
    int fd = 0;
    int filesize = 0;
    void *data = NULL;

    (void) ac;
    for (int i = 1; av[i]; ++i) {
        fd = open(av[i], O_RDONLY);
        if (fd == -1)
            return (84);
        filesize = lseek(fd, 0, SEEK_END);
        data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
        symbols(data);
    }
}