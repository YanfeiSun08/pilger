#ifndef ERR_H
#define ERR_H

/* 声明出错代码 */
#define ERR_NO_ERROR                   0                        /* No error */

#define ERR_ROUGHER_DEPTH_START        1                        /*轧辊开粗时，起始深度小于零*/
#define ERR_ROUGHER_TOOL_DIAME         2                        /*轧辊开粗时，刀具直径小于等于零*/
#define ERR_ROUGHER_DEPTH_INCR         3                        /*轧辊开粗时，深度增量小于等于零*/
#define ERR_ROUGHER_WIDTH_INCR         4                        /*轧辊开粗时，横向增量小于等于零*/
#define ERR_ROUGHER_FEED               5                        /*轧辊开粗时，加工速度小于等于零*/
#define ERR_ROUGHER_DEPTH_FEED         6                        /*轧辊开粗时，下刀速度小于等于零*/
#define ERR_ROUGHER_DISTANCE           7                        /*轧辊开粗时，抬刀距离小于等于零*/
#define ERR_ROUGHER_SAF_HEIGHT         8                        /*轧辊开粗时，安全高度小于等于零*/

#define ERR_REFINE_PROC_NUM            9                        /*轧辊精加工时，加工次数小于等于零*/
#define ERR_REFINE_ALLOWANCE           10                        /*轧辊精加工时，加工量小于零*/
#define ERR_REFINE_TOOL_DIAME          11                        /*轧辊精加工时，刀具直径小于等于零*/
#define ERR_REFINE_ANGLE_INCR          12                        /*轧辊精加工时，角度增量小于等于零*/
#define ERR_REFINE_FEED                13                        /*轧辊精加工时，进给速度小于等于零*/
#define ERR_REFINE_SAF_HEIGHT          14                        /*轧辊精加工时，安全高度小于等于零*/

#define ERR_CHAMFER_TOOL_NUM           15                        /*轧辊倒角加工时，加工次数小于等于零*/
#define ERR_CHAMFER_TOOL_DIAME         16                        /*轧辊倒角加工时，刀具直径小于等于零*/
#define ERR_CHAMFER_FEED               17                        /*轧辊倒角加工时，进给速度小于等于零*/
#define ERR_CHAMFER_SAF_HEIGHT         18                        /*轧辊倒角加工时，安全高度小于等于零*/

#define ERR_PILGER_RADIUS              19                        /*轧辊加工时，轧辊圆弧半径小于等于零*/
#define ERR_ROUGHER_SHAPE_OFFSET	   20                        /*轧辊开粗时，形状补偿量大于轧辊圆弧半径*/
#define ERR_REFINE_SHAPE_OFFSET        21                        /*轧辊精加工时，形状补偿量大于轧辊圆弧半径*/
#define ERR_CHAMFER_SHAPE_OFFSET       22                        /*轧辊倒角加工时，形状补偿量大于轧辊圆弧半径*/

#define ERR_ROUGHER_WIDTH_GT_TOOL      23                        /*轧辊开粗时，横向增量大于刀具直径*/
#define ERR_ROUGHER_DEPTH_GT_MAX       24                        /*轧辊开粗时，起始深度大于轧辊开粗最大深度*/
#define ERR_REFINE_ANGLE_START         25                        /*轧辊精加工时，起始角度不在0~90度范围*/


/*  声明车削错误代码 */
#define ERR_LATHER_DEPTH_MAX          26                        /*轧辊车削时，最大深度小于零*/
#define ERR_LATHER_TOOL_DIAME         27                        /*轧辊车削时，刀具直径小于等于零*/
#define ERR_LATHER_DEPTH_INCR         28                        /*轧辊车削时，深度增量小于等于零*/
#define ERR_LATHER_ANGLE_INCR         29                        /*轧辊车削时，角度增量小于等于零*/
#define ERR_LATHER_FEED               30                        /*轧辊车削时，加工速度小于等于零*/
#define ERR_LATHER_SAF_HEIGHT         31                        /*轧辊车削时，安全高度小于等于零*/
#define ERR_LATHER_SHAPE_OFFSET	   20                        /*轧辊车削时，形状补偿量大于轧辊圆弧半径*/

#endif
