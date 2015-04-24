CROSS_COMPILE ?= arm-none-eabi-
.PHONY: all
all: blink.bin
blink.o: blink.c
		$(CROSS_COMPILE)gcc -mtune=cortex-m4 -mthumb -nostartfiles -c blink.c -o blink.o
blink.out: blink.o simple.ld
		$(CROSS_COMPILE)ld -T simple.ld -o blink.out blink.o
blink.bin: blink.out
		$(CROSS_COMPILE)objcopy -j .text -O binary blink.out blink.bin
flash: $(blink.bin)
	st-flash write blink.bin 0x8000000
#	openocd \
		-f interface/stlink-v2.cfg \
		-f target/stm32f4x.cfg \
		-c "init" \
		-c "reset init" \
		-c "flash probe 0" \
		-c "flash info 0" \
		-c "flash write_image erase blink.bin 0x8000000" \
		-c "reset run" -c shutdown 
#	st-flash write blink.bin 0x8000000
clean:
		rm -f *.o *.out *.bin
