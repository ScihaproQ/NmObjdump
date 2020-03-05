/*
** EPITECH PROJECT, 2020
** 
** File description:
** TODO: Add description
*/

#include "objdump.h"

int check_file(void *data)
{
    if (((Elf64_Ehdr *)data)->e_ident[EI_MAG0] == 0x7f
    && ((Elf64_Ehdr *)data)->e_ident[EI_MAG1] == 'E'
    && ((Elf64_Ehdr *)data)->e_ident[EI_MAG2] == 'L'
    && ((Elf64_Ehdr *)data)->e_ident[EI_MAG3] == 'F')
        return true;
    return false;
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
        if (!check_file(data))
            return 84;
        if (((Elf64_Ehdr *)data)->e_ident[EI_CLASS] == ELFCLASS64
        && (status = dump_64(av[i], data)) == 84)
            return status;
        if (((Elf64_Ehdr *)data)->e_ident[EI_CLASS] == ELFCLASS32
            && (status = dump_32(av[i], data)) == 84)
            return status;
    }
}
