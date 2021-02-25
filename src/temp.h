#include <stdio.h>
#include "pilger.h"

extern long errno;


#define MAX_PROGRAM_NUM			20000      //程序点数

//加工点数
int	pointNum = 15;
//半径输入 第一个是最大半径
//半径
//double radius[MAX_POINT_NUM] = { 20, 10, 10, 10.5, 11, 12, 13, 14, 16, 18, 20 };
//角度
//double angle[MAX_POINT_NUM] = { 326, 5, 36, 72, 108, 144, 180, 216, 252, 288, 326 };
//倒角
double bevel[MAX_POINT_NUM] = { 20, 25, 25, 25, 25, 25, 25, 25, 20, 20, 20 };

//半径
double radius[MAX_POINT_NUM] = { 10.25, 10.25, 10.45, 10.6, 10.83, 11.16, 11.6, 12.2, 13.05, 14.08, 16, 18, 18, 10.25, 10.25 };
//角度
double angle[MAX_POINT_NUM] = { 0, 93, 108, 130, 152, 174, 196, 218, 240, 262, 284, 327, 338, 350, 360 };

/*程序输出*/
void print_file(FILE *fp, int num, Program_info *chamProgram)
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



int main(/*int argc, char *argv[]*/)
{
	int num = 0;

	Program_info program[MAX_PROGRAM_NUM] = { 0 };
	Pilger_info pilger = init_pilger(pointNum, radius, angle, bevel);
	if (errno > 0)
	{
		perr(NULL);
		getchar();
		return 0;
	}

	//开粗
	Rougher_info rougher = init_rougher(0, 12, 0.3, 6, 0, 0, 2000, 1000, 2, 5);
	num = rougher_fun(program, rougher, pilger);
	if (errno > 0)
	{
		perr(NULL);
		getchar();
		return 0;
	}
	print_file(stdout, num, program);


	//Rougher_info rougher = init_rougher(10, 0.5, 7, 0, 0, 2000, 1000, 2, 5);

	//精加工
	Refined_info refine = init_refine(2, 2, 10, 1, 0, -0.5, 2000, 5);
	num = refined_fun(program, refine, pilger);
	if (errno > 0)
	{
		perr(NULL);
		getchar();
		return 0;
	}
	print_file(stdout, num, program);

	//倒角
	Chamfer_info cham = init_chamfer(10, 10., -20, 0., 2000, 5);
	num = chamfer_fun(program, cham, pilger);
	if (errno > 0)
	{
		perr(NULL);
		getchar();
		return 0;
	}
	print_file(stdout, num, program);

	getchar();
	return 0;
}