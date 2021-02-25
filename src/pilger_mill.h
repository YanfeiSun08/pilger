#ifndef PILGER_MILL_H
#define PILGER_MILL_H

#include "pilger.h"
#include "err.h"

//����
typedef struct Rougher
{
	double depthStart;              //��ʼ���
	double toolDiameter;			//����ֱ��
	double depthIncrease;			//�������
	double widthIncrease;			//��������
	double shapeOffset;				//��״����
	double depthOffset;				//��Ȳ���
	double feed;					//�ӹ��ٶ�
	double depthFeed;			    //�µ��ٶ�
	double distance;				//̧������
	double safetyHeight;			//��ȫ�߶�
}Rougher_info;

//���ӹ�
typedef struct Refined
{
	double angleStart;				//��ʼ�Ƕ�
	int processNum;			        //�ӹ�����
	double allowance;               //�ӹ���
	double toolDiameter;            //����ֱ��
	double angleIncrease;           //�Ƕ�����
	double shapeOffset;		        //��״����
	double depthOffset;             //��Ȳ���
	double feed;                    //�����ٶ�
	double safetyHeight;            //��ȫ�߶�
}Refined_info;

//����
typedef struct Chamfer
{
	int toolNum;					  //�ӹ�����
	double toolDiameter;              //����ֱ��
	double shapeOffset;		          //��״����
	double depthOffset;		          //��Ȳ���
	double feed;			          //�����ٶ�
	double safetyHeight;              //��ȫ�߶�
}Chamfer_info;



/*���ܣ�ֱ�߲岹
*������
*		@startPoint��Point�ṹ�壬�������
*		@endPoint��Point�ṹ�壬�յ�����
*		@num���岹�ܲ���
*		@step���岹����
*		@outPoint��ָ�룬Point�ṹ��,�岹�������
*		@����ֵ��1---��ʾ�岹��ɣ�0---��ʾ�岹δ���
*/
int lineInterpolation(Point const startPoint, Point const endPoint, int const num, int step, Point *outPoint);

Rougher_info init_rougher(double depthStart, double toolDiameter, double depthIncrease, double widthIncrease, double shapeOffset, double depthOffset, double feed, double depthFeed, double distance, double safetyHeight);

Refined_info init_refine(double angleStart, int processNum, double angleIncrease, double toolDiameter, double allowance, double shapeOffset, double depthOffset, double feed, double safetyHeight);

Chamfer_info init_chamfer(int toolNum, double toolDiameter, double shapeOffset, double depthOffset, double feed, double safetyHeight);

/*�������*/
int rougher_fun(Program_info *chamProgram, Rougher_info rougher, Pilger_info pilger);

/*���ӹ�����*/
int refined_fun(Program_info *chamProgram, Refined_info refine, Pilger_info pilger);

/*���ǳ���*/
int chamfer_fun(Program_info *chamProgram, Chamfer_info cham, Pilger_info pilger);


#endif
