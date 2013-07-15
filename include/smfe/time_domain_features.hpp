#ifdef _MSC_VER
#pragma once
#endif

#ifndef TIME_DOMAIN_FEATURES_HPP__
#define TIME_DOMAIN_FEATURES_HPP__

#include "time_domain_features.h"
#include "common_function.h"

#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/skewness.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>
#include <boost/type_traits/is_same.hpp>

#include <functional>
#include <algorithm>

namespace smfe
{

template<typename ContainterType>
value_t skewness(const ContainterType& source)
{
    using namespace boost::accumulators;

    BOOST_STATIC_ASSERT((boost::is_same<typename ContainterType::value_type, value_t>::value));

    accumulator_set<int, stats<tag::skewness > > ske_set;
    std::for_each(source.begin(), source.end(), std::ref(ske_set));

    return boost::accumulators::skewness(ske_set);
}

template<typename ContainterType>
value_t kurtosis(const ContainterType& source)
{
    using namespace boost::accumulators;

    BOOST_STATIC_ASSERT((boost::is_same<typename ContainterType::value_type, value_t>::value));

    accumulator_set<int, stats<tag::kurtosis > > kur_set;
    std::for_each(source.begin(), source.end(), std::ref(kur_set));

    return boost::accumulators::kurtosis(kur_set);
}

template<typename ContainterType>
value_t quartile_deviation(const ContainterType& source)
{
    return third_quater(source) - first_quater(source);
}

template<typename ContainterType>
value_t cross_correlation_coefficient(const ContainterType& lhs, const ContainterType& rhs)
{
    BOOST_ASSERT(lhs.size() == rhs.size());
    return vec(arma::cor(make_vec(lhs), make_vec(rhs), 1)).at(0);
}

}
#endif // TIME_DOMAIN_FEATURES_HPP__

