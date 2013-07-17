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
 * ���б�ģ���ж������������ ContainterType ��Ҫ�������������:
 *
 * 1.   STL compatiable interface (begin end operator[] size etc..)
 * 2.   ���ַ����������б�����������<b>Containtertype::value_type</b>����Ϊvalue_t
 *
 * @{
 */

/**
 * �����ֵ
 */
template<typename ContainterType>
inline value_t sum(ContainterType& source)
{
    return arma::sum(make_vec(source));
}

/**
 * �����ֵ
 */
template<typename ContainterType>
inline value_t mean(ContainterType& source)
{
    return arma::mean(make_vec(source));
}

/**
 * ������ֵ
 *
 * @note �����������Ϊż��,��ô��ֵ������Ϊ�м�ֵ�нϴ��һ��
 */
template<typename ContainterType>
inline value_t median(ContainterType& source)
{
    return get_nth_elem(ContainterType(source), source.size()/2);
}

/**
 * ���㷽��
 */
template<typename ContainterType>
inline value_t var(ContainterType& source)
{
    return arma::var(make_vec(source));
}

/**
 * �����׼��
 */
template<typename ContainterType>
inline value_t stddev(ContainterType& source)
{
    return arma::stddev(make_vec(source));
}

template<typename ContainterType>
inline value_t min(ContainterType& source)
{
    return arma::min(make_vec(source));
}

template<typename ContainterType>
inline value_t max(ContainterType& source)
{
    return arma::max(make_vec(source));
}

/**
 * �õ���n��С��Ԫ��
 *
 * @note �������� \c source ��<b>û�о��������</b>
 */
template<typename ContainterType>
value_t get_nth_elem(ContainterType& source, int nth)
{
    BOOST_ASSERT(nth < source.size());

    auto dst_ite = source.begin() + nth;
    std::nth_element(source.begin(), dst_ite, source.end());
    return *dst_ite;
}

/**
 * �õ�1/4С��Ԫ�� @sa get_nth_elem
 */
template<typename ContainterType>
value_t first_quater(const ContainterType& data)
{
    return get_nth_elem(ContainterType(data), data.size()/4);
}

/**
 * �õ�3/4С��Ԫ�� @sa get_nth_elem
 */
template<typename ContainterType>
value_t third_quater(const ContainterType& data)
{
    return get_nth_elem(ContainterType(data), data.size()/4*3);
}

/**
 * Calculates energy of the signal.
 *
 * @param source signal source
 * @return signal energy
 */
template<typename ContainterType>
value_t energy(const ContainterType& source)
{
    value_t init_value = 0.0;
    return std::accumulate(
               std::begin(source),
               std::end(source),
               init_value,
    [] (value_t acc, value_t value) {
        return acc + value * value;
    });
}

/**
* Calculates entropy of the signal
*
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
template<typename ContainterType>
inline value_t power(const ContainterType& source)
{
    return energy(source) / source.size();
}

/**
 * Calculates Euclidean (L2) norm of the signal.
 *
 * @param source signal source
 * @return norm
 */
template<typename ContainterType>
inline value_t norm(const ContainterType& source)
{
    return std::sqrt(energy(source));
}

/**
 * Calculates root mean square level of the signal.
 *
 * @param source signal source
 * @return RMS level
 */
template<typename ContainterType>
inline value_t rms(const ContainterType& source)
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
