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
 * 计算有效的信号区域。
 * 一个有效的信号区域内的数据都大于一个制定的值幅。
 * 
 * 计算过程：
 *
 * 1）将数据全部变为绝对值
 * 2）计算数据的最大值，乘上effective_percentage得到有效信号幅值的最小阈值
 * 3）有效区域的开始和结尾的数值必须大于最小阈值, 且至少存在min_duration_frames个
 *	有效帧的时候才判定为进入一个有效区域.
 * 
 * @tparam ConType 数据容器类型，要求是容器中保存的是一维数据
 * @param min_duration_frams 最小的被认为是有效区域的数据长度
 * @param c 保存数据的容器
 * @param effective_percentage 被认定有效区域数值和最大数值的比例
 * @return 保存所有有效运动区域的容器
 */
template<typename ContainterType>
index_pair_vec effective_duration_index_pair_vec(const ContainterType& c, int min_duration_frames = 1,
                                                         double effective_percentage = 0.2);
/**
 * 得到三轴向量的幅值
 * 
 * @input
 * 1.	3d向量
 * 2.	包含3d向量的矩阵
 * 
 * @return 向量的幅值,或者包含所有向量幅值的向量
 */
template<typename ContainterType>
inline value_t three_axis_amplitude(const ContainterType& c);
vec three_axis_amplitude(const mat& m);

/**
 * 幅值面积(signal manitude area), 表示信号绝对值与x轴包围面积的大小
 *
 * @note 相邻信号之间的距离被设定为单位1
 *
 * @param c 包含信号的向量
 * @return	幅值面积
 */
template<typename ContainterType>
value_t sma(const ContainterType& c);

}

#endif // TIME_DOMAIN_FEATURES_H__

