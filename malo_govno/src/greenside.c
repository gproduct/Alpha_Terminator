#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "odometry.h"
#include "can.h"
#include "sides.h"
#include "uart.h"
#include "actuators.h"
#include "gpio.h"

//////////////////////////////////////////////////////////////////////////
//																		//
//					   DETEKCIJA/CALLBACK FUNKCIJE						//
//																		//
//////////////////////////////////////////////////////////////////////////




char grabbers_down_green(uint32_t start_time)
{
	servo_set_grabbers_down();
	return 0;
}
char grabbers_up_green(uint32_t start_time)
{
	servo_set_grabbers_up();
	return 0;
}
//////////////////////////////////////////////////////////////////////////
const struct goto_fields green_tactic_one_positions[TACTIC_ONE_POSITION_COUNT] =
{
	{{185,820},LOW_SPEED,BACKWARD,NULL},						//POSITION 0			MOVE FORWARD FOR THE BIG ROBOT TO GO
	{{185,1230},LOW_SPEED,FORWARD,NULL},						//POSITION 1			MOVE BACK INFRONT OF THE BLOCKS
	{{1100,1020},LOW_SPEED,FORWARD,grabbers_down_green},		//POSITION 2			PUSH THE BLOCKS TO THE GATE
	{{1020,880},LOW_SPEED,BACKWARD,NULL},						//POSITION 3			GET A LITTLE BACK
	{{280,530},LOW_SPEED,FORWARD,NULL},							//POSITION 4			GRAB 2 PACKS 290,450
	{{220,580},20,FORWARD,NULL},								//POSITION 5			ROTATING WITH 2 PACKS
	{{140,900},20,FORWARD,NULL},								//POSITION 6			MOVE FORWARD PACKS
	{{280,1750},60,BACKWARD,grabbers_up_green},					//POSITION 7			GOING INFRONT DOORS	
	{{85,1800},20,BACKWARD,NULL},								//POSITION 8			GET A GOOD ANGLE
	{{280,1800},50,FORWARD,NULL},								//POSITION 9			GOING INFRONT DOORS
	{{280,1925},20,FORWARD,NULL},								//POSITION 10			GOING INTO THE DOORS 120
	{{280,1660},20,BACKWARD,NULL},								//POSITION 11			GO BACK
	{{580,1660},20,FORWARD,NULL},								//POSITION 12			GO INFRONT OF DOOR NUM 2
	{{580,1960},20,FORWARD,NULL},								//POSITION 13			PUSH DOOR NUM 2
	{{580,1660},20,BACKWARD,NULL},								//POSITION 14			GO BACK
	{{85,1660},20,FORWARD,NULL}									//POSITION 15			GO AND HIDE 100
		//270,530
};
void greenside(void)
{
	struct odometry_position starting_position;
	uint8_t current_position = 0;
	uint8_t next_position = 0;
	uint8_t odometry_status;
	int8_t active_state = ROBOT_STATE_TACTIC_ONE;
	
	starting_position.x		= 180;
	starting_position.y		= 990;
	starting_position.angle = 90;
	
	odometry_set_position(&starting_position);

	while(1)
	{
		switch(active_state)
		{
			case ROBOT_STATE_TACTIC_ONE:
				for(current_position = next_position;current_position < TACTIC_ONE_POSITION_COUNT; current_position++)
				{
					odometry_status = odometry_move_to_position(&(green_tactic_one_positions[current_position].point), green_tactic_one_positions[current_position].speed,
					green_tactic_one_positions[current_position].direction,green_tactic_one_positions[current_position].callback);
		
					if(odometry_status == ODOMETRY_FAIL)
					{
						break;
					}
					else if(current_position == 1 || current_position == 3)
					{
						_delay_ms(1000);
			
					}
					else if(current_position == 6)
					{
						servo_set_left_grabber_position(20);
						_delay_ms(800);
						odometry_rotate(-40,LOW_SPEED,NULL);
						_delay_ms(500);
						servo_set_right_grabber_position(100);
						_delay_ms(800);
						odometry_move_straight(-200,LOW_SPEED,NULL);
						_delay_ms(500);
						odometry_set_angle(-90,LOW_SPEED,NULL);
					
					}
					else if(current_position == 10 || current_position == 11)
					{
						_delay_ms(1000);
					}
					else if(current_position == 8)
					{
						_delay_ms(3000);
					}
					/*
					else if(current_position == 8) actually 11
					{
						odometry_move_straight(-200,LOW_SPEED,NULL);
						_delay_ms(800);
						odometry_rotate(90,LOW_SPEED,NULL);
						_delay_ms(500);
						odometry_move_straight(300,LOW_SPEED,NULL);
						_delay_ms(800);
						odometry_rotate(-90,LOW_SPEED,NULL);
						_delay_ms(500);
						odometry_move_straight(190,20,NULL);
						_delay_ms(1000);
						odometry_move_straight(-200,20,NULL);
						_delay_ms(1000);
						odometry_rotate(-90,LOW_SPEED,NULL);
						_delay_ms(800);
						odometry_move_straight(500,LOW_SPEED,NULL);
						while(1);
					}*/
					else if(current_position == 10)
					{
						_delay_ms(1000);
					}
					else if(current_position == 11)
					{
						_delay_ms(2000);
					}
					else if(current_position == 12)
					{
						_delay_ms(1500);
					}
					else if(current_position == 15)
					{
						PORTG = 0x00;
						while(1);
					}
				}//end for
		}//end switch
	}//end while
}//end void
