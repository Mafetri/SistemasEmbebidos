all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o hello.o hello.c
	avr-gcc -mmcu=atmega328p hello.o -o hello.elf
	avr-objcopy -O ihex -R .eeprom hello.elf hello.hex

arduino:
	make clean
	make
	sudo avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:hello.hex:i 

clean:
	rm hello.elf hello.o hello.hex