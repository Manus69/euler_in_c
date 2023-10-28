#ifndef IO_H
#define IO_H

#include "Str.h"

i64     io_read_fd_buff(byte * buff, int fd, i64 size);
void    Str_append_from_file(Str * str, int fd, i64 size);
Str     io_read_fd(int fd);
Str     io_read_file(const byte * name);
i64     io_write_fd(Str str, int fd);
i64     io_write_to_file(const byte * name, Str str);
int     io_file_new(const byte * name, int perms);
int     io_file_new_rdwr(const byte * name);

#endif