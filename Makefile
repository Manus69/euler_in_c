cc = gcc
falgs_base := -std=c2x -Wall -Wextra 
flags_dbg := $(falgs_base) -g -fsanitize=address -fsanitize=undefined
flags_release := $(falgs_base) -Ofast -flto

target := _euler
lib_dir := ./lib
lib := $(lib_dir)/libEuler.a
lib_header := $(lib_dir)/libEuler.h

src_dir := ./src
src := $(notdir $(wildcard $(src_dir)/*.c))
main := euler.c
obj_dir := ./obj
obj := $(addprefix $(obj_dir)/,$(src:.c=.o)) $(obj_dir)/$(main:.c=.o)

flags_i := -I $(src_dir) -I $(lib_dir)
flags_l := -L $(lib_dir) -lEuler
flags := $(flags_dbg)

$(target) : $(obj) $(lib)
	$(cc) $(flags) $(flags_i) $(obj) -o $@ $(flags_l) 

$(lib) : lib_dbg

lib_dbg :
	make -C $(lib_dir)

lib_release :
	make release -C $(lib_dir)

rm_obj :
	rm -f $(obj)

re_obj : rm_obj $(obj)

release : flags := $(flags_release)
release : lib_release
release : re_obj $(target)

re : lib_dbg re_obj $(target)

$(obj_dir)/%.o : $(src_dir)/%.c
	$(cc) $(flags) $(flags_i) -c $< -o $@

$(obj_dir)/$(main:.c=.o) : $(main)
	$(cc) $(flags) $(flags_i) -c $< -o $@


