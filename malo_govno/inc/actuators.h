#ifndef ACTUATORS_H_
#define ACTUATORS_H_

#define DOWN				0
#define UP					1

#define FRONT_LEFT_SIDE				1
#define FRONT_RIGHT_SIDE			2
#define FRONT_ALL					3

#define BACK_LEFT_SIDE				-1
#define BACK_RIGHT_SIDE				-2
#define BACK_ALL					-3

#define DETECTED		1
#define NOT_DETECTED	0

void servo_init(unsigned int f_pwm);
void servo_set_umbrella_position(int8_t angle);
void servo_set_door_position(int8_t angle);
void actuators_umbrella(void);
void actuators_setup(void);
void servo_set_left_grabber_position(int8_t angle);
void servo_set_right_grabber_position(int8_t angle);
void servo_position(unsigned char duty_cycle);

void servo_set_grabbers_up(void);
void servo_set_grabbers_down(void);

#endif
