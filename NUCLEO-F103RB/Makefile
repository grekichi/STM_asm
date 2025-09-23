
ARMGNU = arm-none-eabi

XCPU = -mcpu=cortex-m3

AOPS = --warn --fatal-warnings $(XCPU)

COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding $(XCPU)

.PHONY: all clean

all: stm_blinker01.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f *.hex

#---------------------------------------------------

flash.o : flash.s
	$(ARMGNU)-as $(AOPS) flash.s -o flash.o

stm_blinker01.o : blinker01.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c blinker01.c -o stm_blinker01.o

stm_blinker01.bin : flash.ld flash.o stm_blinker01.o
	$(ARMGNU)-ld -o stm_blinker01.elf -T flash.ld flash.o stm_blinker01.o
	$(ARMGNU)-objdump -D stm_blinker01.elf > stm_blinker01.list
	$(ARMGNU)-objcopy stm_blinker01.elf stm_blinker01.bin -O binary
