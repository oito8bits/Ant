shell: shell.o
	gcc $^ -o $@

%.o: %.c
	gcc -c -o $@ $<

.PHONY: clean

clean:
	rm *.o shell
