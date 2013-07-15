#ifdef _MSC_VER
	#pragma once
#endif

#ifndef GLOBAL_H__
#define GLOBAL_H__

#if defined (_WIN32) && defined(BUILD_SHARED_LIBS)
#  if defined(SMFE_BUILD)
#    define SMFE_EXPORT __declspec(dllexport)
#  else
#    define SMFE_EXPORT  __declspec(dllimport)
#  endif
#else
#    define SMFE_EXPORT
#endif

#include <complex>
#include <vector>
#include <utility>

#include <boost/assert.hpp>

#include <armadillo>

namespace smfe
{
	typedef double value_t;

	typedef arma::Mat<value_t> mat;
	typedef arma::Col<value_t> vec;

	typedef std::complex<value_t> complex_t;

	typedef arma::Col<complex_t> cx_vec;
	typedef arma::Mat<complex_t> cx_mat;

	typedef unsigned int index_t;
	typedef arma::Col<index_t> index_vec;

	typedef std::pair<index_t, index_t> index_pair_t;
	typedef std::vector<index_pair_t> index_pair_vec;

    inline vec make_vec(const value_t* beg, int length)
    {
		BOOST_ASSERT(length >= 0);
		return vec(beg, length);
	}

    inline vec make_vec(const value_t* beg, const value_t* end)
    {
		BOOST_ASSERT(end-beg >= 0);
		return make_vec(beg, end-beg);
	}

    inline vec make_vec(const std::vector<value_t>& source)
    {
		return vec(source);
	}

    inline vec make_vec(std::vector<value_t>&& source)
    {
		return vec(std::move(source));
	}

    inline const vec& make_vec(const vec& source)
    {
        return source;
    }

    inline vec& make_vec(vec& source)
    {
        return source;
    }
}

#endif // GLOBAL_H__

