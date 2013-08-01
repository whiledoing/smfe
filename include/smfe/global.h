/**
 * @file global.h
 * @brief ��������������л������ͺ����л�������
 * @author whiledoing (lovingwhile@gmail.com)
 * @date 2013-07-17
 */

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
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <armadillo>

#ifdef _MSC_VER
#pragma warning(disable:4215 4018)
#endif

namespace smfe
{
/**
 * @defgroup global global
 * 
 * �����������ȫ�ֵ����ݽṹ�ͷ���
 * 
 * @{
 */

typedef double value_t; /**< �ź����ݵĻ������� */

typedef arma::Mat<value_t> mat; /**< �����ά���ݵľ��� */
typedef arma::Col<value_t> vec; /**< ����һά���ݵ����� */

typedef std::complex<value_t> complex_t; /**< �������� */

typedef arma::Col<complex_t> cx_vec;   /**< �����ά�����ľ��� */ 
typedef arma::Mat<complex_t> cx_mat;   /**< ����һά���������� */

typedef unsigned int index_t;   /**< ���������� */
typedef arma::Col<index_t> index_vec;   /** < �������������� */

typedef std::pair<index_t, index_t> index_pair_t;   /**< ����һ����������Ľṹ */
typedef std::vector<index_pair_t> index_pair_vec;   /**< ������������������ṹ */

class SMFEException : public std::exception
{
public:
    SMFEException(const std::string& error) : std::exception(("[SMFE Error] " + error).c_str()) {}
};

/**
 * make_vec����Ϊ����vec���ݽṹ������������
 */
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

/**
 * make_abs�ǽ�һ������ת��Ϊ����ֵ������
 */
inline vec make_abs(const vec& source)
{
    vec res(source.size());
    for(size_t i = 0u; i < source.size(); ++i)
        res[i] = abs(source[i]);
    return res;
}

inline vec make_abs(vec& source)
{
    for(size_t i = 0u; i < source.size(); ++i)
        source[i] = abs(source[i]);
    return source;
}

/**
 * make_sub_range��һ������������������ȡ����
 *
 * @note ���䷶ΧΪ[beg, end)
 */
inline vec make_sub_range(const vec& data, int beg, int end)
{
	BOOST_ASSERT(beg >= 0 && end <= data.size() && beg <= end);

    vec res(end-beg);
    for(int i = 0; i < res.size(); ++i)
        res[i] = data[beg+i];

    return res;
}

/**
 * ��������������͵ĸ�������
 */
inline void CHECK_VALUE_TYPE(const vec& c)
{
    BOOST_STATIC_ASSERT((boost::is_same<typename vec::value_type, value_t>::value));
}

/** @}*/
}

#endif // GLOBAL_H__

/**
@mainpage sensor motion feature extractor
## Introduction

�ü������Ҫ������ȡ�˶��������źŵ�����.

һ�����͵��˶�����������������Ҫ����:

1.  ���ٶȴ�����
2.  ��ͨ������
3.  �����Ǵ�����

�������������������Ŀ��Ƶ�Ԫһ��Ҳ������IMU(inertia measurement unit)��Ԫ.

�����������Ҫ������������

1.  �˶����л�������(���ٶ�,�ٶ�,λ��,��ת�Ƕ�,���ٶȵ�)
2.  ͳ������
3.  ʱ������
4.  Ƶ������
5.  ʱ��-Ƶ������ (TODO)

## ��װ

�������������漸����������:

1.  [boost](http://www.boost.org/) ��Ҫ������ģ��Ϊ `unit_test filesystem property_tree accumulators`
2.  [armadillo](http://arma.sourceforge.net/) ���Դ���C++�����
3.  [aquila](http://aquila-dsp.org/) �źŴ���C++��

`armadillo`��`aquila`�Ѿ������(visual C++ 2012)��������`3rd`Ŀ¼��,Ҳ�����Լ����뽫����õĽ�����õ�`3rd`Ŀ¼�м���

��Ҫע�����,aquila����õ�library��Ҫ��Ϊ���µ�����(���Բο�`cmake/modules/support_aquila.cmake`ģ��):

1.  debugģʽ��lib: Aquila_debug.lib
2.  relaseģʽ��lib: Aquila_release.lib

boost�����������취:

1.  ����`BOOST_ROOT`��������
2.  �����ڵ���cmake��ʱ������`BOOST_DIR`����ֵ,����`cmake ..  -DCMAKE_DIR="F/lib/boost/"`

���úõ�������֮��,��������������뱾��:

    1.  mkdir build
    2.  cd build && cmake ..
    3.  make/nmake

## ˵��

1.  ����Ļ������Ͷ�����`include/smfe/global.h`�ļ���

2.  ���Բο�`test`Ŀ¼�µĲ��Դ�����Ϊexample

## TODO

1.  ʱ��-Ƶ������
2.  �������źŵ����������ȫ������
*/
