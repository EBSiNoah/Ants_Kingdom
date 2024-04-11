#include <vector>
#include <cstdlib>
#include <ctime>
#include "cell_class.h"

Cell::Cell()
{
	
}

Cell::Cell(int property_value)
{
	srand(time(nullptr));
	if(property_value==0)//empty
	{
		life=0;
		health=0;
	}
	else if(property_value==1)//Queen
	{
		life=1800+rand()%1800;
		health=100+rand()%100;
	}
	else if(property_value==2)//male
	{
		life=180;
		health=10+rand()%10;
	}
	else if(property_value==3)//worker
	{
		life=360;
		health=25+rand()%25;
	}
	else if(property_value==4)//food
	{
		life=0;
		health=10+rand()%30;
	}
	property=property_value;
	hunger=0;
	rest=false;
	move=false;
}
