all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o script.o script.c
	avr-gcc -mmcu=atmega328p script.o -o script.elf
	avr-objcopy -O ihex -R .eeprom script.elf script.hex

arduino:
	make clean
	make
	sudo avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:script.hex:i 

clean:
	rm script.elf script.o script.hex