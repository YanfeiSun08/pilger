#ifndef ERR_H
#define ERR_H

/* ����������� */
#define ERR_NO_ERROR                   0                        /* No error */

#define ERR_ROUGHER_DEPTH_START        1                        /*��������ʱ����ʼ���С����*/
#define ERR_ROUGHER_TOOL_DIAME         2                        /*��������ʱ������ֱ��С�ڵ�����*/
#define ERR_ROUGHER_DEPTH_INCR         3                        /*��������ʱ���������С�ڵ�����*/
#define ERR_ROUGHER_WIDTH_INCR         4                        /*��������ʱ����������С�ڵ�����*/
#define ERR_ROUGHER_FEED               5                        /*��������ʱ���ӹ��ٶ�С�ڵ�����*/
#define ERR_ROUGHER_DEPTH_FEED         6                        /*��������ʱ���µ��ٶ�С�ڵ�����*/
#define ERR_ROUGHER_DISTANCE           7                        /*��������ʱ��̧������С�ڵ�����*/
#define ERR_ROUGHER_SAF_HEIGHT         8                        /*��������ʱ����ȫ�߶�С�ڵ�����*/

#define ERR_REFINE_PROC_NUM            9                        /*�������ӹ�ʱ���ӹ�����С�ڵ�����*/
#define ERR_REFINE_ALLOWANCE           10                        /*�������ӹ�ʱ���ӹ���С����*/
#define ERR_REFINE_TOOL_DIAME          11                        /*�������ӹ�ʱ������ֱ��С�ڵ�����*/
#define ERR_REFINE_ANGLE_INCR          12                        /*�������ӹ�ʱ���Ƕ�����С�ڵ�����*/
#define ERR_REFINE_FEED                13                        /*�������ӹ�ʱ�������ٶ�С�ڵ�����*/
#define ERR_REFINE_SAF_HEIGHT          14                        /*�������ӹ�ʱ����ȫ�߶�С�ڵ�����*/

#define ERR_CHAMFER_TOOL_NUM           15                        /*�������Ǽӹ�ʱ���ӹ�����С�ڵ�����*/
#define ERR_CHAMFER_TOOL_DIAME         16                        /*�������Ǽӹ�ʱ������ֱ��С�ڵ�����*/
#define ERR_CHAMFER_FEED               17                        /*�������Ǽӹ�ʱ�������ٶ�С�ڵ�����*/
#define ERR_CHAMFER_SAF_HEIGHT         18                        /*�������Ǽӹ�ʱ����ȫ�߶�С�ڵ�����*/

#define ERR_PILGER_RADIUS              19                        /*�����ӹ�ʱ������Բ���뾶С�ڵ�����*/
#define ERR_ROUGHER_SHAPE_OFFSET	   20                        /*��������ʱ����״��������������Բ���뾶*/
#define ERR_REFINE_SHAPE_OFFSET        21                        /*�������ӹ�ʱ����״��������������Բ���뾶*/
#define ERR_CHAMFER_SHAPE_OFFSET       22                        /*�������Ǽӹ�ʱ����״��������������Բ���뾶*/

#define ERR_ROUGHER_WIDTH_GT_TOOL      23                        /*��������ʱ�������������ڵ���ֱ��*/
#define ERR_ROUGHER_DEPTH_GT_MAX       24                        /*��������ʱ����ʼ��ȴ�����������������*/
#define ERR_REFINE_ANGLE_START         25                        /*�������ӹ�ʱ����ʼ�ǶȲ���0~90�ȷ�Χ*/


/*  ��������������� */
#define ERR_LATHER_DEPTH_MAX          26                        /*��������ʱ��������С����*/
#define ERR_LATHER_TOOL_DIAME         27                        /*��������ʱ������ֱ��С�ڵ�����*/
#define ERR_LATHER_DEPTH_INCR         28                        /*��������ʱ���������С�ڵ�����*/
#define ERR_LATHER_ANGLE_INCR         29                        /*��������ʱ���Ƕ�����С�ڵ�����*/
#define ERR_LATHER_FEED               30                        /*��������ʱ���ӹ��ٶ�С�ڵ�����*/
#define ERR_LATHER_SAF_HEIGHT         31                        /*��������ʱ����ȫ�߶�С�ڵ�����*/
#define ERR_LATHER_SHAPE_OFFSET	   20                        /*��������ʱ����״��������������Բ���뾶*/

#endif
