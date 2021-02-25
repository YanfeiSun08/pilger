#ifndef PILGER_LATHER_H
#define PILGER_LATHER_H

#include "pilger.h"
#include "err.h"

/* �����ӹ� */
typedef struct Lather
{
	double depthMax;                //������
	double toolDiameter;			//����ֱ��
	double depthIncrease;			//�������
	double angleIncrease;           //�Ƕ�����
	double shapeOffset;				//��״����
	double depthOffset;				//��Ȳ���
	double feed;					//�ӹ��ٶ�
	double safetyHeight;			//��ȫ�߶�
}Lather_info;


Lather_info init_lather(double depthMax, double toolDiameter, double depthIncrease, double angleIncrease, double shapeOffset, double depthOffset, double feed, double safetyHeight);


#endif
