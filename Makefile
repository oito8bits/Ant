ANT_IMG=Ant.img

ant_img: BOOTX64.EFI ant_kernel
	dd if=/dev/zero of=$(ANT_IMG) bs=1024 count=46875
	
	sudo mkfs.fat -v -F32 $(ANT_IMG)
	
	mkdir ant_dir/
	sudo mount $(ANT_IMG) ant_dir
	sudo mkdir ant_dir/efi/boot -p
	sudo mkdir ant_dir/boot -p
	sudo cp boot/efi/BOOTX64.EFI ant_dir/efi/boot/
	sudo cp kernel/arch/x86_64/ant_kernel ant_dir/boot/
	sudo umount $(ANT_IMG)
	rmdir ant_dir

ant_kernel:
	make -C kernel/arch/x86_64/

BOOTX64.EFI:
	make -C boot/efi/

.PHONY: clean run_vnc run

clean:
	make clean -C boot/efi
	make clean -C kernel/arch/x86_64/
	rm Ant.img

run_vnc:
	qemu-system-x86_64 -vnc :0 -L /usr/share/edk2-ovmf/x64/ -bios OVMF.fd -drive file=Ant.img,format=raw
run:
	qemu-system-x86_64 -L /usr/share/edk2-ovmf/x64/ -bios OVMF.fd -drive file=Ant.img,format=raw
