/*
** EPITECH PROJECT, 2020
** oui
** File description:
** TODO: Add description
*/

#include "objdump.h"

char *machine_name_32(Elf32_Ehdr *elf)
{
    static map_t const machines[] = {{EM_NONE, "None"},
    {EM_M32, "WE32100"},
    {EM_SPARC, "Sparc"}, {EM_ARM, "ARM"},
    {EM_386, "Intel 80386"},
    {EM_68K, "MC68000"},
    {EM_88K, "MC88000"},
    {EM_860, "Intel 80860"},
    {EM_MIPS, "MIPS R3000"},
    {EM_PARISC, "HPPA"},
    {EM_SPARC32PLUS, "Sparc v8+"},
    {EM_PPC, "PowerPC"},
    {EM_PPC64, "PowerPC64"},
    {EM_S390, "IBM S/390"},
    {EM_SH, "Renesas / SuperH SH"},
    {EM_SPARCV9, "Sparc v9"},
    {EM_IA_64, "Intel IA-64"},
    {EM_X86_64, "i386:x86-64"}};
    return "i386";
}

char *machine_name_64(Elf64_Ehdr *elf)
{
    static map_t const machines[] = {{EM_NONE, "None"},
    {EM_M32, "WE32100"},
    {EM_SPARC, "Sparc"}, {EM_ARM, "ARM"},
    {EM_386, "Intel 80386"},
    {EM_68K, "MC68000"},
    {EM_88K, "MC88000"},
    {EM_860, "Intel 80860"},
    {EM_MIPS, "MIPS R3000"},
    {EM_PARISC, "HPPA"},
    {EM_SPARC32PLUS, "Sparc v8+"},
    {EM_PPC, "PowerPC"},
    {EM_PPC64, "PowerPC64"},
    {EM_S390, "IBM S/390"},
    {EM_SH, "Renesas / SuperH SH"},
    {EM_SPARCV9, "Sparc v9"},
    {EM_IA_64, "Intel IA-64"},
    {EM_X86_64, "i386:x86-64"}};
    return "i386:x86-64";
}
