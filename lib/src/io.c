#include "io.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

i64 io_read_fd_buff(byte * buff, int fd, i64 size)
{
    return read(fd, buff, size);
}

void Str_append_from_file(Str * str, int fd, i64 size)
{
    Str_reserve(str, size);
    str->idx += io_read_fd_buff(Str_get(* str, str->idx), fd, size);
}

Str io_read_fd(int fd)
{
    Str         str;
    struct stat _stat;

    if (fstat(fd, & _stat)) return Str_new();

    str = Str_new_capacity(_stat.st_size);
    Str_append_from_file(& str, fd, _stat.st_size);

    return str;
}

Str io_read_file(const byte * name)
{
    int fd;
    Str str;

    if ((fd = open(name, O_RDONLY)) < 0) return Str_new();

    str = io_read_fd(fd);
    close(fd);

    return str;
}

i64 io_write_fd(Str str, int fd)
{
    return write(fd, Str_first(str), Str_len(str));
}

i64 io_write_to_file(Str str, const byte * name)
{
    int fd;
    i64 result;

    if ((fd = open(name, O_WRONLY)) < 0) return NO_IDX;

    result = io_write_fd(str, fd);
    close(fd);

    return result;
}

int io_file_new(const byte * name, int perms)
{
    return creat(name, perms);
}

int io_file_new_rdwr(const byte * name)
{
    return io_file_new(name, 0666);
}