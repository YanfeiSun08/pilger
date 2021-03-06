#include <stdio.h>

/* 声明出错信息 */
char* errmsg[] = {
	/* 0 */ "No error",
	/* 1 */ "轧辊开粗时，起始深度小于零",
	/* 2 */ "轧辊开粗时，刀具直径小于等于零",
	/* 3 */ "轧辊开粗时，深度增量小于等于零",
	/* 4 */ "轧辊开粗时，横向增量小于等于零",
	/* 5 */ "轧辊开粗时，加工速度小于等于零",
	/* 6 */ "轧辊开粗时，下刀速度小于等于零",
	/* 7 */ "轧辊开粗时，抬刀距离小于等于零",
	/* 8 */ "轧辊开粗时，安全高度小于等于零",
	/* 9 */ "轧辊精加工时，加工次数小于等于零",
	/* 10 */ "轧辊精加工时，加工量小于零",
	/* 11 */ "轧辊精加工时，刀具直径小于等于零",
	/* 12 */ "轧辊精加工时，角度增量小于等于零",
	/* 13 */ "轧辊精加工时，进给速度小于等于零",
	/* 14 */ "轧辊精加工时，安全高度小于等于零",
	/* 15 */ "轧辊倒角加工时，加工次数小于等于零",
	/* 16 */ "轧辊倒角加工时，刀具直径小于等于零",
	/* 17 */ "轧辊倒角加工时，进给速度小于等于零",
	/* 18 */ "轧辊倒角加工时，安全高度小于等于零",
	/* 19 */ "轧辊加工时，轧辊半径小于等于零",
	/* 20 */ "轧辊开粗时，形状补偿量大于轧辊半径",
	/* 21 */ "轧辊精加工时，形状补偿量大于轧辊半径",
	/* 22 */ "轧辊倒角加工时，形状补偿量大于轧辊半径",
	/* 23 */ "轧辊开粗时，横向增量大于刀具直径",
	/* 24 */ "轧辊开粗时，起始深度大于轧辊开粗最大深度",
	/* 25 */ "轧辊精加工时，起始角度不在0~90度范围",




};

/* 声明错误代码全局变量 */
long errno = 0;

/* 打印出错信息函数 */
void perr()
{
	if (errno > 0)
	{
		printf("Error: %s\n", errmsg[errno]);
		getchar();
		exit();
	}
}
