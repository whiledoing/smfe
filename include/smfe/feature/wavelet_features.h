/**
 * @file wavelet_features.h
 * @brief 计算小波变换相关特征
 * @author whiledoing (lovingwhile@gmail.com)
 * @date 2013-08-02
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef WAVELET_FEATURES_H__
#define WAVELET_FEATURES_H__

#include <smfe/global.h>
#include <string>
#include <vector>

namespace smfe
{
/**
 * @defgroup wavletfeatures wavelet-features
 *
 * 小波计算相关特征
 *
 * 主要使用到的第三方库为:
 *
 * 1.   [wavelet1d](https://code.google.com/p/wavelet1d/)
 * 2.   [fftw](http://www.fftw.org/)
 *
 * 说明:
 *
 * 1.   离散小波变换简称为dwt
 * 2.   计算离散小波变换的过程中, 需要制定变换小波的类型, 经常使用的是haar
 * 小波, 和[Daubechies Wavelet](https://zh.wikipedia.org/wiki/%E5%A4%9A%E8%B4%9D%E8%A5%BF%E5%B0%8F%E6%B3%A2)小波
 * 3.   当前支持的小波类型名称有:
 *
 * haar, db1, db2, db3, db4, db5, db6, db7, db8, db9, db10, db11, db12, db13, db14, db15
 * bior1.1, bio1.3, bior1.5, bior2.2, bior2.4,bior2.6,bior2.8 bior3.1, bior3.3, bior3.5, bior3.7, bior3.9, bior4 bior5.5, bior6.
 * coif1, coif2, coif3, coif4, coif5.
 *
 * db1表示一阶Daubechies Wavelet, db2表示二阶, etc...
 *
 * 具体可以参考 http://code.google.com/p/wavelet1d/wiki/new1DDWTdemo
 *
 * @{ */

/** dwt 离散小波变换后保存各个层级小波数据长度的向量类型 */
typedef std::vector<int> dwt_length_vec;
/** dwt 离散小波变换后保存相关计算信息的向量类型 */
typedef std::vector<double> dwt_flag_vec;

/**
 * @brief dwt 离散小波变换
 *
 * @param time_signal 原始输入信号
 * @param wavelet_name  计算小波使用的名称
 * @param wavelet_level 小波变换层级
 *
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return 变换后小波数据向量
 */
vec dwt(const vec& time_signal, std::string wavelet_name, int wavelet_level);
/**
 * @brief dwt 离散小波变换
 *
 * @param time_signal 原始输入信号
 * @param wavelet_name  计算小波使用的名称
 * @param wavelet_level 小波变换层级
 * @param[out] length 保存小波变换之后不同层级小波数据的长度
 *
 * 假设当前计算的wavelet_level为N, 那么返回结果中数据按照下面方式放置:
 *
 *  [A D[N] D[N-1] D[N-2] ... D[1]]
 *
 * 其中A表示approximation系数, D[i]表示第i层的detail系数
 *
 * length保存的长度就对应: A, D[N], D[N-1] ... D[1]的数据长度
 *
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return 变换后小波数据向量
 */
vec dwt(const vec& time_signal, std::string wavelet_name, int wavelet_level, dwt_length_vec& length);
/**
 * @brief dwt 离散小波变换
 *
 * @param time_signal 原始输入信号
 * @param wavelet_name  计算小波使用的名称
 * @param wavelet_level 小波变换层级
 * @param[out] length 保存小波变换之后不同层级小波数据的长度, 后面计算特征的方法需要用到该返回结果
 *
 * 假设当前计算的wavelet_level为N, 那么返回结果中数据按照下面方式放置:
 *
 *  [A D[N] D[N-1] D[N-2] ... D[1]]
 *
 * 其中A表示approximation系数, D[i]表示第i层的detail系数
 *
 * length保存的长度就对应: A, D[N], D[N-1] ... D[1]的数据长度
 *
 * @param[out] flag 保存小波变换之后的额外计算信息, 使用idwt的时候没用到 @sa idwt
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return 变换后小波数据向量
 */
vec dwt(const vec& time_signal, std::string wavelet_name, int wavelet_level, dwt_length_vec& length, dwt_flag_vec& flag);

/**
 * @brief idwt 离散小波逆运算
 *
 * @param wavelet_signal    原始输入信号
 * @param wavelet_name  小波名称
 * @param wavelet_level 小波变换层级
 * @param length    dwt变换之后保存的小波变换各个层级数据长度 @sa dwt
 * @param flag dwt变换之后保存的小波变换计算结果信息 @sa dwt
 *
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return 逆运算之后的原始时域信号
 */
vec idwt(const vec& wavelet_signal, std::string wavelet_name, int wavelet_level, const dwt_length_vec& length, const dwt_flag_vec& flag);

/**
 * @brief dwt_approximation_coeff 得到离散小波变换之后approximation系数
 *
 * @param time_signal 原始输入信号
 * @param wavelet_name  小波名称
 * @param wavelet_level 小波变换层级
 *
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return approximation系数
 */
vec dwt_approximation_coeff(const vec& time_signal, std::string wavelet_name, int wavelet_level);
/**
 * @brief dwt_approximation_coeff 得到你算小波闭环之后approximation系数
 *
 * @param wavelet_signal    dwt变换之后信号 @sa dwt
 * @param length    dwt变换之后保存小波变换层级长度数据向量 @sa dwt
 *
 * @return approximation系数
 */
vec dwt_approximation_coeff(const vec& wavelet_signal, const dwt_length_vec& length);

/**
 * @brief dwt_detail_coeff 小波变化之后的detail系数
 *
 * @param time_signal 原始输入信号
 * @param wavelet_name  小波名称
 * @param wavelet_level 小波变换层级
 * @param detail_coeff_level detail系数的层级
 *
 * @note 得到的detail层级系数取值范围 [1, wavlet_level]
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return 在detail_coeff_level层级下的detail系数
 */
vec dwt_detail_coeff(const vec& time_signal, std::string wavelet_name, int wavelet_level, int detail_coeff_level);
vec dwt_detail_coeff(const vec& wavelet_signal, const dwt_length_vec& length, int detail_coeff_level);

/**
 * @brief dwt_detail_coeff_of_range 得到一段层级区域内的detail系数
 *
 * @param time_signal 原始输入信号
 * @param wavelet_name 小波名称
 * @param wavelet_level 小波变换层级
 * @param detail_coeff_start_level 开始层级
 * @param detail_coeff_end_level 结束层级
 *
 * @note 得到层级范围都是左闭, 右开区间 [detail_coeff_start_level, detail_coeff_end_level)
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return 
 */
std::vector<vec> dwt_detail_coeff_of_range(const vec& time_signal,
        std::string wavelet_name, int wavelet_level, int detail_coeff_start_level, int detail_coeff_end_level);
std::vector<vec> dwt_detail_coeff_of_range(const vec& wavelet_signal,
        const dwt_length_vec& length, int detail_coeff_start_level, int detail_coeff_end_level);

/**
 * @brief dwt_energy 小波变换detail系数的能量
 *
 * @param time_signal 原始输入信号
 * @param wavelet_name 小波名称
 * @param wavelet_level 小波变换层级
 * @param detail_coeff_level detail的层级
 *
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return 在detail_coeff_level层级上系数能量
 */
value_t dwt_energy(const vec& time_signal, std::string wavelet_name, int wavelet_level, int detail_coeff_level);
value_t dwt_energy(const vec& wavelet_signal, const dwt_length_vec& length, int detail_coeff_level);

/**
 * @brief dwt_energy 小波变换detail系数的root mean square
 *
 * @param time_signal 原始输入信号
 * @param wavelet_name 小波名称
 * @param wavelet_level 小波变换层级
 * @param detail_coeff_level detail的层级
 *
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return 在detail_coeff_level层级上系数的rms
 */
value_t dwt_rms(const vec& time_signal, std::string wavelet_name, int wavelet_level, int detail_coeff_level);
value_t dwt_rms(const vec& wavelet_signal, const dwt_length_vec& length, int detail_coeff_level);

/**
 * @brief dwt_normised_energy_using_signal_energy 使用原始信号的能量对小波变换的能量进行归一化处理
 *
 * 来自于论文:
 *
 *  <<Classification of waist-acceleration signals in a continuouswalking record>>
 *
 * 对能量进行归一化处理可以得到更加有比较性的能量特征.
 *
 * @param time_signal 原始输入信号
 * @param wavelet_name 小波名称
 * @param wavelet_level 小波变换层级
 * @param detail_coeff_level detail的层级
 *
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 *
 * @return 归一化之后的能量
 */
value_t dwt_normised_energy_using_signal_energy(const vec& time_signal,
        std::string wavelet_name, int wavelet_level, int detail_coeff_level);
/**
 * @brief dwt_normised_energy_using_signal_energy 使用原始信号的能量对小波变换的能量进行归一化处理
 *
 * @param time_signal_energy 原始时域信号能量 @sa energy
 * @param wavelet_signal 使用dwt计算之后的小波特征 @sa dwt
 * @param length    dwt变换之后保存的小波变换各个层级数据长度 @sa dwt
 * @param detail_coeff_level detail的层级
 *
 * @note 小波变换层级不可以大于 \f$(int)(log_2^{N}) - 2\f$, 其中N表示数据的长度
 * @return 
 */
value_t dwt_normised_energy_using_signal_energy(value_t time_signal_energy,
        const vec& wavelet_signal, const dwt_length_vec& length, int detail_coeff_level);

/** @} */

}

#endif // WAVELET_FEATURES_H__

/**
 * @example test_wavelet_features.cpp
 * An example for current module @ref wavletfeatures  
 */
