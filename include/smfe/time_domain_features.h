#ifdef _MSC_VER
#pragma once
#endif

#ifndef TIME_DOMAIN_FEATURES_H__
#define TIME_DOMAIN_FEATURES_H__

#include "global.h"
#include "statistic_function.h"

#include <vector>

namespace smfe
{
/**
 * Calculates skewness of the signal
 *
 * Skewness is a measure of symmetry, or more precisely, the lack of symmetry.
 *
 * The skewness for a normal distribution is zero, and any symmetric data
 * should have a skewness near zero. Negative values for the skewness indicate
 * data that are skewed left and positive values for the skewness
 * indicate data that are skewed right.
 *
 *
 * @param source signal source
 * @return skewness
 */
template<typename ContainterType>
value_t skewness(const ContainterType& source);

/**
* Calculates kurtosis of the signal
*
* Kurtosis is a measure of whether the data are peaked or flat relative to
* a normal distribution. That is, data sets with high kurtosis tend to
* have a distinct peak near the mean, decline rather rapidly, and have heavy tails.
*
* @note The term -3 is added in order to ensure that the normal distribution has zero kurtosis.
*
* @param source signal source
* @return skewness
*/
template<typename ContainterType>
value_t kurtosis(const ContainterType& source);

template<typename ContainterType>
value_t quartile_deviation(const ContainterType& source);

template<typename ContainterType>
value_t cross_correlation_coefficient(const ContainterType& lhs, const ContainterType& rhs);

template<typename ContainterType>
value_t mean_absolute_value(const ContainterType& source);

template<typename ContainterType>
value_t mean_absolute_deviation(const ContainterType& source);

/**
* Get all the peak value in container
*
* peak value is larger than its previous value and later value
*
* ```
*      abs(i) > abs(i-1) && abs(i) > abs(i+1)
* ```
*
* @tparam Container Type
* @result all the peak value index in the container
*/
template<typename ContainterType>
index_vec peak_index(const ContainterType& source);

/**
 * Get all the zero-crossing values in the container c
 * 
 * zero-crossing value is the value where data just change from positive to 
 * negative or negative to positive
 * 
 * @tparam Container Type
 * @result zero-crossing index in data collection
 */
template<typename ContainterType>
index_vec zero_crossing_index(const ContainterType& c);

/**
 * Get the efficient signal range 
 * 
 * ������Ч���ź�����
 * һ����Ч���ź������ڵ����ݶ�����һ���ƶ���ֵ����
 * 
 * ������̣�
 *
 * 1��������ȫ����Ϊ����ֵ
 * 2���������ݵ����ֵ������effective_percentage�õ���Ч�źŷ�ֵ����С��ֵ
 * 3����Ч����Ŀ�ʼ�ͽ�β����ֵ���������С��ֵ, �����ٴ���min_duration_frames��
 *	��Ч֡��ʱ����ж�Ϊ����һ����Ч����.
 * 
 * @tparam ConType �����������ͣ�Ҫ���������б������һά����
 * @param min_duration_frams ��С�ı���Ϊ����Ч��������ݳ���
 * @param c �������ݵ�����
 * @param effective_percentage ���϶���Ч������ֵ�������ֵ�ı���
 * @return ����������Ч�˶����������
 */
template<typename ContainterType>
index_pair_vec effective_duration_index_pair_vec(const ContainterType& c, int min_duration_frames = 1,
                                                         double effective_percentage = 0.2);
/**
 * �õ����������ķ�ֵ
 * 
 * @input
 * 1.	3d����
 * 2.	����3d�����ľ���
 * 
 * @return �����ķ�ֵ,���߰�������������ֵ������
 */
template<typename ContainterType>
inline value_t three_axis_amplitude(const ContainterType& c);
vec three_axis_amplitude(const mat& m);

/**
 * ��ֵ���(signal manitude area), ��ʾ�źž���ֵ��x���Χ����Ĵ�С
 *
 * @note �����ź�֮��ľ��뱻�趨Ϊ��λ1
 *
 * @param c �����źŵ�����
 * @return	��ֵ���
 */
template<typename ContainterType>
value_t sma(const ContainterType& c);

}

#endif // TIME_DOMAIN_FEATURES_H__

