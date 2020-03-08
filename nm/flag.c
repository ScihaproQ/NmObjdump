/*
** EPITECH PROJECT, 2020
** 
** File description:
** TODO: Add description
*/

#include "nm.h"

map type[] = {
        {STT_FUNC,   SHT_NULL,       0,    'U'},
        {STT_NOTYPE, SHT_PROGBITS,   50,   'R'},
        {SHF_WRITE,  SHT_PROGBITS,   18,   'R'},
        {STT_OBJECT, SHT_PROGBITS,   2,    'R'},
        {STT_NOTYPE, SHT_PROGBITS,   6,    'T'},
        {STT_OBJECT, SHT_NOTE,       2,    'R'},
        {STT_NOTYPE, SHT_INIT_ARRAY, 3,    'T'},
        {STT_OBJECT, SHT_PROGBITS,   3,    'D'},
        {STT_OBJECT, SHT_INIT_ARRAY, 3,    'T'},
        {STT_FUNC,   SHT_PROGBITS,   6,    'T'},
        {STT_NOTYPE, SHT_FINI_ARRAY, 3,    'T'},
        {STT_NOTYPE, SHT_PROGBITS,   0,    'N'},
        {STT_OBJECT, SHT_FINI_ARRAY, 3,    'T'},
        {STT_NOTYPE, SHT_NOBITS,     3,    'B'},
        {STT_TLS,    SHT_PROGBITS,   1027, 'D'},
        {STT_NOTYPE, SHT_PROGBITS,   3,    'D'},
        {STT_OBJECT, SHT_PROGBITS,   0,    'N'},
        {STT_TLS,    SHT_NOBITS,     1027, 'B'},
        {STT_OBJECT, SHT_DYNAMIC,    3,    'D'},
        {STT_OBJECT, SHT_NOBITS,     3,    'B'},
        {STT_NOTYPE, SHT_PROGBITS,   2,    'R'},
        {STT_OBJECT, SHT_PROGBITS,   50,   'R'},
        {STT_LOOS,   SHT_PROGBITS,   6,    'I'},
        {0, 0,                       0,    '\0'}
};

type_t value_type[] = {
        {SHN_COMMON, 'C'},
        {SHN_UNDEF, 'U'},
        {SHN_ABS, 'A'},
        {0, '\0'}
};

void weak_type_flag(Elf64_Sym *symbol, char *c)
{
    if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT &&
        symbol->st_shndx == SHN_UNDEF) {
        *(c) = 'v';
        return;
    }
    if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT) {
        *(c) = 'V';
        return;
    }
    if (symbol->st_shndx == SHN_UNDEF) {
        *(c) = 'w';
        return;
    }
    *(c) = 'W';
}

void get_flag_sym(Elf64_Sym *symbol, char *c)
{
    if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK) {
        weak_type_flag(symbol, c);
        return;
    }
    if (ELF64_ST_BIND(symbol->st_info) == STB_GNU_UNIQUE) {
        *(c) = 'u';
        return;
    }
    for (int i = 0; value_type[i].c != '\0'; i++)
        if (symbol->st_shndx == value_type[i].value)
            *(c) = (value_type[i].c);
}

void check_shdr(Elf64_Sym *symbol, Elf64_Shdr *shdr, char *c)
{
    if (!*(c)) {
        for (int i = 0; type[i].c != '\0'; i++) {
            if (ELF64_ST_TYPE(symbol->st_info) == type[i].info &&
                shdr[symbol->st_shndx].sh_flags == type[i].flag
                && shdr[symbol->st_shndx].sh_type == type[i].type)
                *(c) = (type[i].c);
        }
    }
}

char get_flags(Elf64_Sym *symbol, Elf64_Shdr *shdr)
{
    char c = 0;

    get_flag_sym(symbol, &c);
    check_shdr(symbol, shdr, &c);
    if (c == '\0')
        return ('?');
    if (ELF64_ST_BIND(symbol->st_info) == STB_LOCAL)
        c += 32;
    return c;
}