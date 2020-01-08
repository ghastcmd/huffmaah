target = bin
src = src
bin = build
inc = src/headers
pch = pch
cc = gcc

source = $(wildcard $(src)/*.c)
object = $(patsubst %,$(bin)/%, $(notdir $(source:.c=.o)))

$(bin)/$(pch).o: $(src)/$(pch).c $(inc)/$(pch).h
	$(cc) -c $< -o $@ -I $(inc)

$(bin)/$(target): $(object)
	$(cc) $^ -o $@

$(bin)/%.o: $(src)/%.c
	$(cc) -c $< -o $@ -I $(inc)

build: $(bin)/$(target)

run: $(bin)/$(target)
	$(bin)/$(target)

dirs:
	@echo "target: $(target)"
	@echo "source  dir: $(src)"
	@echo "binary  dir: $(bin)"
	@echo "include dir: $(inc)"
	@echo "c compiler: $(cc)"

plot:
	Rscript ./plot/script.r