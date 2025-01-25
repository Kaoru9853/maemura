//
//
//
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//         PIN NO
//            		                        --------------
//         (PCINT14/RESET)      PC6--------|1           28|------PC5 (ADC5/SCL/PCINT13)
//         (PCINT16/RXD)        PD0--------|2     A     27|------PC4 (ADC4/SDA/PCINT12)
//         (PCINT17/TXD)        PD1--------|3     T     26|------PC3 (ADC3/PCINT11)
//         (PCINT18/INT0)       PD2--------|4           25|------PC2 (ADC2/PCINT10)
//         (PCINT19/OC2B/INT1)  PD3--------|5     M     24|------PC1 (ADC1/PCINT9)
//         (PCINT20/XCK/T0)     PD4--------|6     E     23|------PC0 (ADC0/PCINT8)
//         VCC-----------------------------|7     G     22|----------GND
//         GND-----------------------------|8     A     21|----------AREF
//         (PCINT6/XTAL1/TOSC1) PB6--------|9           20|----------AVCC
//         (PCINT7/XTAL2/TOSC2) PB7--------|10    3     19|------PB5 (SCK/PCINT5)
//         (PCINT21/OC0B/T1)    PD5--------|11    2     18|------PB4 (MISO/PCINT4)
//         (PCINT22/OC0A/AIN0)  PD6--------|12    8     17|------PB3 (MOSI/OC2A/PCINT3)
//         (PCINT23/AIN1)       PD7--------|13    P     16|------PB2 (SS/OC1B/PCINT2)
//         (PCINT0/CLKO/ICP1)   PB0--------|14          15|------PB1 (OC1A/PCINT1)
//                                          --- ----------
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//
//      [ PD7 ]------<1K>------@ @ @ @ @ @ @ @------<1K>-------[ PB7 ]
//      [ PD6 ]------<1K>------@ @ @ @ @ @ @ @------<1K>-------[ PB6 ]
//      [ PD5 ]------<1K>------@ @ @ @ @ @ @ @------<1K>-------[ PB5 ]
//      [ PD4 ]------<1K>------@ @ @ @ @ @ @ @------<1K>-------[ PB4 ]
//      [ PD3 ]------<1K>------@ @ @ @ @ @ @ @------<1K>-------[ PB3 ]
//      [ PD2 ]------<1K>------@ @ @ @ @ @ @ @------<1K>-------[ PB2 ]
//      [ PD1 ]------<1K>------@ @ @ @ @ @ @ @------<1K>-------[ PB1 ]
//      [ PD0 ]------<1K>------@ @ @ @ @ @ @ @------<1K>-------[ PB0 ]
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//
//      [ GND ]---------------[ PushSW  :  UP   ]-------------[ PC0 ]
//      [ GND ]---------------[ PushSW  :  DOWN ]-------------[ PC1 ]
//      [ GND ]---------------[ PushSW  :  SEL  ]-------------[ PC2 ]
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


//   令和7年1月17日金曜日　午前9時15分　作成開始        上間　薫　＠　沖縄県


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char  f_1ms = 0;
volatile unsigned char  ss = 0;
volatile unsigned char  mm = 0;
volatile unsigned char  hh = 0;
volatile unsigned char  week = 0;
unsigned char font_0[]	= {0x7E,0x42,0x42,0x7E,0x42,0x42,0x7E,0x0};		//日
unsigned char font_1[]	= {0x3E,0x22,0x3E,0x22,0x3E,0x42,0x86,0x0};		//月
unsigned char font_2[]	= {0x10,0x10,0x54,0x58,0x10,0x28,0xC6,0x0};		//火
unsigned char font_3[]	= {0x10,0x12,0xF4,0x38,0x54,0x92,0x30,0x0};		//水
unsigned char font_4[]	= {0x10,0xFE,0x10,0x38,0x54,0x92,0x10,0x0};		//木
unsigned char font_5[]	= {0x10,0x28,0xFE,0x10,0xFE,0x54,0xFE,0x0};		//金
unsigned char font_6[]	= {0x10,0x10,0x7C,0x10,0x10,0x10,0xFE,0x0};		//土

void disp( unsigned char week );
void disp8x8( unsigned char w[] );
void initialize( void);
ISR( TIMER1_COMPA_vect );
int main( void );


int main( void )
{
	unsigned char counter = 0;

	initialize();

	sei();

	while( 1 ) {
		while( ! f_1ms) ;
		f_1ms = 0;
		counter++;
		if( counter % 5 == 0 ) disp( 3 );
	}
	return 0;
}

void initialize( void)
{
	DDRB   = _BV( PB0 );
	TCCR1B = _BV( WGM12) | _BV( CS12 );        // TIMER1_CTC,   CK/256
	OCR1A  = 12800000 / 256 / 1000 - 1;        // 1[ms] compare match interrupt
	TCNT1  = 0;
	TIMSK1 = _BV( OCIE1A );
}

void disp( unsigned char week )
{
	if( week==0 ){
		disp8x8( font_0 );   // 日
	} else if( week==1 ) {
		disp8x8( font_1 );   // 月
	} else if( week==2 ) {
		disp8x8( font_2 );   // 火
	} else if( week==3 ) {
		disp8x8( font_3 );   // 水
	} else if( week==4 ) {
		disp8x8( font_4 );   // 木
	} else if( week==5 ) {
		disp8x8( font_5 );   // 金
	} else if( week==6 ) {
		disp8x8( font_6 );   // 土
	}
}


void disp8x8( unsigned char w[] )
{
	for( unsigned char i = 0; i < 7; i++ ) {
		PORTB = w[ i ];
		PORTD = ~( _BV( i ) );
		_delay_us(450);
	}
}

ISR( TIMER1_COMPA_vect )
{
	f_1ms = 1;
}
