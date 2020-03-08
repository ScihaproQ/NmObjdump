/*
** EPITECH PROJECT, 2020
** 
** File description:
** TODO: Add description
*/

#include <sys/stat.h>
#include <errno.h>
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

int print_files(void *data, char *arg)
{
    int status = 0;

    if (((Elf64_Ehdr *)data)->e_ident[EI_CLASS] == ELFCLASS64
        && (status = dump_64(arg, data)) == 84)
        return status;
    if (((Elf64_Ehdr *)data)->e_ident[EI_CLASS] == ELFCLASS32
        && (status = dump_32(arg, data)) == 84)
        return status;
    return 0;
}

int default_file()
{
    int fd = 0;
    int filesize = 0;
    void *data = NULL;

    fd = open("a.out", O_RDONLY);
    if (fd == -1) {
        if (errno == EACCES)
            fprintf(stderr, "objdump: '%s': Permission denied\n", "a.out");
        else
            fprintf(stderr, "objdump: '%s': No such file\n", "a.out");
        return (84);
    }
    filesize = lseek(fd, 0, SEEK_END);
    data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if (!check_file(data)) {
        fprintf(stderr, "objdump: '%s': file format not recognized\n",
                "a.out");
        return 84;
    }
    return print_files(data, "a.out");
}

int get_file(int fd, char *arg)
{
    int filesize = 0;
    void *data = NULL;
    int status = 0;

    filesize = lseek(fd, 0, SEEK_END);
    data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if (!check_file(data)) {
        fprintf(stderr, "objdump: '%s': file format not recognized\n",
                arg);
        return 84;
    }
    if ((status = print_files(data, arg) == 84))
        return status;
    return 0;
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
                fprintf(stderr, "objdump: '%s': Permission denied\n", av[i]);
            else
                fprintf(stderr, "objdump: '%s': No such file\n", av[i]);
            status = 84;
            continue;
        }
        status = get_file(fd, av[i]);
    }
    return status;
}
