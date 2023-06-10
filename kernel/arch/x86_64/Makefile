KERNEL_NAME=ant_kernel
OBJS = start.o
CC = gcc
AS = as
LD = ld
CFLAGS = -O2 -ffreestanding -nostdlib -nostdinc
LDFLAGS = -T ant.ld

$(KERNEL_NAME): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@
	strip $(KERNEL_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.S
	$(AS) --64 $< -o $@

.PHONY: clean

clean:
	rm -rf *.o $(KERNEL_NAME)
