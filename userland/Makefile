shell: shell.o
	gcc $^ -o $@ --static

%.o: %.c
	gcc -c -o $@ $<

.PHONY: clean

clean:
		rm *.o shell
