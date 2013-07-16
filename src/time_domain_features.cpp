#include "smfe/time_domain_features.hpp"

#include <vector>
typedef std::vector<smfe::value_t> std_vec;

#define INSTIATE(func)	\
template value_t func<vec>(const vec& source);	\
template value_t func<std_vec>(const std_vec& source);

#define INSTIATE_TWO_PARA(func)	\
template value_t func<vec>(const vec& lhs, const vec& rhs);	\
template value_t func<std_vec>(const std_vec& lhs, const std_vec& rhs);

#define INSTIATE_R(func, r_type)	\
template r_type func<vec>(const vec& source);	\
template r_type func<std_vec>(const std_vec& source);

namespace smfe
{
INSTIATE(skewness);
INSTIATE(kurtosis);
INSTIATE(quartile_deviation);
INSTIATE(mean_absolute_deviation);
INSTIATE(mean_absolute_value);
INSTIATE(three_axis_amplitude);
INSTIATE(sma);

INSTIATE_R(peak_index, index_vec);
INSTIATE_R(zero_crossing_index, index_vec);

INSTIATE_TWO_PARA(cross_correlation_coefficient);

template index_pair_vec effective_duration_index_pair_vec(const std_vec& c, 
				   int min_duration_frames, double effective_percentage);
template index_pair_vec effective_duration_index_pair_vec(const vec& c, 
				   int min_duration_frames, double effective_percentage);


}

namespace smfe
{
    vec three_axis_amplitude(const mat& m)
    {
        vec res(m.n_cols);

        for(index_t i = 0u; i < m.n_cols; ++i) {
            res[i] = three_axis_amplitude(vec(m.col(i)));
        }

        return res;
    }
}