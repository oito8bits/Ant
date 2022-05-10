# by Willian S. Oliveira
.code16

.equ dpa.size, 0
.equ dpa.reserved, 1
.equ dpa.number_of_blocks, 2
.equ dpa.buffer, 4
.equ dpa.lba, 8

.section .text
.global _start
_start:
  jmp boot
  nop
  
  bpb_oem_name: .ascii "MEU OS  "
  bpb_bytes_per_sector: .word 0x200
  bpb_sectors_per_cluster: .byte 0x4
  bpb_reserved_sectors_count: .word 0x4
  bpb_number_of_fats: .byte 0x2
  bpb_root_entries_count: .word 0x200
  bpb_total_sectors_16: .word 0x7d00
  bpb_media: .byte 0xf8
  bpb_fat_size_16: .word 0x20
  bpb_sectors_per_track: .word 0x20
  bpb_number_of_heads: .word 0x40
  bpb_hidden_sector: .long 0x0
  bpb_total_sectors_32: .long 0x0
  bs_drive_number: .byte 0x80
  bs_reserved1: .byte 0x0
  bs_boot_signature: .byte 0x29
  bs_volume_id: .long 0x31332875
  bs_volume_label: .ascii "NO NAME    "
  bs_filesystem_type: .ascii "FAT16   "

boot:
  xorw  %ax, %ax
  movw  %ax, %ds
  movw  %ax, %es
  movw  %ax, %ss
  movw  %ax, %fs
  movw  %ax, %gs

  movw	$0x0003, %ax
  int	  $0x10


  movw	$init_msg, %bp
  movw	$23, %cx
  xorw	%dx, %dx
  call	puts
	
  # Calcula o primeiro setor do diretorio raiz.
  # Essa parte do código é o mesmo que:
  # FirstRootDirSecNum = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16);
  xor   %ax, %ax
  movw	bpb_fat_size_16, %bx
  movb	bpb_number_of_fats, %al
  mulw	%bx
  movw	bpb_reserved_sectors_count, %bx
  addw	%bx, %ax
  movw	%ax, first_root_dir_sector

  # Calcula o total de setores em um diretorio raiz. 
  # Essa parte do código faz o mesmo que: 
  # RootDirSectors = ((BPB_RootEntCnt * 32) + (BPB_BytsPerSec – 1)) / BPB_BytsPerSec;
  movw	bpb_root_entries_count, %ax
  movw	$32, %bx
  mulw	%bx
  movw	bpb_bytes_per_sector, %bx
  subw	$1, %bx
  addw	%bx, %ax
  movw	bpb_bytes_per_sector, %bx
  xorw  %dx, %dx
  divw	%bx
  movw	%ax, root_dir_sectors
  
  movw  first_root_dir_sector, %bx

.loop0:
  movb  $0x10, dpa + dpa.size
  movw  %ax, dpa + dpa.number_of_blocks
  movw  $0x8000, dpa + dpa.buffer
  movw  %bx, dpa + dpa.lba
  movw  $dpa, %si
  movb  $0x42, %ah
  movb  $0x80, %dl
  int   $0x13
  jc    .loop0
  
  
  
  jmp	.

puts:
  movw	$0x1301, %ax
  movw	$0x003B, %bx
  int	$0x10
  ret


.comm dpa, 16

first_root_dir_sector: .word 0x0
root_dir_sectors: .word 0x0
kernel_name: .string "KERNEL.ELF"
init_msg: .string "Iniciando o Kernel...\r\n"

. = _start + 510
.word 0xaa55
