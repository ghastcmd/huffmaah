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

run: build
	@$(bin)/$(target)

init:
	mkdir build

clean:
	rm -rf build

plot: build
	python plot.py