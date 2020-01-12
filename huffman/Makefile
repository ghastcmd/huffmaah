target = bin
src = src
bin = build
inc = $(src)/headers
pch = pch
cc = gcc
flags = -Wall -Werror
flags_dbg = -g

source = $(wildcard $(src)/*.c)
object = $(patsubst %,$(bin)/%, $(notdir $(source:.c=.o)))

$(bin)/$(target): $(object)
	$(cc) $^ $(flags) -o $@ 

$(bin)/%.o: $(src)/%.c
	$(cc) -c $< -o $@ $(flags) -I $(inc) 

build: $(bin)/$(target)

$(bin)/$(pch).o: $(src)/$(pch).c $(inc)/$(pch).h
	$(cc) -c $< -o $@ -I $(inc)


run: build
	@$(bin)/$(target)

dirs:
	@echo "target: $(target)"
	@echo "source  dir: $(src)"
	@echo "binary  dir: $(bin)"
	@echo "include dir: $(inc)"
	@echo "c compiler: $(cc)"

clean:
	rm build/*

valgrind: $(object)
	$(cc) $(object) $(flags) $(flags_dgb) -o $(bin)/$(target)
	valgrind --leak-check=full $(bin)/$(target)

plot:
	Rscript ./plot/script.r

help:
	@echo "Commands:"
	@echo "build    run    dirs"
	@echo "clean    valgrind    plot"