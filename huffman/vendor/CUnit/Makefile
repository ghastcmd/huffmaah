source = $(wildcard src/*.c)
object = $(patsubst %,obj/%, $(notdir $(source:.c=.o)))

build: $(object)
	ar rs lib/libcunit.a obj/*.o

obj/%.o: src/%.c
	gcc -c $< -o $@ -I .