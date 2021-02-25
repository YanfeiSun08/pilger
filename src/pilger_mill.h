#ifndef PILGER_MILL_H
#define PILGER_MILL_H

#include "pilger.h"
#include "err.h"

//开粗
typedef struct Rougher
{
	double depthStart;              //起始深度
	double toolDiameter;			//刀具直径
	double depthIncrease;			//深度增量
	double widthIncrease;			//横向增量
	double shapeOffset;				//形状补偿
	double depthOffset;				//深度补偿
	double feed;					//加工速度
	double depthFeed;			    //下刀速度
	double distance;				//抬刀距离
	double safetyHeight;			//安全高度
}Rougher_info;

//精加工
typedef struct Refined
{
	double angleStart;				//起始角度
	int processNum;			        //加工次数
	double allowance;               //加工量
	double toolDiameter;            //刀具直径
	double angleIncrease;           //角度增量
	double shapeOffset;		        //形状补偿
	double depthOffset;             //深度补偿
	double feed;                    //进给速度
	double safetyHeight;            //安全高度
}Refined_info;

//倒角
typedef struct Chamfer
{
	int toolNum;					  //加工刀数
	double toolDiameter;              //刀具直径
	double shapeOffset;		          //形状补偿
	double depthOffset;		          //深度补偿
	double feed;			          //进给速度
	double safetyHeight;              //安全高度
}Chamfer_info;



/*功能：直线插补
*参数：
*		@startPoint：Point结构体，起点坐标
*		@endPoint：Point结构体，终点坐标
*		@num：插补总步数
*		@step：插补步数
*		@outPoint：指针，Point结构体,插补的坐标点
*		@返回值：1---表示插补完成，0---表示插补未完成
*/
int lineInterpolation(Point const startPoint, Point const endPoint, int const num, int step, Point *outPoint);

Rougher_info init_rougher(double depthStart, double toolDiameter, double depthIncrease, double widthIncrease, double shapeOffset, double depthOffset, double feed, double depthFeed, double distance, double safetyHeight);

Refined_info init_refine(double angleStart, int processNum, double angleIncrease, double toolDiameter, double allowance, double shapeOffset, double depthOffset, double feed, double safetyHeight);

Chamfer_info init_chamfer(int toolNum, double toolDiameter, double shapeOffset, double depthOffset, double feed, double safetyHeight);

/*深度增量*/
int rougher_fun(Program_info *chamProgram, Rougher_info rougher, Pilger_info pilger);

/*精加工程序*/
int refined_fun(Program_info *chamProgram, Refined_info refine, Pilger_info pilger);

/*倒角程序*/
int chamfer_fun(Program_info *chamProgram, Chamfer_info cham, Pilger_info pilger);


#endif
