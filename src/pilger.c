#include "pilger.h"
#include "err.h"

extern long errno;

Program_info init_program(char mode[], double axis_1, double axis_2, double axis_3, double feed)
{
	Program_info program = { 0 };
	//program.num = 0;
	sprintf(program.mode, "%s", mode);
	program.axis_1 = axis_1;
	program.axis_2 = axis_2;
	program.axis_3 = axis_3;
	program.feed = feed;
	return program;
}

Pilger_info init_pilger(int pointNum, double radius[], double angle[], double bevel[])
{
	Pilger_info pilger = { 0 };
	pilger.pointNum = pointNum;
	for (int i = 0; i < pointNum; i++)
	{
		if (radius[i] <= 0)
		{
			errno = ERR_PILGER_RADIUS;
			Pilger_info temp = { 0 };
			return temp;
		}
		pilger.radius[i] = radius[i];
		pilger.angle[i] = angle[i];
		pilger.bevel[i] = bevel[i];
	}

	return pilger;
}


/*
²éÕÒ×î´óÔ²»¡°ë¾¶
*/
double max_raduis(unsigned int size, double radius[])
{
	double d_max_raduis = 0;
	for (unsigned int index = 0; index < size; index++)
	{
		if (radius[index] > d_max_raduis) d_max_raduis = radius[index];
	}
	return d_max_raduis;
}
