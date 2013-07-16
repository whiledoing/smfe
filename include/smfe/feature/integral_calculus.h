#ifdef _MSC_VER
	#pragma once
#endif

#ifndef INTEGRAL_CALCULUS_H__
#define INTEGRAL_CALCULUS_H__

#include "../global.h"
#include <boost/assert.hpp>

namespace smfe
{

/**
 * 计算离散数据的积分
 * 
 * 1.	输入数据必须是等间隔分布的,这里将间隔统一设置为单位1,根据计算需要不同的degree
 * 使用不同的数值积分算法.
 *	
 * 2.	不同的degree影响积分计算的最后几项.越高的degree需要计算的数据数目越多,比如
 * degree为3的时候,需要连续的三个数据计算出当前小区域的面积.所以degree为3的时候,最后
 * 一个数据对应的积分区域没有被计算.
 * 
 * 可以参考:http://en.wikipedia.org/wiki/Newton%E2%80%93Cotes_formulas
 *
 * @param data 输入数据
 * @param degree 计算需要的阶数
 *
 * @pre degree的范围为[2,4]
 */
template<typename ContainterType>
value_t integration(ContainterType const& data, int degree = 2)
{
	CHECK_VALUE_TYPE(data);

	BOOST_ASSERT(degree >= 2 && degree <= 4);

    value_t sum = 0.0;

    for(size_t i = degree-1; i < data.size() - (degree-1); ++i)
        sum += data[i];

    if(degree == 2) {
        sum += (data[0] + data[data.size()-1])/2;
    }

    if(degree == 3) {
        sum += (data[0] + 5*data[1] + 5*data[data.size()-2] + data[data.size()-1]) / 6;
    }

    if(degree == 4) {
        sum += (data[0] + 4*data[1] + 7*data[2] + 7*data[data.size()-3] + 4*data[data.size()-2] + data[data.size()-1]) / 8;
    }

    return sum;
}

/**
 *	计算非分等间隔划分数据的积分
 *	
 *	1.	两个相邻离散数据的间隔有参数delta_vec给出
 *	2.	数据data[1]和data[0]之间的间隔为delta_vec[0],	data[2]和data[1]之间间隔为delta_vec[1],etc...
 *	3.	使用degree为2的积分算法
 *	
 *	@param data 被积分数据
 *	@param delta_vec 积分数据之间间隔
 *	
 *	@pre <strong class="paramname">data</strong>的数据长度比<strong class="paramname">delta_vec</strong>的长度大一
 */
template<typename ContainterType>
value_t integration_with_delta(ContainterType const& data, ContainterType const& delta_vec)
{
    CHECK_VALUE_TYPE(data);
    CHECK_VALUE_TYPE(delta_vec);

	BOOST_ASSERT(data.size() - 1 == delta_vec.size());

    value_t sum = 0.0;

    for(size_t i = 0u; i < data.size() - 1; ++i)
        sum += (data[i] + data[i+1]) / 2 * delta_vec[i];

    return sum;
}

}

#endif // INTEGRAL_CALCULUS_H__

