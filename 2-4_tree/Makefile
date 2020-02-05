cc = gcc
src = src
bin = build
inc = $(src)/headers

target = bin

source = $(wildcard $(src)/*.c)
object = $(patsubst %,$(bin)/%, $(notdir $(source:.c=.o)))

$(bin)/$(target): $(object)
	$(cc) $^ -o $@

$(bin)/%.o: $(src)/%.c
	$(cc) -c $< -o $@ -I $(inc)

build: $(bin)/$(target)

init:
	mkdir build

run: build
	@$(bin)/$(target)

clean:
	rm -rf build