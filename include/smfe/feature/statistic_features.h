/**
 * @file statistic_features.h
 * @brief 计算统计特征
 * @author whiledoing
 * @date 2013-07-17
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef STATISTIC_FEATURES_H__
#define STATISTIC_FEATURES_H__

#include "../global.h"

#include <numeric>
#include <algorithm>

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace smfe
{
/**
 * @defgroup stfeatures statiscs-features
 *
 * 统计特征
 *
 * @{
 */

/**
 * 计算和值
 */
using arma::sum;

/**
 * 计算均值
 */
using arma::mean;

/**
 * 计算中值
 *
 * @note 如果数据总数为偶数,那么中值被计算为中间两个数值的均值
 */
using arma::median;

/**
 * 计算方差
 */
using arma::var;

/**
 * 计算标准差
 */
using arma::stddev;

/**
 * 最值
 */
using arma::min;
using arma::max;

/**
 * 得到第n个小的元素
 *
 * @note 输入数据 \c source 是<b>没有经过排序的</b>
 */
value_t get_nth_elem(const vec& source, int nth);

/**
 * 得到1/4小的元素 @sa get_nth_elem
 */
inline value_t first_quater(const vec& data)
{
    return get_nth_elem(data, data.size()/4);
}

/**
 * 得到3/4小的元素 @sa get_nth_elem
 */
inline value_t third_quater(const vec& data)
{
    return get_nth_elem(data, data.size()/4*3);
}

/**
 * Calculates energy of the signal.
 *
 * @param source signal source
 * @return signal energy
 */
value_t energy(const vec& source);

/**
* 计算信号的信息熵
*
* 信息熵表示为信号的分布均匀程度, 如果信号的大小平均分布在不同的值域区间上, 熵越大.
* 
* 计算过程描述为:
* 
* 1. 得到信号source的最大值max和最小值min
* 2. 将[min, max]区间分为nbins份, 统计落在其中的信号数目, 最后统计出各个区间上的概率p(i)
* 3. 计算信息熵  = -1 * sum(p(i) * log2(p(i))
* 
* @param source signal source
* @param nbins 信号按照幅值统计直方图的区域个数, 范围[1, +inf)
* @return signal energy
*/
value_t entropy(const vec& source, int nbins);

/**
 * Calculates power of the signal.
 *
 * @param source signal source
 * @return signal power
 */
inline value_t power(const vec& source)
{
    return energy(source) / source.size();
}

/**
 * Calculates Euclidean (L2) norm of the signal.
 *
 * @param source signal source
 * @return norm
 */
inline value_t norm(const vec& source)
{
    return std::sqrt(energy(source));
}

/**
 * Calculates root mean square level of the signal.
 *
 * @param source signal source
 * @return RMS level
 */
inline value_t rms(const vec& source)
{
    return std::sqrt(power(source));
}

/**  @} */
}

#endif // COMMON_FUNCTION_H__

/**
 * @example test_statistics_features.cpp
 * An example for test of current module @ref stfeatures
 */
