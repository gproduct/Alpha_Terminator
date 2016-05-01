#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "can.h"
#include "actuators.h"

void servo_init(unsigned int f_pwm)
{
	DDRE |= ((1 << PINE3) | (1 << PINE4) | (1 << PINE5));
	DDRB |= (1 << PINB7);//OCR0A
	
	TCNT3 = 0;
	TCNT0 = 0;

	OCR3A = 0;
	OCR3B = 0;
	OCR3C = 0;

	TCCR3A = (1 << COM3A1)  | (1 << COM3B1) | (1 << COM3B0) | (1 << COM3C1) | (1 << COM3C0) | (1 << WGM31);
	TCCR3B = (1<< CS31) | (1 << WGM32) | (1 << WGM33) ; // PRESKALER = 8
	
	//8bit timer for pwm shit
	TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1) | (1 << CS01) | (1 << CS00);

	ICR3   = ((double)F_CPU) / (8.0 * f_pwm) + 0.5;
}

static void servo_set_duty_cycle_umbrella(int16_t value)
{
	uint16_t temp = ((double)ICR3 / 255.0) * value + 0.5;
	OCR3AH = temp >> 8;
	OCR3AL = temp & 0xFF;
}
static void servo_set_duty_cycle_door(int16_t value)
{
	uint16_t temp = ((double)ICR3 / 255.0) * value + 0.5;
	OCR3BH = temp >> 8;
	OCR3BL = temp & 0xFF;
}
static void servo_set_duty_cycle_left_grabber(int16_t value)
{
	uint16_t temp = ((double)ICR3 / 255.0) * value + 0.5;
	OCR3CH = temp >> 8;
	OCR3CL = temp & 0xFF;
}
//////////////////////////////////////////////////////////////////////////

void servo_set_umbrella_position(int8_t angle)//90 je otvoreno -86 zatvoreno 
{
	servo_set_duty_cycle_umbrella( 255-(236.0 - ((double)angle / 90.0) * 11.4));
}
void servo_set_door_position(int8_t angle)
{
	servo_set_duty_cycle_door( 255-(236.0 - ((double)angle / 90.0) * 11.4));
}
void servo_set_left_grabber_position(int8_t angle)//down 89 up -20
{
	servo_set_duty_cycle_left_grabber( 255-(236.0 - ((double)angle / 90.0) * 11.4));
}
void servo_set_right_grabber_position(int8_t angle)//UP 100 DOWN 250 or otherwise I DONT FUCKING KNOW
{
	OCR0A = angle;	
}
void servo_set_grabbers_up(void)
{
	servo_set_left_grabber_position(-10);
	servo_set_right_grabber_position(80);//200 is for the half step
}
void servo_set_grabbers_down(void)
{
	servo_set_left_grabber_position(89);
	servo_set_right_grabber_position(250);
}
/*

servo_set_left_grabber_position(89);
servo_set_right_grabber_position(250);

*/
void actuators_umbrella(void)
{
	servo_set_door_position(90);
	_delay_ms(2000);
	servo_set_umbrella_position(70);
	
}
void actuators_setup(void)
{
	servo_set_door_position(90);
	_delay_ms(1000);
	//servo_set_umbrella_position(-89);
	_delay_ms(1000);
	servo_set_door_position(30);
	_delay_ms(500);
	servo_set_grabbers_up();
}

