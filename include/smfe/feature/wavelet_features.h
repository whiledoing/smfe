#ifdef _MSC_VER
#pragma once
#endif

#ifndef WAVELET_FEATURES_H__
#define WAVELET_FEATURES_H__

#include <smfe/global.h>
#include <string>
#include <vector>

void test_func();
namespace smfe
{

enum SignalType
{
	TIME_SIGNAL,
	WAVELET_SIGNAL
};

typedef std::vector<int> dwt_length_vec;
typedef std::vector<double> dwt_flag_vec;

/**
 * @brief dwt 离散小波变换
 *
 * @param data
 * @param wavelet_name
 * @param level
 *
 * @note 数据data长度必须要大于 `2^level`, 否则无法计算到指定的level层.
 * @return
 */
vec dwt(const vec& time_signal, std::string wavelet_name, int wavlet_level);
vec dwt(const vec& time_signal, std::string wavelet_name, int wavlet_level, dwt_length_vec& length);
vec dwt(const vec& time_signal, std::string wavelet_name, int wavlet_level, dwt_length_vec& length, dwt_flag_vec& flag);

vec idwt(const vec& wavelet_signal, std::string wavelet_name, int wavelet_level, const dwt_length_vec& length, const dwt_flag_vec& flag);

vec dwt_approximation_coeff(const vec& time_signal, std::string wavelet_name, int wavelet_level);
vec dwt_approximation_coeff(const vec& wavelet_signal, const dwt_length_vec& length);

vec dwt_detail_coeff(const vec& time_signal, std::string wavelet_name, int wavelet_level, int detail_coeff_level);
vec dwt_detail_coeff(const vec& wavelet_signal, const dwt_length_vec& length, int detail_coeff_level);

}

#endif // WAVELET_FEATURES_H__

