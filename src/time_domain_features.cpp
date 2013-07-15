#include "smfe/time_domain_features.hpp"

#include <vector>

namespace smfe
{
typedef std::vector<value_t> std_vec;

template value_t skewness<vec>(const vec& source);
template value_t skewness<std_vec>(const std_vec& source);

template value_t kurtosis<vec>(const vec& source);
template value_t kurtosis<std_vec>(const std_vec& source);

template value_t quartile_deviation<vec>(const vec& source);
template value_t quartile_deviation<std_vec>(const std_vec& source);

template value_t cross_correlation_coefficient<vec>(const vec& lhs, const vec& rhs);
template value_t cross_correlation_coefficient<std_vec>(const std_vec& lhs, const std_vec& rhs);

}