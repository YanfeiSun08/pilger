#ifndef PILGER_LATHER_H
#define PILGER_LATHER_H

#include "pilger.h"
#include "err.h"

/* 车床加工 */
typedef struct Lather
{
	double depthMax;                //最大深度
	double toolDiameter;			//刀具直径
	double depthIncrease;			//深度增量
	double angleIncrease;           //角度增量
	double shapeOffset;				//形状补偿
	double depthOffset;				//深度补偿
	double feed;					//加工速度
	double safetyHeight;			//安全高度
}Lather_info;


Lather_info init_lather(double depthMax, double toolDiameter, double depthIncrease, double angleIncrease, double shapeOffset, double depthOffset, double feed, double safetyHeight);


#endif
