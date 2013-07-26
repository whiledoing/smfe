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
* Calculates entropy of the signal
*
* @note 输入容器中必须类型为 int 或者 unsigned int
* @param source signal source
* @return signal energy
*/
template<typename ContainterType>
value_t entropy(const ContainterType& source)
{
    BOOST_STATIC_ASSERT(
        (boost::is_same<typename ContainterType::value_type, int>::value) ||
        (boost::is_same<typename ContainterType::value_type, unsigned int>::value)
    );

    int total_size = 0;
    for(auto ite = std::begin(source); ite != std::end(source); ++ite) {
        BOOST_ASSERT(*ite >= 0);
        total_size += *ite;
    }
    BOOST_ASSERT(total_size > 0);

    value_t sum = 0.0;
    value_t p = 0.0;
    for(auto ite = std::begin(source); ite != std::end(source); ++ite) {
        p = (value_t)(*ite) / total_size;
        if(p != 0.0)
            sum += p * log(p);
    }

    return -sum;
}

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
