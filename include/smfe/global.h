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
#include <armadillo>

namespace smfe
{
	typedef double value_t;

	typedef arma::Mat<value_t> mat;
	typedef arma::Col<value_t> vec;

	typedef std::complex<value_t> complex_t;

	typedef arma::Col<complex_t> cx_vec;
	typedef arma::Mat<complex_t> cx_mat;
}

#endif // GLOBAL_H__

