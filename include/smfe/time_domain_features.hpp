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
	auto data = make_vec(lhs);
    return vec(arma::cor(make_vec(lhs), make_vec(rhs))).at(0);
}

template<typename ContainterType>
value_t mean_absolute_deviation(const ContainterType& source)
{
	value_t m = mean(source);

	value_t sum = 0.0;
	for(auto ite = source.begin(); ite != source.end(); ++ite)
		sum += abs(*ite - m);

	return sum / source.size();
}

template<typename ContainterType>
value_t mean_absolute_value(const ContainterType& source)
{
    value_t sum = 0.0;
    for(auto ite = source.begin(); ite != source.end(); ++ite)
        sum += abs(*ite);

    return sum / source.size();
}

template<typename ContainterType>
index_vec peak_index(const ContainterType& source)
{
	BOOST_STATIC_ASSERT((boost::is_same<typename ContainterType::value_type, value_t>::value));

	static auto abs_greater = [](value_t lhs, value_t rhs) {
		return abs(lhs) > abs(rhs);
	};

	std::vector<unsigned> res;
	for(unsigned i = 1u; i < source.size(); ++i) {
		if(abs_greater(source[i], source[i-1]) && abs_greater(source[i], source[i+1]))
			res.push_back(i);
	}

	return index_vec(std::move(res));
}

template<typename ContainterType>
index_vec zero_crossing_index(const ContainterType& c)
{
	BOOST_STATIC_ASSERT((boost::is_same<typename ContainterType::value_type, value_t>::value));

	BOOST_ASSERT(c.size() > 0);

    value_t left_value = c[0];
    value_t right_value = 0.0;

	std::vector<unsigned> result;
    for(unsigned i = 1u; i < c.size(); ++i) {
		right_value = c[i];

        if(left_value * right_value <= 0.0) 
            result.push_back(i);

		left_value = right_value;
    }

    return index_vec(std::move(result));
}

}
#endif // TIME_DOMAIN_FEATURES_HPP__

