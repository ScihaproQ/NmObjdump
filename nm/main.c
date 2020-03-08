/*
** EPITECH PROJECT, 2020
** main.c from nm
** File description:
** TODO: Add description
*/

#include "nm.h"

int symbols(void *data, char *filename)
{
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;

    if (data == MAP_FAILED)
        return 84;
    elf = (Elf64_Ehdr *) data;
    shdr = (Elf64_Shdr *) (data + elf->e_shoff);
    return get_sections(data, elf, shdr, filename);
}

int check_file(void *data)
{
    if (((Elf64_Ehdr *) data)->e_ident[EI_MAG0] == 0x7f
        && ((Elf64_Ehdr *) data)->e_ident[EI_MAG1] == 'E'
        && ((Elf64_Ehdr *) data)->e_ident[EI_MAG2] == 'L'
        && ((Elf64_Ehdr *) data)->e_ident[EI_MAG3] == 'F')
        return true;
    return false;
}

int get_file(int fd, char *arg)
{
    int filesize = 0;
    void *data = NULL;
    int status = 0;

    filesize = lseek(fd, 0, SEEK_END);
    data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if (!check_file(data)) {
        fprintf(stderr, "nm: %s: file format not recognized\n",
                arg);
        return 84;
    }
    if ((status = symbols(data, arg) == 84))
        return status;
    return 0;
}

int default_file(void)
{
    int fd = 0;
    int status = 0;

    fd = open("a.out", O_RDONLY);
    if (fd == -1) {
        if (errno == EACCES)
            fprintf(stderr, "nm: '%s': Permission denied\n", "a.out");
        else
            fprintf(stderr, "nm: '%s': No such file\n", "a.out");
        return (status = 84), status;
    }
    status = get_file(fd, "a.out");
    return status;
}

int main(int ac, char **av)
{
    int fd = 0;
    int status = 0;

    if (ac == 1)
        return default_file();
    for (int i = 1; av[i]; ++i) {
        fd = open(av[i], O_RDONLY);
        if (fd == -1) {
            if (errno == EACCES)
                fprintf(stderr, "nm: '%s': Permission denied\n", av[i]);
            else
                fprintf(stderr, "nm: '%s': No such file\n", av[i]);
            status = 84;
            continue;
        }
        status = get_file(fd, av[i]);
    }
    return status;
}