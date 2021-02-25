#include <stdio.h>
#include "pilger.h"

extern errno;

#define MAX_PROGRAM_NUM			25000      //程序点数

/*轧辊数据*/
/*加工点数*/
//int	pointNum = 11;
/*半径 半径输入 第一个是最大半径*/
//double radius[MAX_POINT_NUM] = { 20, 10, 10, 10.5, 11, 12, 13, 14, 16, 18, 20 };
/*角度*/
//double angle[MAX_POINT_NUM] = { 326, 5, 36, 72, 108, 144, 180, 216, 252, 288, 326 };
/*倒角*/
//double bevel[MAX_POINT_NUM] = { 20, 25, 25, 25, 25, 25, 25, 25, 20, 20, 20 };


/*轧辊数据*/
/*加工点数*/
int	pointNum = 15;
/*半径 半径输入 第一个是最大半径*/
double radius[MAX_POINT_NUM] = { 14.250, 14.25, 14.25, 14.4, 14.56, 14.78, 15.08, 15.47, 15.99, 16.86, 18.38, 20.1, 24.0, 25 ,14.25};
/*角度*/
double angle[MAX_POINT_NUM] = { 0, 15, 25, 70, 85, 101.0, 117.0, 133.0, 149.0, 167.0, 185.0, 203.0, 255.0, 290.0, 360.0 };
/*倒角*/
double bevel[MAX_POINT_NUM] = { 10, 10, 11, 12, 13, 14, 15, 20, 25, 26, 30, 30, 15, 15, 18.0 };




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


/*程序输出*/
void print_file_vericut(FILE *fp, int num, Program_info *chamProgram)
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
		fprintf(fp, ";\n");
	}
}

int main(/*int argc, char *argv[]*/)
{

	int num = 0;
	/*程序buff空间*/
	Program_info program[MAX_PROGRAM_NUM] = { 0 };
	/*轧辊数据初始化*/
	Pilger_info pilger = init_pilger(pointNum, radius, angle, bevel);
	perr();

#if     0



	/*开粗参数初始化*/
	Rougher_info rougher = init_rougher(0, 10, 0.3, 3.0, -1.0, -1, 2000, 200, 5, 20);
	perr();
	/*程序生成*/
	num = rougher_fun(program, rougher, pilger);
	perr();
	/*程序打印*/
	print_file(stdout, num, program);

	/*精加工参数初始化*/
	Refined_info refine = init_refine(0, 3, 1, 10.0, 1.0, 0, 2.0, 2000, 5);
	perr();
	/*程序生成*/
	num = refined_fun(program, refine, pilger);
	perr();
	/*程序打印*/
	//print_file(stdout, num, program);

	/*倒角参数初始化*/
	Chamfer_info cham = init_chamfer(20, 7., 0, 0., 2000, 5);
	perr();
	/*程序生成*/
	num = chamfer_fun(program, cham, pilger);
	perr();
	/*程序打印*/
	print_file(stdout, num, program);

#endif 
	FILE *fp = fopen("D:/数控仿真模型/激光切割/6000.PRG", "w");
	if (fp == NULL){
		printf("file open err!\n");
		getchar();
	}
	fprintf(fp, "M06 T02\nM03 S2000\nG43 H01\nG90 G54 F1000 G01\n");

	/*车床参数初始化*/
	Lather_info cham = init_lather(27, 10., 2, 4.0, 0, 0,2000,5);
	perr();
	/*程序生成*/
	num = lather_fun(program, cham, pilger);
	perr();
	/*程序打印*/
	print_file_vericut(fp, num, program);

	fclose(fp);
	getchar();
	return 0;
}
