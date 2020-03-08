/*
** EPITECH PROJECT, 2020
** oui
** File description:
** TODO: Add description
*/

#include "nm.h"

char *get_str(void *data, Elf64_Shdr *strtab)
{
    static char *str = NULL;

    if (str == NULL && data != NULL && strtab != NULL)
        str = (char *) ((char *) data + strtab->sh_offset);
    return str;
}

void print_values(const size_t *addresse, int idx, char *str, Elf64_Shdr *sym)
{
    char c = 0;

    for (int k = 0; k < idx; ++k) {
        if (((Elf64_Sym *) addresse[k])->st_info != 4) {
            if (((Elf64_Sym *) addresse[k])->st_value)
                printf("%.16lx ", ((Elf64_Sym *) addresse[k])->st_value);
            else
                printf("%16s ", " ");
            c = get_flags((Elf64_Sym *) addresse[k], sym);
            printf("%c %s\n", c, &str[((Elf64_Sym *) addresse[k])->st_name]);
        }
    }
}

int get_sections(void *data, Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *name)
{
    char *tab = NULL;
    Elf64_Shdr *strtab = NULL;
    int i = 1;

    tab = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
    strtab = get_strtab(elf, shdr, tab);
    for (; i < elf->e_shnum; i++) {
        if (shdr[i].sh_size > 0 && !strcmp(&tab[shdr[i].sh_name], ".symtab")){
            get_symbols(&shdr[i], data, strtab, shdr);
            break;
        }
    }
    if (i == elf->e_shnum) {
        fprintf(stderr, "nm: %s: no symbols\n", name);
        return 84;
    }
    return (0);
}

void get_symbols(Elf64_Shdr *sec, void *data, Elf64_Shdr *stab, Elf64_Shdr *sh)
{
    size_t i = 0;
    size_t idx = 0;
    Elf64_Sym *symtab = (Elf64_Sym *) ((char *) data + sec->sh_offset);
    char *str = get_str(data, stab);
    for (; i < sec->sh_size / sec->sh_entsize; i++)
        if (symtab[i].st_info != 4)
            if (!strcmp(&str[symtab[i].st_name], ""))
                continue;
    size_t addresses[i];
    for (size_t j = 0; j < sec->sh_size / sec->sh_entsize; j++) {
        if (symtab[j].st_info != 4) {
            if (!strcmp(&str[symtab[j].st_name], ""))
                continue;
            addresses[idx] = (size_t) &symtab[j];
            idx++;
        }
    }
    bubble_sort(addresses, idx, str);
    print_values(addresses, idx, str, sh);
}

Elf64_Shdr *get_strtab(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *tab)
{
    for (int i = 1; i < elf->e_shnum; i++) {
        if (shdr[i].sh_size > 0 && !strcmp(&tab[shdr[i].sh_name], ".strtab")){
            return (Elf64_Shdr *) &shdr[i];
        }
    }
    return NULL;
}
