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
template<typename ContainterType>
value_t mean_filter_get_one_index(const ContainterType& data, int filter_size, int index)
{
    BOOST_ASSERT(index < data.size());
    BOOST_ASSERT(filter_size >= 0);

    int low = index - filter_size;
    int high = index + filter_size;
    if(low < 0) low = 0;
    if(high > data.size() - 1)  high = data.size() - 1;

    value_t sum = 0;
    for(int i = low; i <= high; ++i)
        sum += data[i];
    return (value_t)(sum/(high-low+1));
}

/**
 * @brief 计算一段区间内的滤波结果
 *
 * @note 区间范围为[start_index, end_index]两边都是包含关系
 */
template<typename ContainterType>
ContainterType mean_filter_get_range(const ContainterType& data, int filter_size, int start_index, int end_index)
{
    BOOST_ASSERT(start_index < data.size());
    BOOST_ASSERT(end_index < data.size());
    BOOST_ASSERT(start_index <= end_index);
    BOOST_ASSERT(filter_size >= 0);

    ContainterType result(end_index - start_index + 1);
    for(int i = start_index; i <= end_index; ++i) {
        result[i-start_index] = mean_filter_get_one_index(data, filter_size, i);
    }
    return result;
}


/**
 * @brief 计算当前所有数据的均值滤波结果
 */
template<typename ContainterType>
ContainterType mean_filter(const ContainterType& data, int filter_size)
{
    return mean_filter_get_range(data, filter_size, 0, data.size() - 1);
}
}

#endif // MEAN_FILTER_H__

/**
 * @example test_sensor_features.cpp
 * An example for using mean_filter
 */
