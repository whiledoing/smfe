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

/** 描述<b>频率-幅度</b>信息的数据结构 

使用 `frequency_magnitude_vec` 或者 `sorted_frequency_magnitude_vec` 得到信号的<b>频率-幅值</b>信息.

频率-幅值对应了经过fft变换之后的所有频率(单位hz)和频率幅值的信息.

考虑信号:

	f(t) = 10 * f( 2*pi * 1000 * t) + 3 * f(2*pi * 2000 * t);

如果使用fs = 6000来采样, 那么得到的频率幅值信息最大的两个就是:

	1.  mag : 10  fre : 1000
	2.  mag : 3   fre : 2000

可以得到fm_vec的操作API:

1.	`frequency_magnitude_vec` 接口得到的结果按照<b>频率从小到大顺序存放</b>
2.	`sorted_frequency_magnitude_vec` 接口得到结果按照<b>幅值从大到小顺序存放</b>

得到的fm_vec具有如下特点, 假设信号长度为n(n最好为2的倍数), 采样频率为 fs :

1.	fm_vec的长度为<b>n/2 + 1</b>.
2.	fm_vec中频率的最小值是0, 表示直流分量, 最大值为 `fs/2`, 每一个相邻频率的大小间隔为 `fs/size`, 这也就是为什么长度为<b>n/2 + 1</b>的原因.

另外提供了从fm_vec中得到其对应频率和幅值分量的便捷访问API:

1.	`fm_get_fre` 得到fm_vec中的频率分量
2.	`fm_get_mag` 得到fm_vec中的幅值分量

* 
*/

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
        os << "Frequency : " << fm.fre << " Magnitude : " << fm.mag;
        return os;
    }
};

/** 保存FrequencyMagnitude的容器 */
typedef std::vector<FrequencyMagnitude> fm_vec;

/**
 * 根据原始信号计算频谱
 */
cx_vec smfe_fft(const vec& source);

/**
 * 根据频谱计算计算原始信号
 */
vec smfe_ifft(const cx_vec& source);

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
 *	得到当前<b>频率-幅值</b>向量中的频率分量, 并且pack为一个向量
 */
vec fm_get_fre(const fm_vec& fm_vector);

/**
 *	得到当前<b>频率-幅值</b>向量中的幅值分量, 并且pack为一个向量
 */
vec fm_get_mag(const fm_vec& fm_vector);

/**
* 得到排序后的<b>频率-幅值</b>向量
*
* @note 排序按照幅值从大到小的顺序排序
*
* @sa frequency_magnitude_vec
*/
fm_vec sorted_frequency_magnitude_vec(const vec& source, value_t fs);
fm_vec sorted_frequency_magnitude_vec(const cx_vec& spectrum, value_t fs);

/**
* 得到最大幅值的频率
*
* @note 输入的<b>频率-幅值</b>向量是排过序的, @sa sorted_frequency_magnitude_vec
*/
value_t principal_frequency(const fm_vec& fm_vector);

/**
* 得到幅值中间大小频率
*
* @note 输入的<b>频率-幅值</b>向量是排过序的, @sa sorted_frequency_magnitude_vec
*/
value_t median_frequency(const fm_vec& fm_vector);

/**
* 得到1/4幅值大小频率
*
* @note 输入的<b>频率-幅值</b>向量是排过序的, @sa sorted_frequency_magnitude_vec
*/
value_t first_quater_frequency(const fm_vec& fm_vector);

/**
* 得到3/4幅值大小频率
*
* @note 输入的<b>频率-幅值</b>向量是排过序的, @sa sorted_frequency_magnitude_vec
*/
value_t third_quater_frequency(const fm_vec& fm_vector);

/**
* 得到前n个最大幅值的频率
*
* @note 输入的<b>频率-幅值</b>向量是排过序的, @sa sorted_frequency_magnitude_vec
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
* @brief fft分解后所有频率幅值的信息熵, 表示分解后信号幅值分布均匀程度 @sa entropy
*
* @param fm_vector 保存的<b>频率-幅值</b>向量
* @param nbins 数据划分区间的大小
*
* @note 输入的<b>频率-幅值</b>向量是不要求有序 (当然有序更好)
*/
value_t frequency_domain_entropy(const fm_vec& fm_vector, int nbins);

/**
* @brief fft分解后所有频率幅值的信息熵, 表示分解后信号幅值分布均匀程度 @sa entropy
*
* @param magnitude_vector 保存所有幅值的向量
* @param nbins 数据划分区间的大小
*/
value_t frequency_domain_entropy(const vec& magnitude_vector, int nbins);

/** @}*/
}

#endif // FREQUENCY_DOMAIN_FEATURES_H__

/**
* @example test_frequency_domain_features.cpp
* An example for current module @ref frefeatures
*/

