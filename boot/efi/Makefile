PROG = BOOTX64.EFI
IMG = antboot.img
CC = x86_64-w64-mingw32-gcc
OBJS = efi_main.o

$(IMG): $(PROG)
	dd if=/dev/zero of=antboot.img bs=1k count=2880
	mformat -i antboot.img -f 2880 ::
	mmd -i antboot.img ::/efi
	mmd -i antboot.img ::/efi/boot
	mcopy -i antboot.img BOOTX64.EFI ::/efi/boot/bootx64.efi

$(PROG): $(OBJS) libefi/libefi.a
	$(CC) -nostdlib -Wl,-dll -shared -Wl,--subsystem,10 -e efi_main -o $(PROG) $^  -Llibefi/ -l:libefi.a

%.o: %.c
	$(CC) -O2 -ffreestanding -Ilibefi/include/ -c -o $@ $<

libefi/libefi.a:
	make -C libefi/

.PHONY: clean run

clean:
	rm -rf *.o $(PROG) $(IMG)
	make clean -C libefi/

run:
	qemu-system-x86_64 -bios OVMF.fd -drive file=antboot.img,format=raw	
