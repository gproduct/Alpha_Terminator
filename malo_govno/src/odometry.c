#include <stdint.h>
#include "odometry.h"
#include "system.h"
#include "can.h"
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>
#include <avr/io.h>

static uint8_t current_speed = 0;

volatile struct odometry_position position=
{
	.x     = 0,
	.y     = 0,
	.angle = 0,
	.state = IDLE
};

void odometry_set_speed(uint8_t speed)
{
	if(speed == current_speed)
	return;

	uint8_t buffer[8];
	buffer[0] = 'V';
	buffer[1] = speed;
	while(CAN_Write(buffer, DRIVER_TX_IDENTIFICATOR))
	_delay_ms(50);

	current_speed = speed;
}

static void odometry_query_position(void)
{
	uint8_t buffer[8];
	buffer[0] = 'P';
	while(CAN_Write(buffer, DRIVER_TX_IDENTIFICATOR))
		_delay_ms(50);
	CAN_Read(buffer, DRIVER_RX_IDENTIFICATOR);
	position.state = buffer[0];
	position.x	   = (buffer[1] << 8) | buffer[2];
	position.y	   = (buffer[3] << 8) | buffer[4];
	position.angle = (buffer[5] << 8) | buffer[6];
}

static uint8_t odometry_wait_until_done(uint8_t (*callback)(uint32_t start_time))
{
	uint32_t time = system_get_system_time();
	do
	{
		odometry_query_position();
		if(callback != NULL)
		{
			if(callback(time) == 1)
				return ODOMETRY_FAIL;
		}
	}while(position.state == MOVING || position.state == ROTATING);
	
	return ODOMETRY_SUCCESS;
}

void stop(int8_t type)
{
	uint8_t buffer[8];

	do
	{
		buffer[0] = type;

		while(CAN_Write(buffer, DRIVER_TX_IDENTIFICATOR))
			_delay_ms(50);

		odometry_query_position();
	}while(position.state == MOVING || position.state == ROTATING);
}

uint8_t odometry_move_straight(int16_t distance, uint8_t speed, uint8_t (*callback)(uint32_t start_time))
{
	uint8_t buffer[8];
	odometry_set_speed(speed);
	distance *= -1;
	buffer[0] = 'D';
	buffer[1] = distance >> 8;
	buffer[2] = distance & 0xFF;
	
	while(CAN_Write(buffer, DRIVER_TX_IDENTIFICATOR))
		_delay_ms(50);
		
	return odometry_wait_until_done(callback);
}

uint8_t odometry_move_to_position(struct odometry_position* position, uint8_t speed, int8_t direction, uint8_t (*callback)(uint32_t start_time))
{
	uint8_t buffer[8];

	odometry_set_speed(speed);

	buffer[0] = 'G';
	buffer[1] = position->x >> 8;
	buffer[2] = position->x & 0xFF;
	buffer[3] = position->y >> 8;
	buffer[4] = position->y & 0xFF;
	buffer[5] = 0;
	buffer[6] = direction * -1;
	while(CAN_Write(buffer, DRIVER_TX_IDENTIFICATOR))
		_delay_ms(50);
	
	return 0;
	//return odometry_wait_until_done(callback);
}

void odometry_set_position(struct odometry_position* new_position)
{
	uint8_t buffer[8];

	buffer[0] = 'I';
	buffer[1] = new_position->x >> 8;
	buffer[2] = new_position->x & 0xFF;
	buffer[3] = new_position->y >> 8;
	buffer[4] = new_position->y & 0xFF;
	
	int8_t temp = new_position->angle * -1;
	buffer[5] = temp >> 8;
	buffer[6] = temp & 0xFF;

	position.x	   = new_position->x;
	position.y	   = new_position->y;
	position.angle = -1 * new_position->angle;

	while(CAN_Write(buffer, DRIVER_TX_IDENTIFICATOR))
		_delay_ms(50);
}

uint8_t odometry_rotate(int16_t angle,uint8_t speed, uint8_t (*callback)(uint32_t start_time))
{
	uint8_t buffer[8];
	odometry_set_speed(speed);

	angle *= -1;
	buffer[0] = 'T';
	buffer[1] = angle >> 8;
	buffer[2] = angle & 0xFF;

	while(CAN_Write(buffer, DRIVER_TX_IDENTIFICATOR))
		_delay_ms(50);

	return odometry_wait_until_done(callback);

}

uint8_t odometry_set_angle(int16_t angle, uint8_t speed, uint8_t (*callback)(uint32_t start_time))
{
	uint8_t buffer[8];
	odometry_set_speed(speed);

	angle *= -1;
	buffer[0] = 'A';
	buffer[1] = angle >> 8;
	buffer[2] = angle & 0xFF;
	while(CAN_Write(buffer, DRIVER_TX_IDENTIFICATOR))
		_delay_ms(50);

	return odometry_wait_until_done(callback);
}

uint8_t getState(void)
{
	return position.state;
}

int16_t odometry_get_x(void)
{
	return position.x;
}

int16_t odometry_get_y(void)
{
	return position.y;
}

int16_t odometry_get_angle(void)
{
	return position.angle;
}
