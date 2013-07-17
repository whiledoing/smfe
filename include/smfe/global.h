/**
 * @file global.h
 * @brief 计算特征库的所有基本类型和所有基本方法
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
 * 保存计算特征全局的数据结构和方法
 * 
 * @{
 */

typedef double value_t; /**< 信号数据的基本类型 */

typedef arma::Mat<value_t> mat; /**< 保存二维数据的矩阵 */
typedef arma::Col<value_t> vec; /**< 保存一维数据的向量 */

typedef std::complex<value_t> complex_t; /**< 复数类型 */

typedef arma::Col<complex_t> cx_vec;   /**< 保存二维复数的矩阵 */ 
typedef arma::Mat<complex_t> cx_mat;   /**< 保存一维复数的向量 */

typedef unsigned int index_t;   /**< 索引的类型 */
typedef arma::Col<index_t> index_vec;   /** < 保存索引的数组 */

typedef std::pair<index_t, index_t> index_pair_t;   /**< 保存一对索引区间的结构 */
typedef std::vector<index_pair_t> index_pair_vec;   /**< 保存索引区间的向量结构 */

/**
 * make_vec方法为建立vec数据结构的适配器方法
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
 * make_abs是将一个向量转化为绝对值的向量
 */
template<typename ContainterType>
ContainterType make_abs(const ContainterType& source)
{
    ContainterType res(source.size());
    for(size_t i = 0u; i < source.size(); ++i)
        res[i] = abs(source[i]);
    return res;
}

template<typename ContainterType>
ContainterType make_abs(ContainterType& source)
{
    for(size_t i = 0u; i < source.size(); ++i)
        source[i] = abs(source[i]);
    return source;
}

/**
 * make_sub_range将一个向量的区间数据提取出来
 *
 * @note 区间范围为[beg, end], 两边都是闭区间
 */
template<typename ContainterType>
ContainterType make_sub_range(const ContainterType& data, int beg, int end)
{
	BOOST_ASSERT(beg >= 0 && end < data.size());

    ContainterType res(end-beg+1);
    for(int i = 0; i < res.size(); ++i)
        res[i] = data[beg+i];

    return res;
}

/**
 * 检查向量数据类型的辅助方法
 */
template<typename ContainterType>
void CHECK_VALUE_TYPE(const ContainterType& c)
{
    BOOST_STATIC_ASSERT((boost::is_same<typename ContainterType::value_type, value_t>::value));
}

/** @}*/
}

#endif // GLOBAL_H__

