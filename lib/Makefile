cc := gcc
flags_base := -std=c2x -Wall -Wextra
flags_dbg := $(flags_base) -g -fsanitize=address -fsanitize=undefined
flags_release := $(flags_base) -Ofast -flto -D NDEBUG -pg
target := libEuler.a
header := libEuler.h

obj_dir := ./obj
src_dir := ./src
src := $(notdir $(wildcard $(src_dir)/*.c))
headers := $(wildcard $(src_dir)/*.h)
obj := $(addprefix $(obj_dir)/,$(src:.c=.o))

flags := $(flags_dbg)

all: $(target)

$(obj) : $(header) $(headers)

$(obj_dir)/%.o : $(src_dir)/%.c
	$(cc) $(flags) -c $< -o $@

rm_obj:
	rm -f $(obj)

rm_lib:
	rm -f $(target)

$(target): $(obj)
	ar -rcsv $(target) $(obj)

release: flags := $(flags_release)
release: rm_obj rm_lib $(target)

re: rm_obj rm_lib all
