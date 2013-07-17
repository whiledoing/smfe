/**
* @file frequency_domain_features.h
* @brief ����Ƶ��������
* @author whiledoing (lovingwhile@gmail.com)
* @date 2013-07-17
*
* ��Ҫʹ��arma::fft���п��ٸ���Ҷ�任
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
* ����Ƶ���������
*
* @{
*/

using arma::fft;
using arma::ifft;

/** ����<b>Ƶ��-����</b>��Ϣ�����ݽṹ */
struct FrequencyMagnitude {
    FrequencyMagnitude(value_t f = 0.0, value_t m = 0.0) : fre(f), mag(m) {}

    value_t fre;    /**< Ƶ�� */
    value_t	mag;    /**< ���� */

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

/** ����FrequencyMagnitude������ */
typedef std::vector<FrequencyMagnitude> fm_vec;

/**
 * ����ԭʼ�źż���Ƶ��
 */
cx_vec fft(const vec& source);

/**
* @brief ����ԭʼ�źŵõ�<b>Ƶ��-��ֵ</b>��Ϣ
*
* @param source ԭʼ�ź�
* @param fs ����Ƶ�� (��λs)
*
* @return ���ر��浽<b>Ƶ��-��ֵ</b>��Ϣ������
*/
fm_vec frequency_magnitude_vec(const vec& source, value_t fs);

/**
* @brief ����Ƶ����Ϣ�õ�<b>Ƶ��-��ֵ</b>��Ϣ
*
* @param spectrum ԭʼ�źż���õ���Ƶ��
* @param fs ����Ƶ�� (��λs)
*
* @return ���ر��浽<b>Ƶ��-��ֵ</b>���� @sa fm_vec @sa FrequencyMagnitude
*/
fm_vec frequency_magnitude_vec(const cx_vec& spectrum, value_t fs);

/**
* �õ�������<b>Ƶ��-��ֵ</b>����
*
* @note �����շ�ֵ�Ӵ�С��˳������
*
* @sa frequency_magnitude_vec
*/
fm_vec sorted_frequency_magnitude_vec(const vec& spectrum, value_t fs);
fm_vec sorted_frequency_magnitude_vec(const cx_vec& spectrum, value_t fs);

/**
* �õ�����ֵ��Ƶ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ĺ����, @sa sorted_frequency_magnitude_vec
*/
value_t principal_frequency(const fm_vec& fm_vector);

/**
* �õ���ֵ�м��СƵ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ĺ����, @sa sorted_frequency_magnitude_vec
*/
value_t median_frequency(const fm_vec& fm_vector);

/**
* �õ�1/4��ֵ��СƵ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ĺ����, @sa sorted_frequency_magnitude_vec
*/
value_t first_quater_frequency(const fm_vec& fm_vector);

/**
* �õ�3/4��ֵ��СƵ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ĺ����, @sa sorted_frequency_magnitude_vec
*/
value_t third_quater_frequency(const fm_vec& fm_vector);

/**
* �õ�ǰn������ֵ��Ƶ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ĺ����, @sa sorted_frequency_magnitude_vec
*/
vec first_n_frequency(const fm_vec& fm_vector, int n);

/**
* @brief �õ�Ƶ�׵�����
*
* ���з�����ֵ��ƽ����
*
* @param fm_vector �����<b>Ƶ��-��ֵ</b>����
* @note �������ݲ���Ҫ����
*/
value_t frequency_energy(const fm_vec& fm_vector);

/**
* @brief ����Ƶ�ʵ���Ϣ��
*
* �������:
*
* 1.   �����ݰ��շ�ֵ�ķ�Χ����Ϊ \c range_num ������
* 2.   ͳ��ÿһ����ֵ������Ƶ�ʵĸ���,�����ܸ����õ����������pi
* 3.   ������Ϣ�� = sum(pi * log(pi))
*
* @param fm_vector �����<b>Ƶ��-��ֵ</b>����
* @param range_num ���ݻ�������Ĵ�С
*
* @return ��Ϣ��
*/
value_t frequency_entropy(const fm_vec& fm_vector, int range_num = 8);

/** @}*/
}

#endif // FREQUENCY_DOMAIN_FEATURES_H__

/**
* @example test_frequency_domain_features.cpp
* An example for current module @ref frefeatures
*/

