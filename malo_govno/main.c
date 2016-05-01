#include "gpio.h"
#include "system.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "odometry.h"
#include "sides.h"
#include "actuators.h"

int set = 1;

int main()
{

	system_init();
	_delay_ms(100);
	
	while(set)
	{
		if(sides_switch_check() == 0)
		{
			set = 2;
			greenside();	
		}
		else
		{
			set = 3;
			purpleside();	
		}
	}
	while(1)
	{
		if(set == 2)
		{
			greenside();
		}
		else if(set == 3)
		{
			purpleside();
		}
	}
}