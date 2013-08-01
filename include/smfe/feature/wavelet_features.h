/**
 * @file wavelet_features.h
 * @brief ����С���任�������
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
 * С�������������
 *
 * ��Ҫʹ�õ��ĵ�������Ϊ:
 *
 * 1.   [wavelet1d](https://code.google.com/p/wavelet1d/)
 * 2.   [fftw](http://www.fftw.org/)
 *
 * ˵��:
 *
 * 1.   ��ɢС���任���Ϊdwt
 * 2.   ������ɢС���任�Ĺ�����, ��Ҫ�ƶ��任С��������, ����ʹ�õ���haar
 * С��, ��[Daubechies Wavelet](https://zh.wikipedia.org/wiki/%E5%A4%9A%E8%B4%9D%E8%A5%BF%E5%B0%8F%E6%B3%A2)С��
 * 3.   ��ǰ֧�ֵ�С������������:
 *
 * haar, db1, db2, db3, db4, db5, db6, db7, db8, db9, db10, db11, db12, db13, db14, db15
 * bior1.1, bio1.3, bior1.5, bior2.2, bior2.4,bior2.6,bior2.8 bior3.1, bior3.3, bior3.5, bior3.7, bior3.9, bior4 bior5.5, bior6.
 * coif1, coif2, coif3, coif4, coif5.
 *
 * db1��ʾһ��Daubechies Wavelet, db2��ʾ����, etc...
 *
 * ������Բο� http://code.google.com/p/wavelet1d/wiki/new1DDWTdemo
 *
 * @{ */

/** dwt ��ɢС���任�󱣴�����㼶С�����ݳ��ȵ��������� */
typedef std::vector<int> dwt_length_vec;
/** dwt ��ɢС���任�󱣴���ؼ�����Ϣ���������� */
typedef std::vector<double> dwt_flag_vec;

/**
 * @brief dwt ��ɢС���任
 *
 * @param time_signal ԭʼ�����ź�
 * @param wavelet_name  ����С��ʹ�õ�����
 * @param wavelet_level С���任�㼶
 *
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return �任��С����������
 */
vec dwt(const vec& time_signal, std::string wavelet_name, int wavelet_level);
/**
 * @brief dwt ��ɢС���任
 *
 * @param time_signal ԭʼ�����ź�
 * @param wavelet_name  ����С��ʹ�õ�����
 * @param wavelet_level С���任�㼶
 * @param[out] length ����С���任֮��ͬ�㼶С�����ݵĳ���
 *
 * ���赱ǰ�����wavelet_levelΪN, ��ô���ؽ�������ݰ������淽ʽ����:
 *
 *  [A D[N] D[N-1] D[N-2] ... D[1]]
 *
 * ����A��ʾapproximationϵ��, D[i]��ʾ��i���detailϵ��
 *
 * length����ĳ��ȾͶ�Ӧ: A, D[N], D[N-1] ... D[1]�����ݳ���
 *
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return �任��С����������
 */
vec dwt(const vec& time_signal, std::string wavelet_name, int wavelet_level, dwt_length_vec& length);
/**
 * @brief dwt ��ɢС���任
 *
 * @param time_signal ԭʼ�����ź�
 * @param wavelet_name  ����С��ʹ�õ�����
 * @param wavelet_level С���任�㼶
 * @param[out] length ����С���任֮��ͬ�㼶С�����ݵĳ���, ������������ķ�����Ҫ�õ��÷��ؽ��
 *
 * ���赱ǰ�����wavelet_levelΪN, ��ô���ؽ�������ݰ������淽ʽ����:
 *
 *  [A D[N] D[N-1] D[N-2] ... D[1]]
 *
 * ����A��ʾapproximationϵ��, D[i]��ʾ��i���detailϵ��
 *
 * length����ĳ��ȾͶ�Ӧ: A, D[N], D[N-1] ... D[1]�����ݳ���
 *
 * @param[out] flag ����С���任֮��Ķ��������Ϣ, ʹ��idwt��ʱ��û�õ� @sa idwt
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return �任��С����������
 */
vec dwt(const vec& time_signal, std::string wavelet_name, int wavelet_level, dwt_length_vec& length, dwt_flag_vec& flag);

/**
 * @brief idwt ��ɢС��������
 *
 * @param wavelet_signal    ԭʼ�����ź�
 * @param wavelet_name  С������
 * @param wavelet_level С���任�㼶
 * @param length    dwt�任֮�󱣴��С���任�����㼶���ݳ��� @sa dwt
 * @param flag dwt�任֮�󱣴��С���任��������Ϣ @sa dwt
 *
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return ������֮���ԭʼʱ���ź�
 */
vec idwt(const vec& wavelet_signal, std::string wavelet_name, int wavelet_level, const dwt_length_vec& length, const dwt_flag_vec& flag);

/**
 * @brief dwt_approximation_coeff �õ���ɢС���任֮��approximationϵ��
 *
 * @param time_signal ԭʼ�����ź�
 * @param wavelet_name  С������
 * @param wavelet_level С���任�㼶
 *
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return approximationϵ��
 */
vec dwt_approximation_coeff(const vec& time_signal, std::string wavelet_name, int wavelet_level);
/**
 * @brief dwt_approximation_coeff �õ�����С���ջ�֮��approximationϵ��
 *
 * @param wavelet_signal    dwt�任֮���ź� @sa dwt
 * @param length    dwt�任֮�󱣴�С���任�㼶������������ @sa dwt
 *
 * @return approximationϵ��
 */
vec dwt_approximation_coeff(const vec& wavelet_signal, const dwt_length_vec& length);

/**
 * @brief dwt_detail_coeff С���仯֮���detailϵ��
 *
 * @param time_signal ԭʼ�����ź�
 * @param wavelet_name  С������
 * @param wavelet_level С���任�㼶
 * @param detail_coeff_level detailϵ���Ĳ㼶
 *
 * @note �õ���detail�㼶ϵ��ȡֵ��Χ [1, wavlet_level]
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return ��detail_coeff_level�㼶�µ�detailϵ��
 */
vec dwt_detail_coeff(const vec& time_signal, std::string wavelet_name, int wavelet_level, int detail_coeff_level);
vec dwt_detail_coeff(const vec& wavelet_signal, const dwt_length_vec& length, int detail_coeff_level);

/**
 * @brief dwt_detail_coeff_of_range �õ�һ�β㼶�����ڵ�detailϵ��
 *
 * @param time_signal ԭʼ�����ź�
 * @param wavelet_name С������
 * @param wavelet_level С���任�㼶
 * @param detail_coeff_start_level ��ʼ�㼶
 * @param detail_coeff_end_level �����㼶
 *
 * @note �õ��㼶��Χ�������, �ҿ����� [detail_coeff_start_level, detail_coeff_end_level)
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return 
 */
std::vector<vec> dwt_detail_coeff_of_range(const vec& time_signal,
        std::string wavelet_name, int wavelet_level, int detail_coeff_start_level, int detail_coeff_end_level);
std::vector<vec> dwt_detail_coeff_of_range(const vec& wavelet_signal,
        const dwt_length_vec& length, int detail_coeff_start_level, int detail_coeff_end_level);

/**
 * @brief dwt_energy С���任detailϵ��������
 *
 * @param time_signal ԭʼ�����ź�
 * @param wavelet_name С������
 * @param wavelet_level С���任�㼶
 * @param detail_coeff_level detail�Ĳ㼶
 *
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return ��detail_coeff_level�㼶��ϵ������
 */
value_t dwt_energy(const vec& time_signal, std::string wavelet_name, int wavelet_level, int detail_coeff_level);
value_t dwt_energy(const vec& wavelet_signal, const dwt_length_vec& length, int detail_coeff_level);

/**
 * @brief dwt_energy С���任detailϵ����root mean square
 *
 * @param time_signal ԭʼ�����ź�
 * @param wavelet_name С������
 * @param wavelet_level С���任�㼶
 * @param detail_coeff_level detail�Ĳ㼶
 *
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return ��detail_coeff_level�㼶��ϵ����rms
 */
value_t dwt_rms(const vec& time_signal, std::string wavelet_name, int wavelet_level, int detail_coeff_level);
value_t dwt_rms(const vec& wavelet_signal, const dwt_length_vec& length, int detail_coeff_level);

/**
 * @brief dwt_normised_energy_using_signal_energy ʹ��ԭʼ�źŵ�������С���任���������й�һ������
 *
 * ����������:
 *
 *  <<Classification of waist-acceleration signals in a continuouswalking record>>
 *
 * ���������й�һ��������Եõ������бȽ��Ե���������.
 *
 * @param time_signal ԭʼ�����ź�
 * @param wavelet_name С������
 * @param wavelet_level С���任�㼶
 * @param detail_coeff_level detail�Ĳ㼶
 *
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
 *
 * @return ��һ��֮�������
 */
value_t dwt_normised_energy_using_signal_energy(const vec& time_signal,
        std::string wavelet_name, int wavelet_level, int detail_coeff_level);
/**
 * @brief dwt_normised_energy_using_signal_energy ʹ��ԭʼ�źŵ�������С���任���������й�һ������
 *
 * @param time_signal_energy ԭʼʱ���ź����� @sa energy
 * @param wavelet_signal ʹ��dwt����֮���С������ @sa dwt
 * @param length    dwt�任֮�󱣴��С���任�����㼶���ݳ��� @sa dwt
 * @param detail_coeff_level detail�Ĳ㼶
 *
 * @note С���任�㼶�����Դ��� \f$(int)(log_2^{N}) - 2\f$, ����N��ʾ���ݵĳ���
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
