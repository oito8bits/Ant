#by oito8bits
CFLAGS=-m32 -O2 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector

boot.img: boot.bin kernel.elf
	sudo dd if=/dev/zero of=$@ bs=1024 count=16000
	sudo losetup /dev/loop0 $@
	#Crio uma partição FAT16
	sudo mkdosfs -v -F16 /dev/loop0
	mkdir boot/
	sudo mount /dev/loop0 boot/
	sudo mkdir boot/boot
	sudo cp kernel.elf boot/boot
	sudo dd if=$< of=/dev/loop0
	sudo losetup -d /dev/loop0
	sudo umount boot/
	rm -rf boot/

kernel.elf: kernel.o
	ld -melf_i386 -Tkernel.ld -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

boot.bin: boot.o
	ld -melf_i386 -Ttext 0x7c00 --oformat=binary -o $@ $<

%.o: %.S
	as --32 -o $@ $<

.PHONY: clean

clean:
	rm -rf boot/ kernel.elf *.o boot.bin boot.img

run:
	sudo qemu-system-i386 -hda boot.img
