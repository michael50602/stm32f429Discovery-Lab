MEMORY{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 2048K
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 112K
}

SECTIONS {
	.text : {
		KEEP(*(.isr_vector))
		*(.text)
		*(.rodata)
		. = ALIGN(4);
		_etext = . ;
	} > FLASH
	.data : {
		_data = . ;
		*(.data)
		. = ALIGN(4);
		_edata = . ;
	} > SRAM
	.bss : {
		_bss = . ;
		*(.bss)
		. = ALIGN(4);
		_ebss = . ;
	} > SRAM

	_end = . ;
}
