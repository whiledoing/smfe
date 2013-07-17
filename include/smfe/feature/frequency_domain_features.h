/**
* @file frequency_domain_features.h
* @brief 计算频率域特征
* @author whiledoing (lovingwhile@gmail.com)
* @date 2013-07-17
*
* 主要使用arma::fft进行快速傅里叶变换
*/

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
/**
* @defgroup frefeatures frequency-domain-features
*
* 计算频率域的特征
*
* @{
*/

using arma::fft;
using arma::ifft;

/** 描述<b>频率-幅度</b>信息的数据结构 */
struct FrequencyMagnitude {
    FrequencyMagnitude(value_t f = 0.0, value_t m = 0.0) : fre(f), mag(m) {}

    value_t fre;    /**< 频率 */
    value_t	mag;    /**< 幅度 */

    friend inline bool operator<(const FrequencyMagnitude& lhs, const FrequencyMagnitude& rhs) {
        return lhs.mag < rhs.mag;
    }

    friend inline bool operator>(const FrequencyMagnitude& lhs, const FrequencyMagnitude& rhs) {
        return lhs.mag >= rhs.mag;
    }

    friend inline bool operator==(const FrequencyMagnitude& lhs, const FrequencyMagnitude& rhs) {
        return abs(lhs.mag - rhs.mag) < 1e-9 && abs(lhs.fre - rhs.fre) < 1e-9;
    }

    friend inline bool operator!=(const FrequencyMagnitude& lhs, const FrequencyMagnitude& rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const FrequencyMagnitude& fm) {
        os << "Frequency : " << fm.fre << "Magnitude : " << fm.mag << std::endl;
        return os;
    }
};

/** 保存FrequencyMagnitude的容器 */
typedef std::vector<FrequencyMagnitude> fm_vec;

/**
 * 根据原始信号计算频谱
 */
cx_vec fft(const vec& source);

/**
* @brief 根据原始信号得到<b>频率-幅值</b>信息
*
* @param source 原始信号
* @param fs 采样频率 (单位s)
*
* @return 返回保存到<b>频率-幅值</b>信息的向量
*/
fm_vec frequency_magnitude_vec(const vec& source, value_t fs);

/**
* @brief 根据频谱信息得到<b>频率-幅值</b>信息
*
* @param spectrum 原始信号计算得到的频率
* @param fs 采样频率 (单位s)
*
* @return 返回保存到<b>频率-幅值</b>向量 @sa fm_vec @sa FrequencyMagnitude
*/
fm_vec frequency_magnitude_vec(const cx_vec& spectrum, value_t fs);

/**
* 得到排序后的<b>频率-幅值</b>向量
*
* @note 排序按照幅值从大到小的顺序排序
*
* @sa frequency_magnitude_vec
*/
fm_vec sorted_frequency_magnitude_vec(const vec& spectrum, value_t fs);
fm_vec sorted_frequency_magnitude_vec(const cx_vec& spectrum, value_t fs);

/**
* 得到最大幅值的频率
*
* @note 输入的<b>频率-幅值</b>向量是拍过序的, @sa sorted_frequency_magnitude_vec
*/
value_t principal_frequency(const fm_vec& fm_vector);

/**
* 得到幅值中间大小频率
*
* @note 输入的<b>频率-幅值</b>向量是拍过序的, @sa sorted_frequency_magnitude_vec
*/
value_t median_frequency(const fm_vec& fm_vector);

/**
* 得到1/4幅值大小频率
*
* @note 输入的<b>频率-幅值</b>向量是拍过序的, @sa sorted_frequency_magnitude_vec
*/
value_t first_quater_frequency(const fm_vec& fm_vector);

/**
* 得到3/4幅值大小频率
*
* @note 输入的<b>频率-幅值</b>向量是拍过序的, @sa sorted_frequency_magnitude_vec
*/
value_t third_quater_frequency(const fm_vec& fm_vector);

/**
* 得到前n个最大幅值的频率
*
* @note 输入的<b>频率-幅值</b>向量是拍过序的, @sa sorted_frequency_magnitude_vec
*/
vec first_n_frequency(const fm_vec& fm_vector, int n);

/**
* @brief 得到频谱的能量
*
* 所有幅度数值的平方和
*
* @param fm_vector 保存的<b>频率-幅值</b>向量
* @note 输入数据不需要有序
*/
value_t frequency_energy(const fm_vec& fm_vector);

/**
* @brief 计算频率的信息熵
*
* 计算过程:
*
* 1.   将数据按照幅值的范围划分为 \c range_num 个区间
* 2.   统计每一个幅值区间下频率的个数,除以总个数得到该区间概率pi
* 3.   计算信息熵 = sum(pi * log(pi))
*
* @param fm_vector 保存的<b>频率-幅值</b>向量
* @param range_num 数据划分区间的大小
*
* @return 信息熵
*/
value_t frequency_entropy(const fm_vec& fm_vector, int range_num = 8);

/** @}*/
}

#endif // FREQUENCY_DOMAIN_FEATURES_H__

/**
* @example test_frequency_domain_features.cpp
* An example for current module @ref frefeatures
*/

