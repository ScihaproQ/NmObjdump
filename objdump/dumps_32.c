/*
** EPITECH PROJECT, 2020
** 
** File description:
** TODO: Add description
*/

/*
** EPITECH PROJECT, 2020
** 
** File description:
** TODO: Add description
*/

#include "objdump.h"

void dump_header_32(char *filename, Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
    char buf[150];
    long flags = 0;

    flags = 0x01 * (elf->e_type == ET_REL
            && (shdr->sh_type == SHT_RELA
            || shdr->sh_type == SHT_REL))
                    | 0x02 * (elf->e_type == ET_EXEC)
                    | 0x10 * (shdr->sh_type == SHT_SYMTAB
                    || shdr->sh_type == SHT_DYNSYM)
                    |  0x40 * (elf->e_type == ET_DYN)
                    | 0x100 * ((elf->e_type == ET_EXEC
                    || elf->e_type == ET_DYN));
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

int dump_32(char *filename, void *data)
{
    char *strtab = NULL;
    Elf32_Ehdr *elf;
    Elf32_Shdr *shdr;

    if (data == MAP_FAILED)
        return 84;
    elf = (Elf32_Ehdr *) data;
    shdr = (Elf32_Shdr *) (data + elf->e_shoff);
    strtab = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
    dump_header_32(filename, elf, shdr);
    dump_sections_32(filename, elf, shdr, strtab);
    return (0);
}
