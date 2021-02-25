#ifndef PILGER_H
#define PILGER_H

#include <stdio.h>
#include <math.h>

#define MAX_POINT_NUM	50

#ifndef PI
#define PI			(3.14159265358979323846)
#endif

#ifndef POINT
#define POINT
typedef struct Point
{
	double X;
	double Y;
}Point;

#endif
/*扎棍数据*/
typedef struct Pilger
{
	int pointNum;
	//半径
	double radius[MAX_POINT_NUM] ;
	//角度
	double angle[MAX_POINT_NUM] ;
	//倒角
	double bevel[MAX_POINT_NUM] ;
} Pilger_info;

typedef struct Program
{
	//int num;
	char mode[8];            //0位 0:G00 1:G01 1位:X 2位:Z 3位:C 4位:F
	double axis_1;			 //1轴坐标
	double axis_2;           //2轴坐标
	double axis_3;           //3轴坐标
	double feed;             //速度
}Program_info;

Program_info init_program(char mode[], double axis_1, double axis_2, double axis_3, double feed);

Pilger_info init_pilger(int pointNum, double radius[], double angle[], double bevel[]);

/*
查找最大圆弧半径
*/
double max_raduis(unsigned int size, double radius[]);


extern long errno;
#include "pilger_lather.h"
#include "pilger_mill.h"


#endif