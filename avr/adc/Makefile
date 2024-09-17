MCU ?= atmega32a

build: main.elf

main.elf: main.c uart.c
	avr-gcc -O1 -mmcu=$(MCU) $^ -o $@
	avr-objcopy -O ihex -R .eeprom main.elf main.hex

burn: build
	avrdude -c usbasp -p m32 -U flash:w:main.hex

clean:
	rm *.hex *.elf
