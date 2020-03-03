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
#include "objdump.h"
#include "../bfd.h"

void print_address(unsigned long position, unsigned long size)
{
    char buffer[10];

    sprintf(buffer, "%lx", position + size);
    if (strlen(buffer) >= 5)
        printf(" %.5lx", position);
    else
        printf(" %.4lx", position);
}

void print_bytes(unsigned long position, FILE *fp, unsigned long size, int *i)
{
    unsigned char word = 0;
    unsigned char d = 0;
    char *ascii = malloc(16);
    char *hex = malloc(35);
    char *t_char = malloc(3);

    print_address(position, size);
    for (int j = 0; j < 16 && j < size; ++j, (*i)++) {
        if (!(j % 4) && j > 0)
            strcat(hex, " ");
        fread(&word, 1, 1, fp);
        sprintf(t_char, "%.2x", word);
        strncat(hex, t_char, 2);
        d = word;
        if (word <= 0x1F || word >= 0x7F)
            d = '.';
        strncat(ascii, &d, 1);
    }
    printf(" %-35s  %-16s\n", hex, ascii);
}

void read_at_position(unsigned long address, unsigned long position, unsigned long size, char *file)
{
    FILE *f = fopen(file, "rb");
    unsigned long tmp_size = size;

    fseek(f, position, SEEK_CUR);
    for (int i = 0; i < size; position += 0x10, address += 0x10, tmp_size -= 16)
        print_bytes(address, f, tmp_size, &i);
}

char *machine_name(Elf64_Ehdr *elf)
{
    static machine_t const machines[] = {{EM_NONE,        "None"},
                                         {EM_M32,         "WE32100"},
                                         {EM_SPARC,       "Sparc"},
                                         {EM_ARM,         "ARM"},
                                         {EM_386,         "Intel 80386"},
                                         {EM_68K,         "MC68000"},
                                         {EM_88K,         "MC88000"},
                                         {EM_860,         "Intel 80860"},
                                         {EM_MIPS,        "MIPS R3000"},
                                         {EM_PARISC,      "HPPA"},
                                         {EM_SPARC32PLUS, "Sparc v8+"},
                                         {EM_PPC,         "PowerPC"},
                                         {EM_PPC64,       "PowerPC64"},
                                         {EM_S390,        "IBM S/390"},
                                         {EM_SH,          "Renesas / SuperH SH"},
                                         {EM_SPARCV9,     "Sparc v9"},
                                         {EM_IA_64,       "Intel IA-64"},
                                         {EM_X86_64,      "i386:x86-64"}};
    for (int i = 0; i < 17; ++i)
        if (machines[i].key == elf->e_machine)
            return machines[i].str;
    return "i386:x86-64";
}

void dump_header(char *filename, Elf64_Ehdr *elf, Elf64_Shdr *shdr)
{
    char buf[150];
    unsigned long a = 0;

    memset(buf, 0, 150);
    if (elf->e_type & BFD_NO_FLAGS) {
        printf("ABC");
        a += BFD_NO_FLAGS;
        strcat(buf, " NO_FLAGS ");
    }
    if (shdr->sh_type & HAS_RELOC) {
        printf("ABC");
        a += HAS_RELOC;
        strcat(buf, " NO_FLAGS");
    }
    if (elf->e_type & EXEC_P) {
        printf("ABC");
        strcat(buf, " EXEC_P");
    }
    if (elf->e_type & HAS_LINENO) {
        printf("ABC");
        a += HAS_LINENO;
        strcat(buf, " HAS_LINENO");
    }
    if (elf->e_type & HAS_DEBUG) {
        printf("ABC");
        a += HAS_DEBUG;
        strcat(buf, " HAS_DEBUG");
    }
    if (shdr->sh_type & HAS_SYMS) {
        printf("ABC");
        a += HAS_SYMS;
        strcat(buf, " HAS_SYMS");
    }
    if (elf->e_type & HAS_LOCALS) {
        printf("ABC");
        a += HAS_LOCALS;
        strcat(buf, " HAS_LOCALS");
    }
    if (elf->e_type & DYNAMIC) {
        printf("ABC");
        a += DYNAMIC;
        strcat(buf, " DYNAMIC");
    }
    if (elf->e_type & WP_TEXT) {
        printf("ABC");
        a += WP_TEXT;
        strcat(buf, " WP_TEXT");
    }
    if (elf->e_type & D_PAGED) {
        printf("ABC");
        a += D_PAGED;
        strcat(buf, " D_PAGED");
    }
    printf("\n%s:     file format elf64-x86-64\n", filename);
    printf("architecture: %s, flags 0x%08lx:\n%s\n", machine_name(elf), a, buf);
    printf("start address 0x%016lx\n\n", elf->e_entry);
}

void dump_sections(char *filename, Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *strtab)
{
    int counter = 1;

    while (counter < elf->e_shnum - 1) {
        if (strcmp(&strtab[shdr[counter].sh_name], ".bss") == 0 ||strcmp(&strtab[shdr[counter].sh_name], ".strtab") == 0 || shdr[counter].sh_type ==
        SHT_NOBITS
            || shdr[counter].sh_type == SHT_SYMTAB) {
            counter++;
            continue;
        }
        printf("Contents of section %s:\n", &strtab[shdr[counter].sh_name]);
        read_at_position(shdr[counter].sh_addr, shdr[counter].sh_offset, shdr[counter].sh_size, filename);
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
        if ((status = dump(av[i], data)) == 84)
            return status;
    }
}
