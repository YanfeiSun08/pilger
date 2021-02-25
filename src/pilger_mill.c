#include "pilger_mill.h"



/*���ܣ�ֱ�߲岹
*������
*		@startPoint��Point�ṹ�壬�������
*		@endPoint��Point�ṹ�壬�յ�����
*		@delta������ϵͳ�ķֱ���-�岹����
*		@outPoint��ָ�룬Point�ṹ��,�岹�������
*		@����ֵ��1---��ʾ�岹��ɣ�0---��ʾ�岹δ���
*/
int lineInterpolation(Point const startPoint, Point const endPoint, int const num, int step, Point *outPoint)
{
	//����������
	double length = sqrt((endPoint.X - startPoint.X)*(endPoint.X - startPoint.X) + (endPoint.Y - startPoint.Y)*(endPoint.Y - startPoint.Y));
	//�岹��������
	double delta = (double)length / num;
	//�岹�������
	if (length > 0.0009)
	{
		outPoint->X = startPoint.X + step*delta*(endPoint.X - startPoint.X) / length;
		outPoint->Y = startPoint.Y + step*delta*(endPoint.Y - startPoint.Y) / length;
	}
	else
	{
		*outPoint = endPoint;
	}
	if (step == num && (outPoint->X != endPoint.X || outPoint->Y != endPoint.Y))
	{
		*outPoint = endPoint;
	}
	return 0;
}

Rougher_info init_rougher(double depthStart, double toolDiameter, double depthIncrease, double widthIncrease, double shapeOffset, double depthOffset, double feed, double depthFeed, double distance, double safetyHeight)
{
	Rougher_info rougher = { 0 };
	if (depthStart < 0)
	{
		errno = ERR_ROUGHER_DEPTH_START;
		return rougher;
	}

	if (toolDiameter <= 0)
	{
		errno = ERR_ROUGHER_TOOL_DIAME;
		return rougher;
	}

	if (depthIncrease <= 0)
	{
		errno = ERR_ROUGHER_DEPTH_INCR;
		return rougher;
	}

	if (widthIncrease <= 0)
	{
		errno = ERR_ROUGHER_WIDTH_INCR;
		return rougher;
	}

	if (feed <= 0)
	{
		errno = ERR_ROUGHER_FEED;
		return rougher;
	}
	if (depthFeed <= 0)
	{
		errno = ERR_ROUGHER_DEPTH_FEED;
		return rougher;
	}

	if (distance <= 0)
	{
		errno = ERR_ROUGHER_DISTANCE;
		return rougher;
	}

	if (safetyHeight <= 0)
	{
		errno = ERR_ROUGHER_SAF_HEIGHT;
		return rougher;
	}

	if (widthIncrease >= toolDiameter)
	{
		errno = ERR_ROUGHER_WIDTH_GT_TOOL;
		return rougher;
	}
	rougher.depthStart = depthStart;
	rougher.toolDiameter = toolDiameter;
	rougher.depthIncrease = depthIncrease;
	rougher.widthIncrease = widthIncrease;
	rougher.shapeOffset = shapeOffset;
	rougher.depthOffset = depthOffset;
	rougher.feed = feed;
	rougher.depthFeed = depthFeed;
	rougher.distance = distance;
	rougher.safetyHeight = safetyHeight;

	return rougher;
}

Refined_info init_refine(double angleStart, int processNum, double allowance, double toolDiameter, double angleIncrease, double shapeOffset, double depthOffset, double feed, double safetyHeight)
{
	Refined_info refine = { 0 };

	if (angleStart > 90 || angleStart < 0)
	{
		errno = ERR_REFINE_ANGLE_START;
		return refine;
	}

	if (processNum < 0)
	{
		errno = ERR_REFINE_PROC_NUM;
		return refine;
	}

	if (allowance < 0)
	{
		errno = ERR_REFINE_ALLOWANCE;
		return refine;
	}
	if (toolDiameter <= 0)
	{
		errno = ERR_REFINE_TOOL_DIAME;
		return refine;
	}

	if (angleIncrease <= 0)
	{
		errno = ERR_REFINE_ANGLE_INCR;
		return refine;
	}

	if (feed <= 0)
	{
		errno = ERR_REFINE_FEED;
		return refine;
	}

	if (safetyHeight <= 0)
	{
		errno = ERR_REFINE_SAF_HEIGHT;
		return refine;
	}
	refine.angleStart = angleStart;
	refine.processNum = processNum;
	refine.angleIncrease = angleIncrease;
	refine.toolDiameter = toolDiameter;
	refine.allowance = allowance;
	refine.shapeOffset = shapeOffset;
	refine.depthOffset = depthOffset;
	refine.feed = feed;
	refine.safetyHeight = safetyHeight;
	return refine;

}

Chamfer_info init_chamfer(int toolNum, double toolDiameter, double shapeOffset, double depthOffset, double feed, double safetyHeight)
{
	Chamfer_info chamfer = { 0 };

	if (toolNum <= 0)
	{
		errno = ERR_CHAMFER_TOOL_NUM;
		return chamfer;
	}
	if (toolDiameter <= 0)
	{
		errno = ERR_CHAMFER_TOOL_DIAME;
		return chamfer;
	}
	if (feed <= 0)
	{
		errno = ERR_CHAMFER_FEED;
		return chamfer;
	}
	if (safetyHeight <= 0)
	{
		errno = ERR_CHAMFER_SAF_HEIGHT;
		return chamfer;
	}

	chamfer.toolNum = toolNum;
	chamfer.toolDiameter = toolDiameter;
	chamfer.shapeOffset = shapeOffset;
	chamfer.depthOffset = depthOffset;
	chamfer.feed = feed;
	chamfer.safetyHeight = safetyHeight;

	return chamfer;
}

/*�������*/
int rougher_fun(Program_info *chamProgram, Rougher_info rougher, Pilger_info pilger)
{
	double x = 0;
	double y = 0;

	/*�������*/
	double depth = 0;
	/*�������*/
	double length = 0;
	int index = 0;
	double tempAngle = 0;
	int flag = 0;

	double inc_length = rougher.widthIncrease;
	double inc_depth = rougher.depthIncrease;
	double maxRadius = max_raduis(pilger.pointNum, pilger.radius);
	double maxDepth = sqrt(maxRadius*maxRadius - (rougher.toolDiameter*rougher.toolDiameter / 4));
	double maxLength = 0;
	int tempNum = 0;
	int num = 0;

	if (rougher.depthStart >maxDepth)
	{
		errno = ERR_ROUGHER_DEPTH_GT_MAX;
		return -1;
	}

	double Radius[MAX_POINT_NUM] = { 0 };
	//��״����
	for (int i = 0; i < pilger.pointNum; i++)
	{
		Radius[i] = pilger.radius[i] + rougher.shapeOffset;
		if (Radius[i] <= 0)
		{
			errno = ERR_ROUGHER_SHAPE_OFFSET;
			return -1;
		}
	}

	/*����ͷ*/
	chamProgram[num++] = init_program("01000", rougher.safetyHeight, 0, 0, 0);
	chamProgram[num++] = init_program("00100", 0, 0, 0, 0);
	chamProgram[num++] = init_program("10011", 0, 0, pilger.angle[pilger.pointNum - 1], rougher.feed);

	//��ȼ���
	double tempDepth[MAX_POINT_NUM] = { 0 };
	for (index = 0; index < pilger.pointNum; index++)
	{
		tempDepth[index] = sqrt(Radius[index] * Radius[index] - (rougher.toolDiameter*rougher.toolDiameter / 4));
	}
	for (depth = rougher.depthStart /* inc_depth*/; depth <= maxDepth; depth += inc_depth)
	{
		maxLength = sqrt(maxRadius*maxRadius - depth*depth);
		tempNum = (int)((maxLength - inc_length) / inc_length);
		chamProgram[num++] = init_program("11111", rougher.distance - depth + rougher.depthOffset, 0, pilger.angle[pilger.pointNum - 1], rougher.feed);
		for (index = 0; index < pilger.pointNum; index++)
		{
			x = 0;
			y = depth;
			if (depth > tempDepth[index])
				y = tempDepth[index];
			if (index == 0)
			{
				chamProgram[num++] = init_program("11111", -y + rougher.depthOffset, x, pilger.angle[index], rougher.depthFeed);
			}
			else
			{
				chamProgram[num++] = init_program("11111", -y + rougher.depthOffset, x, pilger.angle[index], rougher.feed);
			}
		}
		if (maxLength <= rougher.toolDiameter)
			break;

		flag = 0;
		for (length = inc_length*tempNum; length >= -0.1; length -= inc_length)
		{
			if (length < 0) length = 0;
			for (index = 0; index <pilger.pointNum; index++)
			{
				/*�����Ƕȼ���*/
				if (depth < tempDepth[index])
				{
					tempAngle = asin(depth / Radius[index]) / PI * 180;
					y = depth;
				}
				else
				{
					tempAngle = asin(tempDepth[index] / Radius[index]) / PI * 180;
					y = tempDepth[index];
				}
				x = Radius[index] * cos(tempAngle*PI / 180.0) - rougher.toolDiameter / 2.0 - length;

				if (x > (rougher.toolDiameter + inc_length*flag + flag*(rougher.toolDiameter - inc_length) / 4.0))
					x = rougher.toolDiameter + inc_length*flag + flag*(rougher.toolDiameter - inc_length) / 4.0;

				if (x < 0) x = 0;

				if (index == 0)
				{
					chamProgram[num++] = init_program("11111", -y + rougher.depthOffset, x, pilger.angle[index], rougher.depthFeed);
				}
				else
				{
					chamProgram[num++] = init_program("11111", -y + rougher.depthOffset, x, pilger.angle[index], rougher.feed);
				}
			}

			for (index = 0; index <pilger.pointNum; index++)
			{
				if (depth < tempDepth[index])
				{
					tempAngle = asin(depth / Radius[index]) / PI * 180;
					y = depth;
				}
				else
				{
					tempAngle = asin(tempDepth[index] / Radius[index]) / PI * 180;
					y = tempDepth[index];
				}
				x = Radius[index] * cos(tempAngle*PI / 180.0) - rougher.toolDiameter / 2.0 - length;
				if (x > (rougher.toolDiameter + inc_length*flag + flag*(rougher.toolDiameter - inc_length) / 4.0))
					x = rougher.toolDiameter + inc_length*flag + flag*(rougher.toolDiameter - inc_length) / 4.0;

				/*�����ж�*/
				if (x < 0)
				{
					x = 0;
				}
				if (x > 0.001) x = -x;
				if (index == 0)
				{
					chamProgram[num++] = init_program("11111", -y + rougher.depthOffset, x, pilger.angle[index], rougher.depthFeed);
				}
				else
				{
					chamProgram[num++] = init_program("11111", -y + rougher.depthOffset, x, pilger.angle[index], rougher.feed);
				}
			}
			flag++;
		}
		chamProgram[num++] = init_program("11001", rougher.distance - depth + rougher.depthOffset, 0, 0, rougher.feed);
	}
	chamProgram[num++] = init_program("11001", rougher.safetyHeight, 0, 0, rougher.feed);

	return num;
}

/*���ӹ�����*/
int refined_fun(Program_info *chamProgram, Refined_info refine, Pilger_info pilger)
{
	int index = 0;
	double tempAngle = 0;
	double tempRaduis = 0;
	double x = 0;
	double y = 0;
	int num = 0;


	double Radius[MAX_POINT_NUM] = { 0 };
	//��״����
	for (int i = 0; i < pilger.pointNum; i++)
	{
		Radius[i] = pilger.radius[i] + refine.shapeOffset;

		if (Radius[i] <= 0)
		{
			errno = ERR_REFINE_SHAPE_OFFSET;
			return -1;
		}
	}

	for (int i = refine.processNum - 1; i >= 0; i--)
	{
		/*����ͷ*/
		chamProgram[num++] = init_program("01000", refine.safetyHeight, 0, 0, 0);
		chamProgram[num++] = init_program("00100", 0, 0, 0, 0);
		chamProgram[num++] = init_program("10011", 0, 0, pilger.angle[pilger.pointNum - 1], refine.feed);

		if (i == refine.processNum - 1)
		{
			tempAngle = refine.angleStart;
		}
		else
		{
			tempAngle = 0;
		}
		for (; tempAngle <= 90; tempAngle += refine.angleIncrease)
		{
			for (index = 0; index < pilger.pointNum; index++)
			{
				tempRaduis = Radius[index] - refine.toolDiameter / 2.0;
				if (tempRaduis < 0) continue;
				x = tempRaduis * cos(tempAngle*PI / 180.0);
				y = tempRaduis * sin(tempAngle *PI / 180.0) + refine.toolDiameter / 2.0 - i*(refine.allowance / refine.processNum) - refine.depthOffset;
				chamProgram[num++] = init_program("11110", -y, x, pilger.angle[index], 0);
			}

			for (index = 0; index < pilger.pointNum; index++)
			{
				tempRaduis = Radius[index] - refine.toolDiameter / 2.0;
				if (tempRaduis < 0) continue;
				x = tempRaduis * cos(tempAngle*PI / 180.0);
				y = tempRaduis * sin(tempAngle *PI / 180.0) + refine.toolDiameter / 2.0 - i*(refine.allowance / refine.processNum) - refine.depthOffset;
				chamProgram[num++] = init_program("11110", -y, -x, pilger.angle[index], 0);
			}
		}

		chamProgram[num++] = init_program("11000", refine.safetyHeight, 0, 0, 0);
	}
	return num;
}

/*���ǳ���*/
int chamfer_fun(Program_info *chamProgram, Chamfer_info cham, Pilger_info pilger)
{
	int index = 0;
	Point start[50] = { 0 };
	Point end[50] = { 0 };
	Point out = { 0 };
	int num = 0;

	double Radius[MAX_POINT_NUM] = { 0 };
	//��״����
	for (int i = 0; i < pilger.pointNum; i++)
	{
		Radius[i] = pilger.radius[i] + cham.shapeOffset;
		if (Radius[i] <= 0)
		{
			errno = ERR_CHAMFER_SHAPE_OFFSET;
			return -1;
		}
	}

	/*����ͷ*/
	chamProgram[num++] = init_program("01000", cham.safetyHeight, 0, 0, 0);
	chamProgram[num++] = init_program("00100", 0, 0, 0, 0);
	chamProgram[num++] = init_program("10011", 0, 0, pilger.angle[pilger.pointNum - 1], cham.feed);

	for (index = 0; index < pilger.pointNum; index++)
	{
		start[index].X = 0;
		start[index].Y = Radius[index] / cos(pilger.bevel[index] * PI / 180.0);
		end[index].X = -Radius[index] * sin(pilger.bevel[index] * PI / 180.0);
		end[index].Y = Radius[index] * cos(pilger.bevel[index] * PI / 180.0);
	}

	for (int i = 0; i <= cham.toolNum; i++)
	{
		for (index = 0; index < pilger.pointNum; index++)
		{
			lineInterpolation(start[index], end[index], cham.toolNum, i, &out);
			chamProgram[num++] = init_program("11110", out.X + cham.depthOffset, out.Y - cham.toolDiameter / 2, pilger.angle[index], 0);
		}

		for (index = 0; index < pilger.pointNum; index++)
		{
			lineInterpolation(start[index], end[index], cham.toolNum, i, &out);
			chamProgram[num++] = init_program("11110", out.X + cham.depthOffset, -(out.Y - cham.toolDiameter / 2), pilger.angle[index], 0);
		}
	}
	chamProgram[num++] = init_program("11000", cham.safetyHeight, 0, 0, 0);

	return num;
}