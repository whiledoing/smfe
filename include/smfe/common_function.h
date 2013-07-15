#ifdef _MSC_VER
	#pragma once
#endif

#ifndef COMMON_FUNCTION_H__
#define COMMON_FUNCTION_H__

#include "global.h"

#include <numeric>
#include <algorithm>

#include <boost/assert.hpp>

namespace smfe
{
    template<typename ContainterType>
    inline value_t sum(ContainterType& source)
    {
        return arma::sum(make_vec(source));
    }

    template<typename ContainterType>
    inline value_t mean(ContainterType& source)
    {
		return arma::mean(make_vec(source));
	}

    template<typename ContainterType>
    inline value_t median(ContainterType& source)
    {
		return get_nth_elem(ContainterType(source), source.size()/2);
	}
	
    template<typename ContainterType>
    inline value_t var(ContainterType& source)
    {
		return arma::var(make_vec(source));
	}

    template<typename ContainterType>
    inline value_t stddev(ContainterType& source)
    {
		return arma::stddev(make_vec(source));
	}

    template<typename ContainterType>
    inline value_t min(ContainterType& source)
    {
		return arma::min(make_vec(source));
	}

    template<typename ContainterType>
    inline value_t max(ContainterType& source)
    {
		return arma::max(make_vec(source));
	}

    template<typename ContainterType>
    value_t get_nth_elem(ContainterType& source, int nth)
    {
        BOOST_ASSERT(nth < source.size());

        auto dst_ite = source.begin() + nth;
        std::nth_element(source.begin(), dst_ite, source.end());
        return *dst_ite;
    }

    template<typename ContainterType>
	value_t first_quater(const ContainterType& data)
    {
		return get_nth_elem(ContainterType(data), data.size()/4);
	}

    template<typename ContainterType>
	value_t third_quater(const ContainterType& data)
    {
        return get_nth_elem(ContainterType(data), data.size()/4*3);
	}

	/**
     * Calculates energy of the signal.
     *
     * @param source signal source
     * @return signal energy
     */
	template<typename ContainterType>
    value_t energy(const ContainterType& source)
    {
		value_t init_value = 0.0;
        return std::accumulate(
            std::begin(source),
            std::end(source),
            init_value,
            [] (value_t acc, value_t value) {
                return acc + value * value;
            }
        );
    }

     /**
     * Calculates entropy of the singal
     *
     * @param source signal source
     * @return signal energy
     */
	template<typename ContainterType>
    value_t entropy(const ContainterType& source)
    {
		int total_size = 0;
		for(auto ite = std::begin(source); ite != std::end(source); ++ite) {
			BOOST_ASSERT(*ite >= 0);
			total_size += *ite;
        }
        BOOST_ASSERT(total_size > 0);

		value_t sum = 0.0;
		value_t p = 0.0;
		for(auto ite = std::begin(source); ite != std::end(source); ++ite) {
            p = (value_t)(*ite) / total_size;
			if(p != 0.0)
				sum += p * log(p);
        }

		return -sum;
    }

    /**
     * Calculates power of the signal.
     *
     * @param source signal source
     * @return signal power
     */
	template<typename ContainterType>
    inline value_t power(const ContainterType& source)
    {
        return energy(source) / source.size();
    }

    /**
     * Calculates Euclidean (L2) norm of the signal.
     *
     * @param source signal source
     * @return norm
     */
	template<typename ContainterType>
    inline value_t norm(const ContainterType& source)
    {
        return std::sqrt(energy(source));
    }

    /**
     * Calculates root mean square level of the signal.
     *
     * @param source signal source
     * @return RMS level
     */
	template<typename ContainterType>
    inline value_t rms(const ContainterType& source)
    {
        return std::sqrt(power(source));
    }

}

#endif // COMMON_FUNCTION_H__

