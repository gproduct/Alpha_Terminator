#ifndef SYSTEM_H_
#define SYSTEM_H_

#define MAX_INPUTS	    20
#define USE_TIMER_HOOK  1


#define GPIOA_BASE 0x22
#define GPIOB_BASE 0x25
#define GPIOC_BASE 0x28
#define GPIOD_BASE 0x2B
#define GPIOE_BASE 0x2E
#define GPIOG_BASE 0x34
#define GPIOF_BASE 0x31

#define PURPLE					1
#define GREEN					0

#define ACTIVATE				1
#define DEACTIVE			 	0

#define TRUE					0
#define FALSE					1

#define JUMPER_PIN				40		//portf 0
#define SIDE_PIN				41		//portf 1

#define SENSOR_F_L_PIN			8		//portb 0	
#define SENSOR_F_R_PIN			10		//portb 2 
#define SENSOR_B_L_PIN			12		//portb 4
#define SENSOR_B_R_PIN			14		//portb 6


void timer_init(unsigned int freq);

unsigned char restartCheck;
unsigned char stateRobot;

int active_state;

void delay(double ms);
void wait_for_big_robot(double time_to_wait);

//int camera(void);
signed char sides_switch_check(void);

void system_init(void);

//Funkcije za proveru senzora, jumpera i prekidaca
uint8_t return_active_state(void);
signed char check_front_sensors(signed char sensor);
signed char check_back_sensors(signed char sensor);

void system_set_match_started(void);
uint8_t system_get_match_started(void);

#endif
