cc = gcc
src = src
bin = build
inc = $(src)/headers
flags = -Wall -Werror -lm

target = bin

source = $(wildcard $(src)/*.c)
object = $(patsubst %,$(bin)/%, $(notdir $(source:.c=.o)))

$(bin)/$(target): $(object)
	$(cc) $^ -o $@ $(flags)

$(bin)/%.o: $(src)/%.c
	$(cc) -c $< -o $@ $(flags) -I $(inc)

build: $(bin)/$(target)

init:
	mkdir build

run: build
	@$(bin)/$(target)

debug:
	$(eval flags += -g)

clean:
	rm -rf build/*

cleans:
	rm -rf build

valgrind: debug build
	valgrind --leak-check=full --show-leak-kinds=all $(bin)/$(target)

help:
	@echo "Commands:"
	@echo "    init  build  run  clean"