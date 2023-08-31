#include "io.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

i64 io_read_fd_buff(byte * buff, int fd, i64 size)
{
    return read(fd, buff, size);
}

void io_read_fd_Str(Str * str, int fd, i64 size)
{
    i64 len;

    Str_reserve(str, size);
    len = io_read_fd_buff(Str_cstr(* str), fd, size);
    Str_set_len(str, len);
}

Str io_read_fd(int fd)
{
    Str         str;
    struct stat _stat;

    if (fstat(fd, & _stat)) return Str_new();

    str = Str_new_size(_stat.st_size + 1);
    io_read_fd_Str(& str, fd, _stat.st_size);

    return str;
}

Str io_read_file(const byte * name)
{
    int fd;

    if ((fd = open(name, O_RDONLY)) < 0) return Str_new();

    return io_read_fd(fd);
}

int io_file_new(const byte * name, int perms)
{
    return creat(name, perms);
}

int io_file_new_rdwr(const byte * name)
{
    return io_file_new(name, 0666);
}