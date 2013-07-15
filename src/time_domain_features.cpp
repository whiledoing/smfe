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

INSTIATE_R(peak_index, index_vec);
INSTIATE_R(zero_crossing_index, index_vec);

INSTIATE_TWO_PARA(cross_correlation_coefficient);
}