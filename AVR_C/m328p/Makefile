# Makefile

PROG=main
OBJS=$(PROG).o

MCU=atmega328p
F_CPU=12800000UL

#--------
ELF = $(PROG)
LST = $(PROG).lst
IHEX= $(PROG).ihex

CC      = avr-gcc
OBJDUMP = avr-objdump
OBJCOPY = avr-objcopy
SIZE    = avr-size

CFLAGS=-g -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)
LDFLAGS=-g -Os -mmcu=$(MCU)

all: $(LST) $(IHEX)

$(LST):	$(ELF)
	$(OBJDUMP) -h -S $< > $@

$(IHEX): $(ELF)
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
	$(SIZE) --format=avr --mcu=$(MCU) $(ELF)

$(ELF): $(OBJS)

up: $(IHEX)
	hidspx $(IHEX)

upload: $(IHEX)
	hidspx $(IHEX)

clean:
	-$(RM) $(ELF) $(IHEX) $(OBJS) *.lst *~

.PHONY: all clean
