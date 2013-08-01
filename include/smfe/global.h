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

class SMFEException : public std::exception
{
public:
    SMFEException(const std::string& error) : std::exception(("[SMFE Error] " + error).c_str()) {}
};

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
 * make_sub_range将一个向量的区间数据提取出来
 *
 * @note 区间范围为[beg, end)
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
 * 检查向量数据类型的辅助方法
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

该计算库主要用来提取运动传感器信号的特征.

一个典型的运动传感器包含三个主要部分:

1.  加速度传感器
2.  磁通传感器
3.  陀螺仪传感器

包含整个三个传感器的控制单元一般也被叫做IMU(inertia measurement unit)单元.

计算的特征主要包含几个部分

1.  运动传感基本特征(加速度,速度,位移,旋转角度,角速度等)
2.  统计特征
3.  时域特征
4.  频域特征
5.  时间-频率特征 (TODO)

## 安装

本库依赖于下面几个第三方库:

1.  [boost](http://www.boost.org/) 主要几个子模块为 `unit_test filesystem property_tree accumulators`
2.  [armadillo](http://arma.sourceforge.net/) 线性代数C++计算库
3.  [aquila](http://aquila-dsp.org/) 信号处理C++库

`armadillo`和`aquila`已经编译好(visual C++ 2012)放置在了`3rd`目录中,也可以自己编译将编译好的结果放置到`3rd`目录中即可

需要注意的是,aquila编译好的library需要改为如下的命名(可以参考`cmake/modules/support_aquila.cmake`模块):

1.  debug模式的lib: Aquila_debug.lib
2.  relase模式的lib: Aquila_release.lib

boost查找有两个办法:

1.  设置`BOOST_ROOT`环境变量
2.  或者在调用cmake的时候设置`BOOST_DIR`的数值,比如`cmake ..  -DCMAKE_DIR="F/lib/boost/"`

配置好第三方库之后,调用下面命令编译本库:

    1.  mkdir build
    2.  cd build && cmake ..
    3.  make/nmake

## 说明

1.  本库的基本类型定义在`include/smfe/global.h`文件中

2.  可以参考`test`目录下的测试代码作为example

## TODO

1.  时间-频率特征
2.  将计算信号的特征变得完全可配置
*/
