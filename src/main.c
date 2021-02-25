#include <stdio.h>
#include "pilger.h"


/*

#define MAX_PROGRAM_NUM			10000      //程序点数

//加工点数
int	pointNum1 = 11;
//半径输入 第一个是最大半径
//半径
double radius1[MAX_POINT_NUM] = { 20, 10, 10, 10.5, 11, 12, 13, 14, 16, 18, 20 };
//角度
double angle1[MAX_POINT_NUM] = { 326 ,5, 36, 72, 108, 144, 180, 216, 252, 288, 326 };
//倒角
double bevel1[MAX_POINT_NUM] = { 20, 25, 25, 25, 25, 25, 25, 25, 20, 20, 20 };
*/

/*程序输出*/
/*
void print_file1(FILE *fp, int num, Program_info *chamProgram)
{
	for (int i = 0; i < num; i++)
	{
		fprintf(fp, "N%03d ", i);
		if (chamProgram[i].mode[0] == '1')
		{
			fprintf(fp, "G01 ");
		}
		else
		{
			fprintf(fp, "G00 ");
		}
		if (chamProgram[i].mode[1] == '1')
		{
			fprintf(fp, "X%.3f ", chamProgram[i].axis_1);
		}
		if (chamProgram[i].mode[2] == '1')
		{
			fprintf(fp, "Z%.3f ", chamProgram[i].axis_2);
		}
		if (chamProgram[i].mode[3] == '1')
		{
			fprintf(fp, "C%.3f ", chamProgram[i].axis_3);
		}
		if (chamProgram[i].mode[4] == '1')
		{
			fprintf(fp, "F%.0f", chamProgram[i].feed);
		}
		fprintf(fp, ";\n");
	}
}

*/

/*仿真程序输出*/
/*
void print_file_m1(FILE *fp, int num, Program_info *chamProgram)
{
	for (int i = 0; i < num; i++)
	{
		fprintf(fp, "N%03d ", i);
		if (chamProgram[i].mode[0] == '1')
		{
			fprintf(fp, "G01 ");
		}
		else
		{
			fprintf(fp, "G00 ");
		}
		if (chamProgram[i].mode[1] == '1')
		{
			fprintf(fp, "Z%.3f ", chamProgram[i].axis_1);
		}
		if (chamProgram[i].mode[2] == '1')
		{
			fprintf(fp, "X%.3f ", chamProgram[i].axis_2);
		}
		if (chamProgram[i].mode[3] == '1')
		{
			fprintf(fp, "A%.3f ", chamProgram[i].axis_3);
		}
		if (chamProgram[i].mode[4] == '1')
		{
			fprintf(fp, "F%.0f", chamProgram[i].feed);
		}
		fprintf(fp, "\n");
	}
}

*/


/*
int main1(int argc, char *argv[])
{
	int num = 0;
	FILE *fp = fopen("E:/数控仿真模型/激光切割/7000.prg", "w");
	if (fp == NULL)
	{
		printf("open file err!\n");
		getchar();
	}

	Program_info program[MAX_PROGRAM_NUM] = { 0 };
	Pilger_info pilger = init_pilger(pointNum1, radius1, angle1, bevel1);
	Chamfer_info cham = init_chamfer(10, 10, 0.5, 0, 2000, 5);
	Refined_info refine = init_refine(2, 2, 10, 1, 0, -0.5, 2000, 5);
	Rougher_info rougher = init_rougher(10, 0.5, 7, 0, 0, 2000, 1000, 2, 5);


	num = rougher_fun(program, rougher, pilger);

	fprintf(fp, "M06 T02\nM03 S2000 \nG43 H01\nG90 G54 F1000 G01\n");

	print_file_m1(fp, num, program);

	num = refined_fun(program, refine, pilger);
	fprintf(fp, "M06 T01\nM03 S2000 \nG43 H01\nG90 G54 F1000 G01\n");
	print_file_m1(fp, num, program);

	num = chamfer_fun(program, cham, pilger);
	fprintf(fp, "M06 T03\nM03 S2000 \nG43 H01\nG90 G54 F1000 G01\n");
	print_file_m1(fp, num, program);
	//print_file(stdout, num, program);

	refine = init_refine(1, 1, 10, 4, 1, 0, 2000, 5);


	num = refined_fun(program, refine, pilger);



	print_file(stdout, num, program);
	//num = rougher_fun(program, rougher, pilger);

	//print_file(stdout, num, program);

	//Program_info d;
	//printf("%d\n", sizeof(Program_info));

	//d = init_program("01110", 10, 2., 3., 0);


	getchar();
	fclose(fp);
	return 0;
}
*/