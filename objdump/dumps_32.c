/*
** EPITECH PROJECT, 2020
**
** File description:
** TODO: Add description
*/

#include "objdump.h"

void dump_header_32(char *filename, Elf32_Ehdr *elf, long flags)
{
    char buf[150];

    memset(buf, 0, 150);
    printf("\n%s:     file format elf32-i386\n", filename);
    printf("architecture: %s, flags 0x%08lx:\n", machine_name_32(elf), flags);
    dump_flags(flags);
    printf("start address 0x%08x\n\n", elf->e_entry);
}

void dump_sections_32(char *filename, Elf32_Ehdr *elf,
        Elf32_Shdr *shdr, char *strtab)
{
    int counter = 1;

    while (counter < elf->e_shnum - 1) {
        if (strcmp(&strtab[shdr[counter].sh_name], ".bss") == 0
            || strcmp(&strtab[shdr[counter].sh_name], ".strtab") == 0
            || strcmp(&strtab[shdr[counter].sh_name], ".shstrtab") == 0
            || strcmp(&strtab[shdr[counter].sh_name], ".symtab") == 0
            || shdr[counter].sh_type == SHT_NOBITS
            || shdr[counter].sh_type == SHT_SYMTAB
            || shdr[counter].sh_size <= 0) {
            counter++;
            continue;
        }
        printf("Contents of section %s:\n", &strtab[shdr[counter].sh_name]);
        read_at_position(shdr[counter].sh_addr, shdr[counter].sh_offset,
                shdr[counter].sh_size, filename);
        counter++;
    }
}

long get_flag_32(Elf32_Ehdr *elf)
{
    long flags = 0;
    long flag = 0;
    int counter = 0;
    Elf32_Shdr *te = NULL;

    while (counter < elf->e_shnum - 1) {
        te = &(((Elf32_Shdr *)((char *)elf + elf->e_shoff))[counter + 1]);
        flags = 0x01 * (elf->e_type == ET_REL && (te->sh_type == SHT_RELA
                || te->sh_type == SHT_REL)) | 0x02 * (elf->e_type == ET_EXEC)
                | 0x10 * (te->sh_type == SHT_SYMTAB
                || te->sh_type == SHT_DYNSYM)
                | 0x40 * (elf->e_type == ET_DYN)
                | 0x100 * ((elf->e_type == ET_EXEC
                || elf->e_type == ET_DYN));
        if (flags > flag)
            flag = flags;
        counter++;
    }
    return flag;
}

int dump_32(char *filename, void *data)
{
    char *strtab = NULL;
    Elf32_Ehdr *elf;
    Elf32_Shdr *shdr;
    long flags = 0;

    if (data == MAP_FAILED)
        return 84;
    elf = (Elf32_Ehdr *) data;
    shdr = (Elf32_Shdr *) (data + elf->e_shoff);
    strtab = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
    flags = get_flag_32(elf);
    dump_header_32(filename, elf, flags);
    dump_sections_32(filename, elf, shdr, strtab);
    return (0);
}
