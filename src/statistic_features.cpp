#include "smfe/feature/statistic_features.h"

namespace smfe
{
value_t energy(const vec& source)
{
    value_t init_value = 0.0;
    return std::accumulate(
               std::begin(source),
               std::end(source),
               init_value,
    [] (value_t acc, value_t value) {
        return acc + value * value;
    });
}

value_t get_nth_elem(const vec& source, int nth)
{
    BOOST_ASSERT(nth < source.size());

    // copy source
    vec res = source;
    auto dst_ite = res.begin() + nth;
    std::nth_element(res.begin(), dst_ite, res.end());
    return *dst_ite;
}

}
