target = bin
src = src
bin = build

source = $(wildcard $(src)/*.c)
object = $(patsubst %,$(bin)/%, $(notdir $(source:.c=.o)))

cc = gcc

$(bin)/$(target) : $(object)
	$(cc) $^ -o $@

$(bin)/%.o: $(src)/%.c
	$(cc) -c $< -o $@ -I $(src)

main:
	echo "$(source) - $(object)"