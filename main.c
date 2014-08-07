#include <pic16/delay.h>
#include <pic16/pic18f452.h>
#include <delay.h>

#pragma config WDT=OFF,LVP=OFF

static volatile unsigned char ucConductors = 16;
static volatile unsigned char ucMap[16];

#define CLOCKFREQ    32768

// bit macros
#define  testbit(var, bit)   ((var) & (1 <<(bit)))
#define  setbit(var, bit)    ((var) |= (1 << (bit)))
#define  clrbit(var, bit)    ((var) &= ~(1 << (bit)))

static void delay_ms(unsigned short ms)
{
    delay10tcy(ms * CLOCKFREQ / 4 / 1000 / 10);
}

static unsigned char testinput(unsigned char ucIndex)
{
    unsigned char ucRc = 0;
    unsigned char porta = PORTA;
    unsigned char portb = PORTB;

    switch (ucIndex) {
    case 0:
	ucRc = testbit(PORTA, 0);
	break;
    case 1:
	ucRc = testbit(PORTA, 1);
	break;
    case 2:
	ucRc = testbit(PORTA, 2);
	break;
    case 3:
	ucRc = testbit(PORTA, 3);
	break;
    case 4:
	ucRc = testbit(PORTA, 4);
	break;
    case 5:
	ucRc = testbit(PORTA, 5);
	break;
    case 6:
	ucRc = testbit(PORTA, 6);
	break;
    case 7:
	ucRc = testbit(PORTA, 7);
	break;

    case 8:
	ucRc = testbit(portb, 0);
	break;
    case 9:
	ucRc = testbit(portb, 1);
	break;
    case 10:
	ucRc = testbit(portb, 2);
	break;
    case 11:
	ucRc = testbit(portb, 3);
	break;
    case 12:
	ucRc = testbit(portb, 4);
	break;
    case 13:
	ucRc = testbit(portb, 5);
	break;
    case 14:
	ucRc = testbit(portb, 6);
	break;
    case 15:
	ucRc = testbit(portb, 7);
	break;
    }

    return ucRc;
}

static void test_cable()
{
    unsigned char ii, jj;
    for (ii = 0; ii < 8; ++ii) {
	setbit(LATC, ii);	// raise port
	ucMap[ii] = 0;
	for (jj = 0; jj < 8; ++jj) {
	    if (testinput(jj)) {
		setbit(ucMap[ii], jj);
	    }
	}
	delay_ms(1000);
	clrbit(PORTC, ii);	// drop port
    }

    for (ii = 8; ii < 16; ++ii) {
	setbit(LATD, ii - 8);	// raise port
	delay_ms(2000);
	ucMap[ii] = 0;
	for (jj = 8; jj < 16; ++jj) {
	    if (testinput(jj)) {
		setbit(ucMap[ii], jj);
	    }
	}
	delay_ms(1000);
	clrbit(PORTD, ii - 8);	// drop port
    }
}

void main(void)
{
    INTCON = 0;			// no interrupts
    TRISA = 0xFF;		// input
    TRISB = 0xFF;		// input
    TRISC = 0x00;		// output
    TRISD = 0x00;		// output

    LATC = 0x00;
    LATD = 0x00;
    while (1)
	test_cable();
}
