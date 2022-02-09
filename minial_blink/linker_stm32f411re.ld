/* linker script */

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH =  128K
}

ENTRY(Reset_Handler)

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector)) /* Vector table */
		*(.text*)         /* Program code */
		*(.rodata*)       /* Read only data */
	} > FLASH

	_etext = ALIGN (4);

	.data : 
	{
		_sdata = .;
		*(vtable)
		*(.data*)         /* Read-write initialized data */

		. = ALIGN(4);
		_edata = .;

	} > RAM

	.bss :
	{
		. = ALIGN(4);
		_sbss = .;
		*(.bss*)       /* Read-write zero initialized data */

		. = ALIGN(4);
		_ebss = .;
	} > RAM

	_estack = ORIGIN(RAM) + LENGTH(RAM);
}
