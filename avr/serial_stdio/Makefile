MCU ?= atmega328p
DEVICE ?= /dev/ttyACM0
BAUD ?= 9600

build: main.elf

main.elf: main.c uart.elf
	avr-gcc -mmcu=$(MCU) $^ -o $@
	avr-objcopy -O ihex -R .eeprom main.elf main.hex

uart.elf: uart.c uart.h
	avr-gcc -mmcu=$(MCU) -c $< -o $@

burn: build
	avrdude -F -v -c arduino -p m328p -P $(DEVICE) -b 115200 -U flash:w:main.hex 

monitor:
	cu -l $(DEVICE) -s $(BAUD)

clean:
	rm *.hex *.elf
