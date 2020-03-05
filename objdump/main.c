/*
** EPITECH PROJECT, 2020
** 
** File description:
** TODO: Add description
*/

#include "objdump.h"

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
