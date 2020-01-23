target = bin
src = src
bin = build
inc = $(src)/headers
ext = vendor
pch = pch
cc = gcc

libs = $(wildcard $(ext)/*/lib/*.a)

flags = -Wall -Werror -L $(ext)/CUnit/lib
ldlibs = -lcunit

flags_dbg = -g

source = $(wildcard $(src)/*.c)
object = $(patsubst %,$(bin)/%, $(notdir $(source:.c=.o)))

$(bin)/$(target): $(object) $(libs)
	$(cc) $^ -o $@ $(flags) $(ldlibs)

$(ext)/%/lib/*.a: $(ext)/%/obj/*.o
	echo "---------------------"
	cd $(ext)/% && make

$(bin)/%.o: $(src)/%.c
	$(cc) -c $< -o $@ $(flags) $(ldlibs) -I $(inc) -I $(ext)

build: $(bin)/$(target)

$(bin)/$(pch).o: $(src)/$(pch).c $(inc)/$(pch).h
	$(cc) -c $< -o $@ -I $(inc) -I $(ext)

run: build
	@$(bin)/$(target)

dirs:
	@echo "target: $(target)"
	@echo "source         dir: $(src)"
	@echo "binary         dir: $(bin)"
	@echo "include        dir: $(inc)"
	@echo "external libs  dir: $(ext)"
	@echo "c compiler: $(cc)"

clean:
	rm -f $(bin)/*

cleans:
	rm -rf $(bin)
	rm -rf $(ext)/*/obj
	rm -rf $(ext)/*/lib

curdir = $(wildcard $(ext)/*/.)

init:
	mkdir $(curdir:.=obj)
	mkdir $(curdir:.=lib)
	mkdir $(bin)
	cd vendor/CUnit && make

valgrind: $(object)
	$(cc) $(object) $(flags) $(flags_dgb) -o $(bin)/$(target)
	valgrind --leak-check=full --show-leak-kinds=all $(bin)/$(target)

help:
	@echo "Commands:"
	@echo "build    run         dirs"
	@echo "clean    valgrind    init"
	@echo "init_rm"