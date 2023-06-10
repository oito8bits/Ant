ENTRY(_start)

virtual = 0xFFFFFFFF80000000;
physical = 0x1000000;
address = virtual + physical;

SECTIONS
{
  _start = physical;
  . =  address; 

  .text ALIGN(0x1000): AT(ADDR(.text) - virtual)
  {
    *(.text)
  }

  .data ALIGN(0x1000): AT(ADDR(.text) - virtual)
  {
    *(.data)
  }
}
