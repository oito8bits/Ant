ANT_IMG=Ant.img

Ant.img: BOOTX64.EFI ant_kernel
	dd if=/dev/zero of=$(ANT_IMG) bs=1024 count=46875
	
	mkfs.fat -v -F32 $(ANT_IMG)
	
	mkdir ant_dir/
	sudo mount $(ANT_IMG) ant_dir
	sudo mkdir ant_dir/efi/boot -p
	sudo mkdir ant_dir/boot -p
	sudo cp antboot/BOOTX64.EFI ant_dir/efi/boot/
	sudo cp antkernel/ant_kernel ant_dir/boot/
	sudo umount Ant.img
	rmdir ant_dir

ant_kernel:
	make -C antkernel/

BOOTX64.EFI:
	make -C antboot/

.PHONY: clean run_vnc run

clean:
	make clean -C antboot/
	make clean -C antkernel/
	rm Ant.img

run:
	qemu-system-x86_64 -L /usr/share/edk2-ovmf/x64/ -bios OVMF.fd -drive file=Ant.img,format=raw -m 3G -smp 4
debug:
	qemu-system-x86_64 -L /usr/share/edk2-ovmf/x64/ -bios OVMF.fd -drive file=Ant.img,format=raw -m 3G -s -S -smp 4
