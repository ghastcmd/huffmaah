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
	mkdir data

clean:
	rm -rf build/
	rm -rf data/

plot: build
	python3 plot.py