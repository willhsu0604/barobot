#include <Arduino.h>

/*------------------------------    i2c     ------------------------------*/
//#define I2C_ADR_MASTER 0x01
#define I2C_ADR_MAINBOARD 0x01
#define I2C_ADR_RESERVED 0x06
#define I2C_ADR_PROGRAMMER 0x07
//#define I2C_ADR_TROLLEY 0x09
#define I2C_ADR_IPANEL 0x0A
#define I2C_ADR_USTART 0x0B
#define I2C_ADR_UEND 0x70

/*------------------------------ MAINBOARD  ------------------------------*/
#define MAINBOARD_DEVICE_TYPE 0x10
#define MAINBOARD_VERSION 0x01
#define MAINBOARD_F_CPU 16000000
#define MAINBOARD_CPU "atmega328"
#define MAINBOARD_SERIAL0_BOUND 115200


/*------------------------------ IPANEL (carret)    ------------------------------*/
#define IPANEL_DEVICE_TYPE 0x11
#define IPANEL_VERSION 0x01
#define IPANEL_F_CPU == 16000000
#define IPANEL_CPU "atmega328"
#define IPANEL_SERIAL0_BOUND 115200


/*------------------------------ PROGRAMMER ------------------------------*/
#define PROGRAMMER_DEVICE_TYPE 0x14
#define PROGRAMMER_VERSION 0x01
#define PROGRAMMER_F_CPU 12000000
#define PROGRAMMER_CPU "atmega8"


/*------------------------------ OTHER ------------------------------*/
#define COUNT_UPANEL 12
#define COUNT_UPANEL_ONBOARD_LED 8
#define COUNT_IPANEL 1
#define COUNT_IPANEL_ONBOARD_LED 8


/*------------------ MAINBOARD -------------------*/
#if IS_MAINBOARD

	#define MAINBOARD_USE_BT false
	#define MAINBOARD_USE_SERIAL0 true
	#define SERIAL0_BOUND MAINBOARD_SERIAL0_BOUND
	
	#define MAINBOARD_BT_BOUND 115200
	#define MAINBOARD_BT_DEV_NAME "barobotA"


	// czy wyl�czaj stepper X gdy zajechal za miejsce?
	#define MAINBOARD_STEPPER_READY_DISABLE true
	#define MAINBOARD_SERVO_4PIN false

	#define MAINBOARD_BUFFER_LENGTH 3

	// domyslnie ustawienie mocy silnikow Xy
	#if MAINBOARD_SERVO_4PIN==true
	  #define MAINBOARD_SPEEDX 400
	  #define MAINBOARD_ACCELERX 1050
	  #define MAINBOARD_XLENGTH 1700
	#else
	  #define MAINBOARD_SPEEDX 4000
	  #define MAINBOARD_ACCELERX 9000
	  #define MAINBOARD_XLENGTH 12700
	#endif

	// silniki 2-pin (easy driver, palulu)
		#define PIN_MAINBOARD_STEPPER_ENABLE 14			// arduino PIN 14
		#define PIN_MAINBOARD_STEPPER_STEP 4
		#define PIN_MAINBOARD_STEPPER_DIR 5

		#define PIN_MAINBOARD_STEPPER_MS1 15			// microstepping controll 1
		#define PIN_MAINBOARD_STEPPER_MS2 16			// microstepping controll 2
		#define PIN_MAINBOARD_STEPPER_MS3 17			// microstepping controll 3

	// silniki 4-pin (LMxxxx)
		#define PIN_MAINBOARD_STEPPER_STEP0 14
		#define PIN_MAINBOARD_STEPPER_STEP1 15
		#define PIN_MAINBOARD_STEPPER_STEP2 16
		#define PIN_MAINBOARD_STEPPER_STEP3 17

	// Set as INPUT to allow programming over ISP
	#define PIN_MAINBOARD_SCK SCK			// 13
	#define PIN_MAINBOARD_MISO MISO			// 11
	#define PIN_MAINBOARD_MOSI MOSI			// 12

	#define PIN_MAINBOARD_SDA SDA			// arduino 18
	#define PIN_MAINBOARD_SCL SCL			// arduino 19
	
	#if IS_PROGRAMMER	
		#define HWVER		2
		#define SWMAJ		1
		#define SWMIN		18
		#define PTIME       30
		#define STK_OK      0x10
		#define STK_FAILED  0x11
		#define STK_UNKNOWN 0x12
		#define STK_INSYNC  0x14
		#define STK_NOSYNC  0x15
		#define CRC_EOP     0x20
		#define beget16(addr) (*addr * 256 + *(addr+1) )


		//#define PROGRAMMER_SERIAL0_BOUND 115200
		#define PROGRAMMER_SERIAL0_BOUND 19200
		//#define PIN_PROGRAMMER_RESET_MAINBOARD 7

		#define PIN_PROGRAMMER_LED_OTHER   	3		// PWM dip ??
		#define PIN_PROGRAMMER_LED_ERROR   	6		// PWM dip ??		Lights up if something goes wrong (use red if that makes sense)
		#define PIN_PROGRAMMER_LED_ACTIVE	9		// PWM dip ??		shows the programmer is running
		#define PIN_PROGRAMMER_LED_STATE    10		// PWM dip ??		In communication with the slave
		
		#define PIN_PROGRAMMER_RESET_UPANEL 7		// dip ??
		#define PIN_PROGRAMMER_RESET_IPANEL 8		// dip ??
		#define PIN_PROGRAMMER_RESET_MASTER 15		// dip ??

		#define PROGRAMMER_METHOD_PIN	true
		#define PROGRAMMER_METHOD_RPC	false
		
	#endif

#endif

/*------------------ IPANEL -------------------*/
#if IS_IPANEL

	/*
		Komponenty:

		HALL_X	: getValue
		HALL_Y	: getValue

		SERVO_Y	: setSpeed, setPos, getPos
		SERVO_Z	: setSpeed, setPos, getPos

		WEIGHT_SENSOR	getValue,
		8xLED			set PWMUP,PWMDOWN,FadeUp, FadeDown,TimeUp,TimeDown
		I2C				getValue, test_slave
	*/

	#define IPANEL_COMMON_ANODE false		// sterowanie plusem? false gdy sterowaniem minusem
	#define IPANEL_BUFFER_LENGTH 6			// i2c input buffer
	#define SERIAL0_BOUND MAINBOARD_SERIAL0_BOUND
		
	// domyslen ustawienie mocy silnika Z
	// pozycja jechania do g�ry i czas jechania
	#define IPANEL_SERVOZ_UP_POS 2200

	// pozycja jechania w d� i czas jechania
	#define IPANEL_SERVOZ_DOWN_POS 900

	#define PIN_IPANEL_SDA SDA
	#define PIN_IPANEL_SCL SCL
	
	// set as INPUT to allow programming over ISP
	#define PIN_IPANEL_SCK 13			// dip pin 17,
	#define PIN_IPANEL_MISO 11			// dip pin 18,
	#define PIN_IPANEL_MOSI 12			// dip pin 19,

	#define PIN_IPANEL_HALL_X A0		// dip pin 23 A0,	Q 23
	#define PIN_IPANEL_HALL_Y A1		// dip pin 24 A1,	Q 24
	#define PIN_IPANEL_WEIGHT A2		// dip pin 25 A2,	Q 25

	#define PIN_IPANEL_SERVO_Y 5		// dip pin 11,	Q 9
	#define PIN_IPANEL_SERVO_Z 6		// dip pin 12,	Q 10

	#define PIN_IPANEL_LED0_NUM	2		// dip pin 4		Q 32
	#define PIN_IPANEL_LED1_NUM	3		// dip pin 5		Q 1
	#define PIN_IPANEL_LED2_NUM	4		// dip pin 6,		Q 2
	#define PIN_IPANEL_LED3_NUM	7		// dip pin 13,		Q 11
	#define PIN_IPANEL_LED4_NUM	8		// dip pin 14,		Q 12
	#define PIN_IPANEL_LED5_NUM	9		// dip pin 15,		Q 13
	#define PIN_IPANEL_LED6_NUM	10		// dip pin 16		Q 14
	#define PIN_IPANEL_LED7_NUM	17		// dip pin 26 A3,	Q 26

	#define PIN_IPANEL_LED0_MASK	digital_pin_to_bit_mask_PGM+PIN_IPANEL_LED0_NUM
	#define PIN_IPANEL_LED1_MASK	digital_pin_to_bit_mask_PGM+PIN_IPANEL_LED1_NUM
	#define PIN_IPANEL_LED2_MASK	digital_pin_to_bit_mask_PGM+PIN_IPANEL_LED2_NUM
	#define PIN_IPANEL_LED3_MASK	digital_pin_to_bit_mask_PGM+PIN_IPANEL_LED3_NUM
	#define PIN_IPANEL_LED4_MASK	digital_pin_to_bit_mask_PGM+PIN_IPANEL_LED4_NUM
	#define PIN_IPANEL_LED5_MASK	digital_pin_to_bit_mask_PGM+PIN_IPANEL_LED5_NUM
	#define PIN_IPANEL_LED6_MASK	digital_pin_to_bit_mask_PGM+PIN_IPANEL_LED6_NUM
	#define PIN_IPANEL_LED7_MASK	digital_pin_to_bit_mask_PGM+PIN_IPANEL_LED7_NUM
	
	#define LED_TOP_RED					PIN_IPANEL_LED0_NUM
	#define LED_TOP_BLUE				PIN_IPANEL_LED1_NUM
	#define LED_TOP_GREEN				PIN_IPANEL_LED2_NUM
	#define LED_TOP_WHITE				PIN_IPANEL_LED3_NUM
	#define LED_BOTTOM_RED				PIN_IPANEL_LED4_NUM
	#define LED_BOTTOM_BLUE				PIN_IPANEL_LED5_NUM
	#define LED_BOTTOM_GREEN			PIN_IPANEL_LED6_NUM
	#define LED_BOTTOM_WHITE			PIN_IPANEL_LED7_NUM
	
	
	// EEPROM content:
	/*
	0x00	- NEUTRAL_VALUE kopia 0
	0x01	- NEUTRAL_VALUE kopia 1
	*/

#endif


/*------------------------------  UPANEL    ------------------------------*/

#define UPANEL_DEVICE_TYPE 0x13
#define UPANEL_VERSION 0x01
#define UPANEL_F_CPU 8000000
#define UPANEL_CPU "atmega8"
#define UPANEL_SERIAL0_BOUND 115200

#if IS_UPANEL
	#define UPANEL_COMMON_ANODE false		// sterowanie plusem? false gdy sterowaniem minusem
	#define SERIAL0_BOUND UPANEL_SERIAL0_BOUND

	// set as INPUT do allow programming over ISP
	#define PIN_UPANEL_SCK SCK				// dip pin 17
	#define PIN_UPANEL_MISO MISO				// dip pin 18
	#define PIN_UPANEL_MOSI MOSI				// dip pin 19

	#define PIN_UPANEL_LEFT_RESET 14		// dip pin 23
	#define PIN_UPANEL_POKE 3				// dip pin 5
		
	#define PIN_UPANEL_SDA SDA
	#define PIN_UPANEL_SCL SCL
	
	#define PIN_UPANEL_LED0_NUM	4		// dip pin 6,		Q 2
	#define PIN_UPANEL_LED1_NUM	5		// dip pin 11,		Q 9
	#define PIN_UPANEL_LED2_NUM	6		// dip pin 12,		Q 10
	#define PIN_UPANEL_LED3_NUM	7		// dip pin 13,		Q 11
	#define PIN_UPANEL_LED4_NUM	8		// dip pin 14,		Q 12
	#define PIN_UPANEL_LED5_NUM	9		// dip pin 15,		Q 13
	#define PIN_UPANEL_LED6_NUM	16		// dip pin 25 A2,	Q 25
	#define PIN_UPANEL_LED7_NUM	17		// dip pin 26 A3,	Q 26

	#define PIN_UPANEL_LED0_MASK	digital_pin_to_bit_mask_PGM+PIN_UPANEL_LED0_NUM
	#define PIN_UPANEL_LED1_MASK	digital_pin_to_bit_mask_PGM+PIN_UPANEL_LED1_NUM
	#define PIN_UPANEL_LED2_MASK	digital_pin_to_bit_mask_PGM+PIN_UPANEL_LED2_NUM
	#define PIN_UPANEL_LED3_MASK	digital_pin_to_bit_mask_PGM+PIN_UPANEL_LED3_NUM
	#define PIN_UPANEL_LED4_MASK	digital_pin_to_bit_mask_PGM+PIN_UPANEL_LED4_NUM
	#define PIN_UPANEL_LED5_MASK	digital_pin_to_bit_mask_PGM+PIN_UPANEL_LED5_NUM
	#define PIN_UPANEL_LED6_MASK	digital_pin_to_bit_mask_PGM+PIN_UPANEL_LED6_NUM
	#define PIN_UPANEL_LED7_MASK	digital_pin_to_bit_mask_PGM+PIN_UPANEL_LED7_NUM

	#define LED_TOP_RED					PIN_UPANEL_LED0_NUM
	#define LED_TOP_BLUE				PIN_UPANEL_LED1_NUM
	#define LED_TOP_GREEN				PIN_UPANEL_LED2_NUM
	#define LED_TOP_WHITE				PIN_UPANEL_LED3_NUM
	#define LED_BOTTOM_RED				PIN_UPANEL_LED4_NUM
	#define LED_BOTTOM_BLUE				PIN_UPANEL_LED5_NUM
	#define LED_BOTTOM_GREEN			PIN_UPANEL_LED6_NUM
	#define LED_BOTTOM_WHITE			PIN_UPANEL_LED7_NUM
	

	// EEPROM content:
	/*
	0x00	- i2c adres kopia 0
	0x01	- i2c adres kopia 1
	0x02	- i2c adres kopia 2

	0xF0	- starts m�odsze
	0xF1	- starts starsze
	
	0xF2	- i2c errors m�odsze
	0xF3	- i2c errors starsze

	0xFA	- watchdog m�odsze
	0xFB	- watchdog starsze
	*/
	
#endif

#if 1
#define DEBUGINIT(sth) (Serial.begin(SERIAL0_BOUND))
#define DEBUG(sth) (Serial.print(String(sth)))
#define DEBUGLN(sth) (Serial.println(String(sth)))
#else
#define DEBUGINIT(sth)
#define DEBUG(sth)
#define DEBUGLN(sth)
#endif

#define METHOD_GETVERSION 	5
#define METHOD_PROG_MODE_ON 	10
#define METHOD_PROG_MODE_OFF 	14
#define METHOD_TEST_SLAVE 	19
#define METHOD_RESETCYCLES 	20
#define METHOD_SETPWM 	38
#define METHOD_SETTIME 	42
#define METHOD_SETFADING 	46
#define METHOD_RESETSLAVEADDRESS 	50
#define METHOD_GETANALOGVALUE 	51
#define METHOD_GETVALUE 	55
#define METHOD_RESET_NEXT 	58
#define METHOD_RUN_NEXT 	62
#define METHOD_GETSERVOYPOS 	65
#define METHOD_GOTOSERVOYPOS 	66
#define METHOD_GETSERVOZPOS 	69
#define METHOD_GOTOSERVOZPOS 	70
#define METHOD_HERE_I_AM 	114
#define METHOD_SEND_PIN_VALUE 	118
#define METHOD_I2C_SLAVEMSG 	122
#define METHOD_LIVE_ANALOG 	74
#define METHOD_LIVE_OFF 	72
#define METHOD_SEND2SLAVE 	127
#define METHOD_DRIVER_ENABLE 	82
#define METHOD_DRIVER_DISABLE 	86

#define METHOD_RET_FROM_SLAVE 	88
#define METHOD_I2C_ERROR 		90
#define METHOD_RET_FROM_SLAVE2 	92


#define RETURN_PIN_VALUE 		211
//#define RETURN_ANALOG_CHANGE 	111





#define INNER_SERVOY  0
#define INNER_SERVOZ  1

#define DRIVER_X 	4
#define DRIVER_Y 	8
#define DRIVER_Z 	16

#define RETURN_DRIVER_ERROR 	211
#define RETURN_DRIVER_READY 	211



#if HAS_LEDS
	typedef struct{ 
	  uint8_t pin;      // hardware I/O port and pin for this channel
	  volatile uint8_t *outport;
	  uint8_t pinmask;
	  uint8_t current_pwm;
	  uint8_t fadeup;      // 0- 15
	  uint8_t fadedown;    // 0- 15
	  uint8_t pwmup;       // PWM przy UP
	  uint8_t pwmdown;     // PWM przy DOWN
	  uint8_t timedown;    // Czas trwania UP
	  uint8_t timeup;      // Czas trwania DOWN
	} PWMChannel;

	volatile PWMChannel _pwm_channels[COUNT_UPANEL_ONBOARD_LED]= {
		{4,0,0,0,0,0},
		{5,0,0,0,0,0},
		{6,0,0,0,0,0},
		{7,0,0,0,0,0},
		{8,0,0,0,0,0},
		{9,0,0,0,0,0},
		{16,0,0,0,0,0},
		{17,0,0,0,0,0}
	};
	boolean prog_mode  = false;    // czy magistrala jest w trybie programowania?
	boolean prog_me    = false;    // czymam zamiar programowa� mnie?
	
#endif


/* 
DIP28
	pin01	PC6	arduino ??		RESET	- CONN1
	pin02	PD0	arduino 00		RX		- CONN2
	pin03	PD1	arduino 01		TX		- CONN2
	pin04	PD2	arduino 02		INT0	- SWITCH
	pin05	PD3	arduino 03		INT1	- CONN1
	pin06	PD4	arduino 04		-
	pin07	VCC
	pin08	GND	
	pin09	PB6	arduino ??		XTAL1 
	pin10	PB7	arduino ??		XTAL2	
	pin11	PD5	arduino 05		-
	pin12	PD6	arduino 06		-
	pin13	PD7	arduino 07		-
	pin14	PB0	arduino 08		- 
	pin15	PB1	arduino 09				-SERVO_X
	pin16	PB2	arduino 10		SS		-SERVO_Y
	pin17	PB3	arduino 11		MOSI	-CONN1
	pin18	PB4	arduino 12		MISO	-CONN1
	pin19	PB5	arduino 13		SCK		-CONN1
	pin20	AVCC	
	pin21	AREF	
	pin22	GND	
	pin23	PC0	arduino A0/D14	ADC0	HALL_X 
	pin24	PC1	arduino A1/D15	ADC1	HALL_Y 
	pin25	PC2	arduino A2/D16	ADC2	WEIGHT
	pin26	PC3	arduino A3/D17	ADC3	
	pin27	PC4	arduino A4/D18	ADC4	SDA	-CONN1
	pin28	PC5	arduino A5/D19	ADC5	SCL	-CONN1


ATMEGA8 / ARDUINO
                  +-\/-+
            PC6  1|    |28  PC5 (A5/ D19) (SDA)
  RX  (D0)  PD0  2|    |27  PC4 (A4/ D18) (SCL)
  TX  (D1)  PD1  3|    |26  PC3 (A3/ D17)
 INT0 (D2)  PD2  4|    |25  PC2 (A2/ D16)
 INT1 (D3)  PD3  5|    |24  PC1 (A1/ D15)
 XCK  (D4)  PD4  6|    |23  PC0 (A0/ D14)
            VCC  7|    |22  GND
            GND  8|    |21  AREF
 XTAL       PB6  9|    |20  AVCC
 XTAL       PB7 10|    |19  PB5 (D13) SCK
      (D5)  PD5 11|    |18  PB4 (D12) MISO
 AIN0 (D6)  PD6 12|    |17  PB3 (D11) MOSI PWM
 AIN1 (D7)  PD7 13|    |16  PB2 (D10) SS PWM
      (D8)  PB0 14|    |15  PB1 (D9) PWM
                  +----+


ARDUINO DIP to TQFP
PIN			DIP		TQFP
0			2		30		PD0
1			3		31		PD1
2			4		32		PD2
3			5		1		PD3
4			6		2		PD4
5			11		9		PD5
6			12		10		PD6
7			13		11		PD7
8			14		12		PB0
9			15		13		PB1
10			16		14		PB2
11			17		15		PB3
12			18		16		PB4
13			19		17		PB5
14	A0		23		23		PC0
15	A1		24		24		PC1
16	A2		25		25		PC2
17	A3		26		26		PC3
18	A4		27		27		PC4
19	A5		28		28		PC5

RESET		1		29		PC6
XTAL1		9		7		PB6
XTAL2		10		8		PB7

TQFP32
	pin01	PD3	arduino 03	PWM	- CONN1
	pin02	PD4	arduino 04
	pin03	GND
	pin04	VCC
	pin05	GND
	pin06	VCC
	pin07	PB6	arduino ??	XTAL1 
	pin08	PB7	arduino ??	XTAL2
	pin09	PD5	arduino 05	PWM			-SERVO_Y
	pin10	PD6	arduino 06	PWM			-SERVO_Z
	pin11	PD7	arduino 07				- 
	pin12	PB0	arduino 08				-
	pin13	PB1	arduino 09		
	pin14	PB2	arduino 10	PWM,SS

	pin15	PB3	arduino 11	MOSI		-CONN1
	pin16	PB4	arduino 12	MISO		-CONN1
	pin17	PB5	arduino 13	SCK			-CONN1
	pin18	AVCC
	pin19	ADC6	??
	pin20	AREF
	pin21	GND
	pin22	ADC7	??
	pin23	PC0	arduino A0/D14	ADC0	-HALL_X  
	pin24	PC1	arduino A1/D15	ADC1	-HALL_Y 
	pin25	PC2	arduino A2/D16	ADC2	-WEIGHT
	pin26	PC3	arduino A3/D17	ADC3	-
	pin27	PC4	arduino A4/D18	ADC4	-SDA	-CONN1
	pin28	PC5	arduino A5/D19	ADC5	-SCL	-CONN1
	pin29	PC6	arduino ??		RESET	-CONN1
	pin30	PD0	arduino 00		RX		-CONN2
	pin31	PD1	arduino 01		TX		-CONN2
	pin32	PD2	arduino 02		INT0	-

*/

/*








boolean i2c_getValue(  byte slave_address, byte pin ){      // zwraca 2 bajty. typ na m�odszych bitach, versja na starszych
  out_buffer[0]  = METHOD_GETVALUE;
  out_buffer[1]  = pin;
  byte error = writeRegisters(slave_address, 2, true );
  if(!error){
    readRegisters( slave_address, 1 );
    byte res = in_buffer[0];    // = wersja
    if( res == 0 ){
      return false;
    }
    if( res == 0xFF ){
       return true;
    }
    // todo. zwr�c true ale raportuj warning
    return true;
  }
  return false;
}



void i2c_reloadAddress( byte slave_address, byte new_addr ){			// Zmie� adres I2c, musi by� podane co najmniej 4 razy zeby zadzia�a�o. (2 bajty)
  out_buffer[0]  = METHOD_RESETSLAVEADDRESS;
  out_buffer[1]  = new_addr;
  writeRegisters(slave_address, 2, true );    // powtarzaj
  writeRegisters(slave_address, 2, true );
  writeRegisters(slave_address, 2, true );
  writeRegisters(slave_address, 2, true );
  writeRegisters(slave_address, 2, true );
}



void i2c_resetCycles( byte slave_address ){
  out_buffer[0]  = METHOD_RESETCYCLES;
  writeRegisters(slave_address, 1, true );
}
void i2c_setPWM( byte slave_address, byte pin, byte level ){		                              // Wpisz wype�nienie PWM do LEDa ( 3 bajty )
  out_buffer[0]  = METHOD_SETPWM;
  out_buffer[1]  = pin;
  out_buffer[2]  = level;
  writeRegisters(slave_address, 3, true );
}
void i2c_setTime( byte slave_address, byte pin, byte on_time, byte off_time ){			            // Czas pomi�dzy kolejnym zapaleniem i Czas od zapalenia do zgaszenia ( 4 bajty )
  out_buffer[0]  = METHOD_SETTIME;
  out_buffer[1]  = pin;
  out_buffer[2]  = on_time;
  out_buffer[3]  = off_time;
  writeRegisters(slave_address, 3, true );
}
void i2c_setFading( byte slave_address,  byte pin, byte level_in, byte level_out ){			       // Czas i kierunek zanikania PWMa	( 4 bajty )
  out_buffer[0]  = METHOD_SETFADING;
  out_buffer[1]  = pin;
  out_buffer[2]  = level_in;
  out_buffer[2]  = level_out;
  writeRegisters(slave_address, 2, true );
}













ANDROID:	
	- mainboard
	- upanel
	- carret

MAINBOARD:
	- android
	- upanel
	- carret

	
upanel:	
	- android
	- mainboard
	- carret

CARRET:	
	- android
	- mainboard
	- upanel









Master:
- X
	enable X
	disable X

	move Z




Carret:
	enable Y
	enable Z

	disable Y
	disable Z
	
	move Y
	move Z

	hall X
	hall Y
	
	






X5,40,200
X55,60,-1250

D:\PROG\arduino-1.0.5\hardware/tools/avr/bin/avrdude -CD:\PROG\arduino-1.0.5\hardware/tools/avr/etc/avrdude.conf -v -v -v -v -D -patmega8 -cstk500v1 -P\\.\COM43 -b19200 -Uflash:w:c:\temp\build7005077114599572471.tmp\atmega8_i2c_slave.cpp.hex:i -Ulock:w:0x3F:m -Uhfuse:w:0xc4:m -Ulfuse:w:0xe4:m
D:\PROG\arduino-1.0.5\hardware/tools/avr/bin/avrdude -CD:\PROG\arduino-1.0.5\hardware/tools/avr/etc/avrdude.conf -v -v -v -v -D -patmega8 -cstk500v1 -P\\.\COM43 -b19200 -Ulock:w:0x3F:m -Uhfuse:w:0xc4:m -Ulfuse:w:0xe4:m
D:\PROG\arduino-1.0.5\hardware/tools/avr/bin/avrdude -CD:\PROG\arduino-1.0.5\hardware/tools/avr/etc/avrdude.conf -v -v -v -v -patmega8 -cstk500v1 -P\\.\COM43 -b19200 -Uflash:w:c:\temp\build7005077114599572471.tmp\atmega8_i2c_slave.cpp.hex:i

*/





