.PHONY: clean

include ~/rv32emu/mk/toolchain.mk

ASFLAGS = -march=rv32i -mabi=ilp32
LDFLAGS = --oformat=elf32-littleriscv

%.o: %.S
	$(CROSS_COMPILE)as -R $(ASFLAGS) -o $@ $<

all: hw2.elf

hw2.elf: hw2.o
	 $(CROSS_COMPILE)ld -o $@ -T hw2.ld $(LDFLAGS) $<

clean:
	$(RM) hw2.elf hw2.o
