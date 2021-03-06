all: 
	sdcc --funsigned-char --fverbose-asm --debug --cyclomatic --verbose -mpic16 -p18f452 --debug-xtra --debug-ralloc --pcode-verbose --calltree --use-non-free main.c

sim:
	gpsim main.hex -s main.cod

prog: 
	pk2cmd -P PIC18F452 -X -M -F main.hex

run:
	pk2cmd -P PIC18F452 -T

stop:
	pk2cmd -P PIC18F452
