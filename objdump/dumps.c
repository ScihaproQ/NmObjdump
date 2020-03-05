/*
** EPITECH PROJECT, 2020
** 
** File description:
** TODO: Add description
*/

#include "objdump.h"

void dump_flags(unsigned long flags)
{
    map_t flags_to_string[] = {
            {0x01, "HAS_RELOC"},
            {0x02, "EXEC_P"},
            {0x04, "HAS_LINENO"},
            {0x08, "HAS_DEBUG"},
            {0x10, "HAS_SYMS"},
            {0x20, "HAS_LOCALS"},
            {0x40, "DYNAMIC"},
            {0x80, "WP_TEXT"},
            {0x100, "D_PAGED"},
            {0, NULL},
    };
}

void dump_header(char *filename, Elf64_Ehdr *elf, Elf64_Shdr *shdr)
{
    char buf[150];
    unsigned long a = 0;
    unsigned long flags = 0;

    flags = 0x01 * (elf->e_type == ET_REL &&
            (shdr->sh_type == SHT_RELA || shdr->sh_type == SHT_REL))
                    | 0x02 * (elf->e_type == ET_EXEC)
                    | 0x10 * (shdr->sh_type == SHT_SYMTAB
                    || shdr->sh_type == SHT_DYNSYM)
                    |  0x40 * (elf->e_type == ET_DYN)
                    | 0x100 * ((elf->e_type == ET_EXEC
                    || elf->e_type == ET_DYN));
    memset(buf, 0, 150);
    printf("\n%s:     file format elf64-x86-64\n", filename);
    printf("architecture: %s, flags 0x%08lx:\n", machine_name(elf), flags);
    dump_flags(flags);
    printf("start address 0x%016lx\n\n", elf->e_entry);
}

void dump_sections(char *filename, Elf64_Ehdr *elf,
        Elf64_Shdr *shdr, char *strtab)
{
    int counter = 1;

    while (counter < elf->e_shnum - 1) {
        if (strcmp(&strtab[shdr[counter].sh_name], ".bss") == 0
            || strcmp(&strtab[shdr[counter].sh_name], ".strtab") == 0
            || shdr[counter].sh_type == SHT_NOBITS
            || shdr[counter].sh_type == SHT_SYMTAB) {
            counter++;
            continue;
        }
        printf("Contents of section %s:\n", &strtab[shdr[counter].sh_name]);
        read_at_position(shdr[counter].sh_addr, shdr[counter].sh_offset,
                shdr[counter].sh_size, filename);
        counter++;
    }
}

int dump(char *filename, void *data)
{
    char *strtab = NULL;
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;

    if (data == MAP_FAILED)
        return 84;
    elf = (Elf64_Ehdr *) data;
    shdr = (Elf64_Shdr *) (data + elf->e_shoff);
    strtab = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
    dump_header(filename, elf, shdr);
    dump_sections(filename, elf, shdr, strtab);
    return (0);
}
