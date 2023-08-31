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

}

Str io_read_fd(int fd)
{
    Str         str;
    struct stat _stat;

    if (fstat(fd, & _stat)) return Str_new();

    str = Str_new_size(_stat.st_size + 1);
    read(fd, Str_cstr(str), _stat.st_size);
    Str_set_len(& str, _stat.st_size);

    return str;
}

Str io_read_file(const byte * name)
{

}