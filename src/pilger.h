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
/*��������*/
typedef struct Pilger
{
	int pointNum;
	//�뾶
	double radius[MAX_POINT_NUM] ;
	//�Ƕ�
	double angle[MAX_POINT_NUM] ;
	//����
	double bevel[MAX_POINT_NUM] ;
} Pilger_info;

typedef struct Program
{
	//int num;
	char mode[8];            //0λ 0:G00 1:G01 1λ:X 2λ:Z 3λ:C 4λ:F
	double axis_1;			 //1������
	double axis_2;           //2������
	double axis_3;           //3������
	double feed;             //�ٶ�
}Program_info;

Program_info init_program(char mode[], double axis_1, double axis_2, double axis_3, double feed);

Pilger_info init_pilger(int pointNum, double radius[], double angle[], double bevel[]);

/*
�������Բ���뾶
*/
double max_raduis(unsigned int size, double radius[]);


extern long errno;
#include "pilger_lather.h"
#include "pilger_mill.h"


#endif