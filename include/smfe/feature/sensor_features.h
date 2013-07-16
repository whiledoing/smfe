#ifdef _MSC_VER
	#pragma once
#endif

#ifndef SENSOR_FEATURES_H__
#define SENSOR_FEATURES_H__

#include "../sensor_global.h"

namespace smfe 
{

/**
 * 计算一定时间运动的速度
 * 
 * 输入的数据必须为加速度数据
 * 
 * @note 求解的数值没有量纲,每一个相邻数据之间的间隔被认为为delta的大小.比如
 * 等间隔采样的加速度速度数据,delta就是采样时间fs.
 * 
 * @param acce_data 输入的加速度数据向量
 * @param delta 相邻数据之间间隔大小
 * @param still_acce_threshold 被认定为数值0的加速度阈值(比如0.5,就表示所有加速度数值绝对值小于0.5的都认为是静止状态)
 * @param station_count_threshold 被认定为处于静止状态说需要最小的0数值加速度帧数
 * @param init_velocity 初始时刻加速度
 * @param using_ave_filter 是否使用均值滤波对数据进行预处理
 * @param filter_size 均值滤波使用filter的大小. i帧的数据,使用[i-filter, i+filter_size]之间的数值进行平滑
 * 
 * @return velocity collection 
 */
template<typename ContainterType>
ContainterType velocity(const ContainterType& acce_data, 
						value_t delta = 1.0,
                        value_t still_acce_threshold = 0.0, 
						int station_count_threshold = 1,
                        value_t init_velocity = 0.0, 
                        bool using_ave_filter = false,
						int filter_size = 2
);

/**
 * 计算短时间内(2s)内运动传感器移动的位移(也可以理解为角度,如果使用角速度作为输入参数的话)
 *
 * 输入数据必须是表示速度的数据
 * 
 * @note 求解的数值没有量纲,每一个相邻数据之间的间隔被认为为delta的大小.比如
 * 等间隔采样的加速度速度数据,delta就是采样时间fs.
 * 
 * @param velocity_data 输入的速度数据
 * @param delta 相邻数据之间间隔大小
 * @param using_ave_filter 是否使用均值滤波对数据进行预处理
 * @param filter_size 均值滤波使用filter的大小. i帧的数据,使用[i-filter, i+filter_size]之间的数值进行平滑
 * 
 * @return moving distance
 */
template<typename ContainterType>
value_t distance(const ContainterType& velocity_data, 
				 value_t delta = 1.0,
				 bool using_ave_filter = false,
				 int filter_size = 2
);

}

#endif // SENSOR_FEATURES_H__

