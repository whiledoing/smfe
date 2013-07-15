#ifdef _MSC_VER
#pragma once
#endif

#ifndef TIME_DOMAIN_FEATURES_H__
#define TIME_DOMAIN_FEATURES_H__

#include "global.h"
#include "common_function.h"

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

}

#endif // TIME_DOMAIN_FEATURES_H__

