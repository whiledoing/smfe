#include "smfe/frequency_domain_features.h"
#include "smfe/common_function.h"

#include <algorithm>
#include <functional>
using namespace std;

#include <boost/assert.hpp>

namespace smfe
{

inline bool operator< (const complex_t& lhs, const complex_t& rhs)
{
	return abs(lhs) < abs(rhs);
}

smfe::value_t median_frequency(const fm_vec& fm_vector)
{
    return fm_vector[fm_vector.size()/2].fre;
}

smfe::fm_vec frequency_magnitude_vec(const cx_vec& spectrum, value_t fs)
{
    // get first half frequency spectrum
    size_t size = spectrum.size();
    size_t half_size = spectrum.size()/2;
    fm_vec res(half_size);

    for(size_t i = 0u; i < half_size; ++i) {
        res[i].mag = 2 * abs(spectrum[i]) / size;
        res[i].fre = (value_t)(i) * fs / size;
    }

	return res;
}

smfe::fm_vec frequency_magnitude_vec(const vec& spectrum, value_t fs)
{
	return frequency_magnitude_vec(fft(spectrum), fs);
}

smfe::fm_vec sorted_frequency_magnitude_vec(const cx_vec& spectrum, value_t fs)
{
	fm_vec res = frequency_magnitude_vec(spectrum, fs);
	sort(res.begin(), res.end(), greater<FrequencyMagnitude>());
	return res;
}

smfe::fm_vec sorted_frequency_magnitude_vec(const vec& spectrum, value_t fs)
{
	return sorted_frequency_magnitude_vec(fft(spectrum), fs);
}

smfe::value_t first_quater(const fm_vec& fm_vector)
{
	return fm_vector[fm_vector.size()/4].fre;
}

smfe::value_t third_quater_frequency(const fm_vec& fm_vector)
{
	return fm_vector[fm_vector.size()/4*3].fre;
}

smfe::value_t principal_frequency(const fm_vec& fm_vector)
{
	return fm_vector.front().fre;
}

smfe::vec first_n_frequency(const fm_vec& fm_vector, int n)
{
	BOOST_ASSERT(n > 0 && n < fm_vector.size());

	vec res(n);
	for(size_t i = 0u; i < n; ++i)
		res[i] = fm_vector[i].fre;
	return res;
}

smfe::value_t frequency_energy(const fm_vec& fm_vector)
{
	vector<value_t> mags;
	for(auto fm : fm_vector)
		mags.push_back(fm.mag);

	return energy(mags);
}

smfe::value_t frequency_entropy(const fm_vec& fm_vector, int range_num /*= 8*/)
{
	BOOST_ASSERT(range_num > 0 && range_num < fm_vector.size());

	vector<int> count(range_num, 0);
	value_t beg_mag = fm_vector.back().mag;
	value_t dist = (fm_vector.front().mag - fm_vector.back().mag) / (value_t)(range_num);

	int index = 0;
	int size = fm_vector.size();
	for(auto fm : fm_vector) {
		index = static_cast<int>((fm.mag - beg_mag) / dist);
		index = (index == range_num) ? index - 1 : index;
		++count[index];
	}

	return entropy(count);
}

}