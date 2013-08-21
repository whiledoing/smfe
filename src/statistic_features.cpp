#include "smfe/feature/statistic_features.h"

#include <vector>

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

smfe::value_t entropy(const vec& source, int nbins)
{
	BOOST_ASSERT(nbins > 0);

	value_t max_v = max(source);
	value_t min_v = min(source);

    std::vector<int> count(nbins, 0);
    value_t bin_size = (max_v - min_v) / nbins;

	// 统计个数
    int index = 0;
	for(int i = 0; i < source.size(); ++i) {
        index = static_cast<int>((source[i] - min_v) / bin_size);
        index = (index == nbins) ? index - 1 : index;
        ++count[index];
    }

	// 计算信息熵
	int n = source.size();
    value_t sum = 0.0; value_t p = 0.0;
	const value_t error = 1e-8;
	const value_t LOG_2 = log(2);
	for(int i = 0; i < count.size(); ++i) {
        p = (value_t)(count[i]) / n; /* 得到概率 */
        if(abs(p) > error) sum += p * log(p) / LOG_2;
    }

    return -sum;
}

}
