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

    template<typename T>
    inline arma::Col<T> make_vec(const T* beg, int length)
    {
		BOOST_ASSERT(length >= 0);
		return arma::Col<T>(beg, length);
	}

    template<typename T>
    inline arma::Col<T> make_vec(const T* beg, const T* end)
    {
		return make_vec(beg, end-beg);
	}

    template<typename T>
    inline arma::Col<T> make_vec(const std::vector<T>& source)
    {
		return arma::Col<T>(source);
	}

    template<typename T>
    inline arma::Col<T> make_vec(std::vector<T>&& source)
    {
		return arma::Col<T>(std::move(source));
	}

    template<typename T>
    inline const arma::Col<T>& make_vec(const arma::Col<T>& source)
    {
        return source;
    }

    template<typename T>
    inline arma::Col<T>& make_vec(arma::Col<T>& source)
    {
        return source;
    }
}

#endif // GLOBAL_H__

