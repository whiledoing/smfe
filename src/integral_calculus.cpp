#include "smfe/feature/integral_calculus.h"

namespace smfe {

smfe::value_t smfe::integration(vec const& data, int degree /*= 2*/)
{
    CHECK_VALUE_TYPE(data);

    BOOST_ASSERT(degree >= 2 && degree <= 4);

    value_t sum = 0.0;

    for(size_t i = degree-1; i < data.size() - (degree-1); ++i)
        sum += data[i];

    if(degree == 2) {
        sum += (data[0] + data[data.size()-1])/2;
    }

    if(degree == 3) {
        sum += (data[0] + 5*data[1] + 5*data[data.size()-2] + data[data.size()-1]) / 6;
    }

    if(degree == 4) {
        sum += (data[0] + 4*data[1] + 7*data[2] + 7*data[data.size()-3] + 4*data[data.size()-2] + data[data.size()-1]) / 8;
    }

    return sum;
}

smfe::value_t smfe::integration(vec const& data, vec const& delta_vec)
{
    CHECK_VALUE_TYPE(data);
    CHECK_VALUE_TYPE(delta_vec);

    BOOST_ASSERT(data.size() - 1 == delta_vec.size());

    value_t sum = 0.0;

    for(size_t i = 0u; i < data.size() - 1; ++i)
        sum += (data[i] + data[i+1]) / 2 * delta_vec[i];

    return sum;
}

}
