#include "smfe/feature/time_domain_features.h"
#include "smfe/feature/statistic_features.h"
#include "smfe/feature/integral_calculus.h"

#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/skewness.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>
#include <boost/type_traits/is_same.hpp>

#include <functional>
#include <algorithm>

namespace smfe
{

value_t skewness(const vec& source)
{
    using namespace boost::accumulators;

    CHECK_VALUE_TYPE(source);

    accumulator_set<value_t, stats<tag::skewness > > ske_set;
    std::for_each(source.begin(), source.end(), std::ref(ske_set));

    return boost::accumulators::skewness(ske_set);
}

value_t kurtosis(const vec& source)
{
    using namespace boost::accumulators;

    CHECK_VALUE_TYPE(source);

    accumulator_set<value_t, stats<tag::kurtosis > > kur_set;
    std::for_each(source.begin(), source.end(), std::ref(kur_set));

    return boost::accumulators::kurtosis(kur_set);
}

value_t quartile_deviation(const vec& source)
{
    return third_quater(source) - first_quater(source);
}

value_t cross_correlation_coefficient(const vec& lhs, const vec& rhs)
{
    BOOST_ASSERT(lhs.size() == rhs.size());
    auto data = make_vec(lhs);
    return vec(arma::cor(make_vec(lhs), make_vec(rhs))).at(0);
}

value_t mean_absolute_deviation(const vec& source)
{
    value_t m = smfe::mean(source);

    value_t sum = 0.0;
    for(auto ite = source.begin(); ite != source.end(); ++ite)
        sum += abs(*ite - m);

    return sum / source.size();
}

value_t mean_absolute_value(const vec& source)
{
    return smfe::mean(make_abs(source));
}

index_vec peak_index(const vec& source)
{
    CHECK_VALUE_TYPE(source);

    static auto abs_greater = [](value_t lhs, value_t rhs) {
        return fabs(lhs) > fabs(rhs);
    };

    std::vector<unsigned> res;
    for(unsigned i = 1u; i < source.size() - 1; ++i) {
        if(abs_greater(source[i], source[i-1]) && abs_greater(source[i], source[i+1]))
            res.push_back(i);
    }

    return index_vec(std::move(res));
}

index_vec zero_crossing_index(const vec& c)
{
    CHECK_VALUE_TYPE(c);

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

index_pair_vec effective_duration_index_pair_vec(const vec& c, int min_duration_frames /*= 1*/, double effective_percentage /*= 0.2*/)
{
    BOOST_ASSERT(min_duration_frames > 0);
    BOOST_ASSERT(effective_percentage > 0.0);

    CHECK_VALUE_TYPE(c);

    auto abs_c = make_abs(c);
    auto max_v = smfe::max(abs_c);
    auto delta_v = max_v * effective_percentage;

    index_t duration_count = 0;
    bool find_start = false;
    index_t start_index = -1, end_index = -1;

    std::vector<std::pair<index_t, index_t> > result;

    auto c_beg = abs_c.begin();
    auto c_end = abs_c.end();
    auto ite = c_beg;

    while(ite != c_end) {
        if(!find_start) {
            if(*ite >= delta_v) {
                ++duration_count;
                if(duration_count == min_duration_frames) {
                    find_start = true;
                    duration_count = 0;
                    start_index = std::distance(c_beg, ite) - min_duration_frames + 1;
                }
            } else {
                duration_count = 0;
            }
        } else {
            if(*ite < delta_v) {
                ++duration_count;
                if(duration_count == min_duration_frames) {
                    find_start = false;
                    duration_count = 0;
                    end_index = std::distance(c_beg, ite) - min_duration_frames;
                    result.push_back(std::make_pair(start_index, end_index));
                }
            } else {
                duration_count = 0;
            }
        }
        ++ite;
    }

    return result;
}

value_t three_axis_amplitude(const vec& c)
{
    CHECK_VALUE_TYPE(c);

    BOOST_ASSERT_MSG(c.size() == 3, "only support 3d vector data");

    return sqrt(c[0]*c[0] + c[1]*c[1] + c[2]*c[2]);
}

value_t sma(const vec& c)
{
    return integration(make_abs(c));
}

vec three_axis_amplitude(const mat& m)
{
    vec res(m.n_cols);

    for(index_t i = 0u; i < m.n_cols; ++i) {
        res[i] = three_axis_amplitude(vec(m.col(i)));
    }

    return res;
}

} // namespace smfe

