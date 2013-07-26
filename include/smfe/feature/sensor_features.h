/**
 * @file sensor_features.h
 * @brief 和运动信号相关的特征
 * @author whiledoing
 * @date 2013-07-17
 */

#ifdef _MSC_VER
	#pragma once
#endif

#ifndef SENSOR_FEATURES_H__
#define SENSOR_FEATURES_H__

#include "../sensor_global.h"

namespace smfe 
{
/**
 * @defgroup sensorfeatures sensor-features
 *
 * 运动传感相关的特征
 *
 * 所有本模块中定义的容器类型 ContainterType 需要符合下面的条件:
 *
 * 1.   STL compatiable interface (begin end operator[] size etc..)
 * 2.   部分方法对容器中保存数据类型<b>Containtertype::value_type</b>限制为value_t*
 *
 * @{ */

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
 * @param init_velocity 初始时刻加速度
 * @param still_acce_threshold 被认定为数值0的加速度阈值(比如0.5,就表示所有加速度数值绝对值小于0.5的都认为是静止状态)
 * @param station_count_threshold 被认定为处于静止状态说需要最小的0数值加速度帧数,默认设置为最大int值,表示不进行静止状态的检测
 * @param using_ave_filter 是否使用均值滤波对数据进行预处理
 * @param filter_size 均值滤波使用filter的大小. i帧的数据,使用[i-filter, i+filter_size]之间的数值进行平滑
 * 
 * @return velocity collection 
 */
vec velocity(const vec& acce_data, 
						value_t delta = 1.0,
                        value_t init_velocity = 0.0, 
                        value_t still_acce_threshold = 0.0, 
						int station_count_threshold = INT_MAX,
                        bool using_ave_filter = false,
						int filter_size = 2
);

/**
 * 计算短时间内(2s)内运动传感器移动的位移(也可以理解为角度,如果使用角速度作为输入参数的话)
 *
 * 输入数据必须是表示速度的数据
 * 
 * @note 
 * 1.	求解的数值没有量纲,每一个相邻数据之间的间隔被认为为delta的大小.比如
 * 等间隔采样的加速度速度数据,delta就是采样时间fs.
 * 2.	degree的数值在[2,4]之间
 * 
 * @sa integration
 * 
 * @param velocity_data 输入的速度数据
 * @param delta 相邻数据之间间隔大小
 * @param degree 积分算法使用的degree数目
 * @param using_ave_filter 是否使用均值滤波对数据进行预处理
 * @param filter_size 均值滤波使用filter的大小. i帧的数据,使用[i-filter, i+filter_size]之间的数值进行平滑
 * 
 * @return moving distance
 */
value_t distance(const vec& velocity_data, 
				 value_t delta = 1.0,
				 int degree = 3,
				 bool using_ave_filter = false,
				 int filter_size = 2
);

/**  @} */
}

#endif // SENSOR_FEATURES_H__

/**
 * @example test_sensor_features.cpp
 * An example for current module @ref sensorfeatures
 */
