SCRIPT = lightbarButton

all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o ${SCRIPT}.o ${SCRIPT}.c
	avr-gcc -mmcu=atmega328p ${SCRIPT}.o -o ${SCRIPT}.elf
	avr-objcopy -O ihex -R .eeprom ${SCRIPT}.elf ${SCRIPT}.hex

arduino:
	make clean
	make
	sudo avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:${SCRIPT}.hex:i 

clean:
	rm ${SCRIPT}.elf ${SCRIPT}.o ${SCRIPT}.hex