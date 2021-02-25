#include "pilger_lather.h"


Lather_info init_lather(double depthMax, double toolDiameter, double depthIncrease, double angleIncrease, double shapeOffset, double depthOffset, double feed, double safetyHeight)
{
	Lather_info lather = { 0 };
	if (depthMax < 0)
	{
		errno = ERR_LATHER_DEPTH_MAX;
		return lather;
	}

	if (toolDiameter < 0)
	{
		errno = ERR_LATHER_TOOL_DIAME;
		return lather;
	}

	if (depthIncrease <= 0)
	{
		errno = ERR_LATHER_DEPTH_INCR;
		return lather;
	}

	if (angleIncrease <= 0)
	{
		errno = ERR_LATHER_ANGLE_INCR;
		return lather;
	}

	if (feed <= 0)
	{
		errno = ERR_LATHER_FEED;
		return lather;
	}

	if (safetyHeight <= 0)
	{
		errno = ERR_LATHER_SAF_HEIGHT;
		return lather;
	}

	lather.depthMax = depthMax;
	lather.toolDiameter = toolDiameter;
	lather.depthIncrease = depthIncrease;
	lather.angleIncrease = angleIncrease;
	lather.shapeOffset = shapeOffset;
	lather.depthOffset = depthOffset;
	lather.feed = feed;
	lather.safetyHeight = safetyHeight;

	return lather;
}


/*精加工程序*/
int lather_fun(Program_info *chamProgram, Lather_info lather, Pilger_info pilger)
{
	int index = 0;
	double tempAngle = 0;
	double tempRaduis = 0;
	double x = 0;
	double y = 0;
	int num = 0;
	double depth = 0;

	double maxRaduis = max_raduis(pilger.pointNum, pilger.radius);
	double Radius[MAX_POINT_NUM] = { 0 };
	//形状补偿
	for (int i = 0; i < pilger.pointNum; i++)
	{
		Radius[i] = pilger.radius[i] + lather.shapeOffset;

		if (Radius[i] <= 0)
		{
			errno = ERR_LATHER_SHAPE_OFFSET;
			return -1;
		}
	}

	/*程序头*/
	chamProgram[num++] = init_program("01000", lather.safetyHeight, 0, 0, 0);
	chamProgram[num++] = init_program("00100", 0, 0, 0, 0);
	chamProgram[num++] = init_program("10011", 0, 0, pilger.angle[pilger.pointNum - 1], lather.feed);


	for (depth = lather.depthMax - lather.depthIncrease; depth >= 0.0; depth -= lather.depthIncrease)
	{
		if (depth < 0) {
			depth = 0.0;
		}

		tempAngle = asin((depth + lather.depthOffset) / maxRaduis)*180.0/PI;
		printf("angle %.3f\n", tempAngle);

		for (; tempAngle <= 90; tempAngle += lather.angleIncrease)
		{
			for (index = 0; index < pilger.pointNum; index++)
			{
				tempRaduis = Radius[index] - lather.toolDiameter / 2.0;
				x = tempRaduis * cos(tempAngle*PI / 180.0);
				y = tempRaduis * sin(tempAngle *PI / 180.0) + lather.toolDiameter / 2.0 - depth - lather.depthOffset;

				chamProgram[num++] = init_program("11110", -y, x, pilger.angle[index], 0);
			}

			for (index = 0; index < pilger.pointNum; index++)
			{
				tempRaduis = Radius[index] - lather.toolDiameter / 2.0;
				x = tempRaduis * cos(tempAngle*PI / 180.0);
				y = tempRaduis * sin(tempAngle *PI / 180.0) + lather.toolDiameter / 2.0 - depth - lather.depthOffset;
				chamProgram[num++] = init_program("11110", -y, -x, pilger.angle[index], 0);
			}
		}
		if (depth == 0.0) {
			depth -= 1.0;
		}
	}
	chamProgram[num++] = init_program("11000", lather.safetyHeight, 0, 0, 0);

	return num;
}