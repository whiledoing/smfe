/**
 * @file mean_filter.h
 * @brief 均值滤波
 * @author whiledoing
 * @date 2013-07-17
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef MEAN_FILTER_H__
#define MEAN_FILTER_H__

#include "../global.h"

#include <boost/assert.hpp>

namespace smfe
{
/**
 * @brief 计算数据特定index下的滤波结果
 *
 * @param data 输入数据
 * @param filter_size 中值滤波大小
 * @param index 滤波的index位置
 *
 * @return index位置下的滤波结果
 */
value_t mean_filter_get_one_index(const vec& data, int filter_size, int index);

/**
 * @brief 计算一段区间内的滤波结果
 *
 * @note 区间范围为[start_index, end_index)两边都是包含关系
 */
vec mean_filter_get_range(const vec& data, int filter_size, int start_index, int end_index);


/**
 * @brief 计算当前所有数据的均值滤波结果
 */
inline vec mean_filter(const vec& data, int filter_size)
{
    return mean_filter_get_range(data, filter_size, 0, data.size());
}

}

#endif // MEAN_FILTER_H__

/**
 * @example test_sensor_features.cpp
 * An example for using mean_filter
 */
