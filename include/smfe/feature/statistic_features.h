/**
 * @file statistic_features.h
 * @brief ����ͳ������
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
 * ͳ������
 *
 * @{
 */

/**
 * �����ֵ
 */
using arma::sum;

/**
 * �����ֵ
 */
using arma::mean;

/**
 * ������ֵ
 *
 * @note �����������Ϊż��,��ô��ֵ������Ϊ�м�������ֵ�ľ�ֵ
 */
using arma::median;

/**
 * ���㷽��
 */
using arma::var;

/**
 * �����׼��
 */
using arma::stddev;

/**
 * ��ֵ
 */
using arma::min;
using arma::max;

/**
 * �õ���n��С��Ԫ��
 *
 * @note �������� \c source ��<b>û�о��������</b>
 */
value_t get_nth_elem(const vec& source, int nth);

/**
 * �õ�1/4С��Ԫ�� @sa get_nth_elem
 */
inline value_t first_quater(const vec& data)
{
    return get_nth_elem(data, data.size()/4);
}

/**
 * �õ�3/4С��Ԫ�� @sa get_nth_elem
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
* @note ���������б�������Ϊ int ���� unsigned int
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
