#ifdef _MSC_VER
	#pragma once
#endif

#ifndef FREQUENCY_DOMAIN_FEATURES_H__
#define FREQUENCY_DOMAIN_FEATURES_H__

#include "../global.h"
#include <iostream>
#include <vector>

namespace smfe
{
    using arma::fft;
    using arma::ifft;

	struct FrequencyMagnitude
    {
        FrequencyMagnitude(value_t f = 0.0, value_t m = 0.0) : fre(f), mag(m) {}
		value_t fre;
		value_t	mag;

		friend inline bool operator<(const FrequencyMagnitude& lhs, const FrequencyMagnitude& rhs)
        {
			return lhs.mag < rhs.mag;
		}

		friend inline bool operator>(const FrequencyMagnitude& lhs, const FrequencyMagnitude& rhs)
        {
			return lhs.mag >= rhs.mag;
		}

        friend inline bool operator==(const FrequencyMagnitude& lhs, const FrequencyMagnitude& rhs)
        {
            return abs(lhs.mag - rhs.mag) < 1e-9 && abs(lhs.fre - rhs.fre) < 1e-9;
        }

        friend inline bool operator!=(const FrequencyMagnitude& lhs, const FrequencyMagnitude& rhs)
        {
			return !(lhs == rhs);
        }

		friend std::ostream& operator<<(std::ostream& os, const FrequencyMagnitude& fm) {
			os << "Frequency : " << fm.fre << "Magnitude : " << fm.mag << std::endl;
			return os;
		}
	};

	typedef std::vector<FrequencyMagnitude> fm_vec;

	fm_vec frequency_magnitude_vec(const vec& spectrum, value_t fs);
	fm_vec frequency_magnitude_vec(const cx_vec& spectrum, value_t fs);

	fm_vec sorted_frequency_magnitude_vec(const vec& spectrum, value_t fs);
	fm_vec sorted_frequency_magnitude_vec(const cx_vec& spectrum, value_t fs);

    value_t principal_frequency(const fm_vec& fm_vector);
	value_t median_frequency(const fm_vec& fm_vector);
    value_t first_quater_frequency(const fm_vec& fm_vector);
    value_t third_quater_frequency(const fm_vec& fm_vector);
    vec first_n_frequency(const fm_vec& fm_vector, int n);

    value_t frequency_energy(const fm_vec& fm_vector);
    value_t frequency_entropy(const fm_vec& fm_vector, int range_num = 8);
}

#endif // FREQUENCY_DOMAIN_FEATURES_H__