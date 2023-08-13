default: build

build:
	avr-gcc -mmcu=atmega328p main.c -o main.elf

burn:
	avr-objcopy -O ihex -R .eeprom main.elf main.hex
	avrdude -F -v -c arduino -p m328p -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex 
