#include <stdint.h>
#include "system.h"
#include "can.h"
#include "gpio.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "actuators.h"
#include "list_generic.h"
#include "odometry.h"

static volatile unsigned long sys_time;
static uint8_t match_started;
static void (*timer_callback)(void) = NULL;
//static int combination[2];

unsigned int received = 0;

void timer_register_callback(void (*callback)(void))
{
    timer_callback = callback;
}
/*
static int combination_check()
{
	PORTG = 0x00;
	if(combination[0] == 1 && combination[1] == 0 && combination[2] == 0)//first combination
	{
		PORTG = 0x01;
		active_state = ROBOT_STATE_TACTIC_ONE;
		return 1;
	}
	else if(combination[0] == 0 && combination[1] == 1 && combination[2] == 0)//second combination
	{
		PORTG = 0x02;
		active_state = ROBOT_STATE_TACTIC_TWO;
		return 1;
	}
	else if(combination[0] == 0 && combination[1] == 0 && combination[2] == 1)//third combination
	{
		PORTG = 0x04;
		active_state = ROBOT_STATE_TACTIC_THREE;
		return 1;
	}
	else if(combination[0] == 1 && combination[1] == 1 && combination[2] == 0)//fourth combination
	{
		PORTG = 0x03;
		active_state = ROBOT_STATE_TACTIC_FOUR;
		return 1;
	}
	else if(combination[0] == 0 && combination[1] == 1 && combination[2] == 1)//five combination
	{
		PORTG = 0x06;
		active_state = ROBOT_STATE_TACTIC_FIVE;
		return 1;
	}
	else if(combination[0] == 0 && combination[1] == 0 && combination[2] == 0)//error combination
	{
		PORTG = 0x00;
		return 0;
	}
	return 0;
}

int camera(void)
{
	int i;
	for(i=0;i<10;i++)
	{
		combination[0] = gpio_read_pin(CAMERA_0_PIN);
		combination[1] = gpio_read_pin(CAMERA_1_PIN);
		combination[2] = gpio_read_pin(CAMERA_2_PIN);
		
		_delay_ms(100);
	}
	if(combination_check())
	{
		return 1;
	}
	return 0;
}*/
void timer_init(unsigned int freq)
{
    TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS10);
	OCR1A = (double)F_CPU / (double)freq + 0.5;
	TIMSK1 = 1 << OCIE1A;

	SREG |= 0x80;
}
ISR(TIMER1_COMPA_vect)
{
    if(timer_callback != NULL)
        timer_callback();
	if(sys_time >= 90000)
		actuators_umbrella();
	sys_time++;
}
void delay(double ms)
{
	double current_time;
	current_time = sys_time;
	while(!(sys_time - current_time) >= ms);
}
void wait_for_big_robot(double time_to_wait)
{
	while(sys_time < time_to_wait);
}
signed char sides_switch_check(void)
{
	if(gpio_read_pin(SIDE_PIN) == 1)
	{
		return 1;
	}
	
	return 0;
}

void system_reset_system_time(void)
{
	sys_time = 0;
}
void system_set_match_started(void)
{
	match_started = 1;
}
uint32_t system_get_system_time(void)
{
	return sys_time;
}
uint8_t system_get_match_started(void)
{
	return match_started;
}
uint8_t return_active_state(void)
{
	return active_state;
}
void delay_ms(uint32_t ms)
{
	uint32_t current;
	current = system_get_system_time();
	while((sys_time - current ) < ms);
}
void system_init(void)
{	

	timer_register_callback(gpio_debouncer);
	_delay_ms(100);
	
	gpio_register_pin(JUMPER_PIN,GPIO_DIRECTION_INPUT,TRUE);							//jumper
	gpio_register_pin(SIDE_PIN,GPIO_DIRECTION_INPUT,TRUE);								//prekidac za stranu

	gpio_register_pin(SENSOR_F_L_PIN,GPIO_DIRECTION_INPUT,TRUE);						//sensor front left
	gpio_register_pin(SENSOR_F_R_PIN,GPIO_DIRECTION_INPUT,TRUE);						//sensor front right
	gpio_register_pin(SENSOR_B_L_PIN,GPIO_DIRECTION_INPUT,TRUE);						//sensor back left
	gpio_register_pin(SENSOR_B_R_PIN,GPIO_DIRECTION_INPUT,TRUE);						//sensor back right
	
	
	DDRG = 0xff;
	PORTG = 0x00;
	servo_init(50);
	timer_init(1000);
	CAN_Init(1);

	actuators_setup();
	
	while(!(gpio_read_pin(JUMPER_PIN)));
		_delay_ms(10);
	PORTG = 0xff;
	system_reset_system_time();
	system_set_match_started();
}
signed char check_front_sensors(signed char sensor)
{
	if(sensor == FRONT_ALL)
	{
		if(!(gpio_read_pin(SENSOR_F_L_PIN)) || !(gpio_read_pin(SENSOR_F_R_PIN)))
		{
			return DETECTED;
		}
	}
	
	return NOT_DETECTED;
}
signed char check_back_sensors(signed char sensor)
{
	if(sensor == BACK_ALL)
	{
		if(!(gpio_read_pin(SENSOR_B_L_PIN)) || !(gpio_read_pin(SENSOR_B_R_PIN)))
		{
			return DETECTED;
		}
	}
	
	return NOT_DETECTED;
}
/*
signed char checkFrontSensors(signed char sensor)
{
	if(sensor == FRONT_LEFT_SIDE)
	{
		if(gpio_read_pin(SENSOR_F_L_PIN) == TRUE)
		{
			return DETECTED;
		}
	}
	else if(sensor == FRONT_RIGHT_SIDE)
	{
		if(gpio_read_pin(SENSOR_F_R_PIN) == TRUE)
		{
			return DETECTED;
		}
	}
	else if(sensor == FRONT_ALL)
	{
		if(gpio_read_pin(SENSOR_F_L_PIN) == TRUE || gpio_read_pin(SENSOR_F_R_PIN) == TRUE)
		{
			return DETECTED;
		}
	}
	return NOT_DETECTED;
}
signed char checkRearSensors(signed char sensor)
{
	if(sensor == BACK_LEFT_SIDE)
	{
		if(gpio_read_pin(SENSOR_B_L_PIN) == TRUE)
		{
			return DETECTED;
		}
	}
	else if(sensor == BACK_RIGHT_SIDE)
	{
		if(gpio_read_pin(SENSOR_B_R_PIN) == TRUE)
		{
			return DETECTED;
		}
	}
	else if(sensor == BACK_ALL)
	{
		if(gpio_read_pin(SENSOR_B_L_PIN) == TRUE || gpio_read_pin(SENSOR_B_R_PIN) == TRUE)
		{
			return DETECTED;
		}
	}
	return NOT_DETECTED;
}*/