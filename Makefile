target = bin
src = src
bin = build
cc = gcc

source = $(wildcard $(src)/*.c)
object = $(patsubst %,$(bin)/%, $(notdir $(source:.c=.o)))


$(bin)/$(target) : $(object)
	$(cc) $^ -o $@

$(bin)/%.o: $(src)/%.c
	$(cc) -c $< -o $@ -I $(src)

build: $(bin)/$(target)

run: $(bin)/$(target)
	$(bin)/$(target)

dirs:
	@echo "target: $(target)"
	@echo "src dir: $(src)"
	@echo "bin dir: $(bin)"
	@echo "compiler: $(cc)"