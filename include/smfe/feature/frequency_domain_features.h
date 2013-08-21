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

/** ����<b>Ƶ��-����</b>��Ϣ�����ݽṹ 

ʹ�� `frequency_magnitude_vec` ���� `sorted_frequency_magnitude_vec` �õ��źŵ�<b>Ƶ��-��ֵ</b>��Ϣ.

Ƶ��-��ֵ��Ӧ�˾���fft�任֮�������Ƶ��(��λhz)��Ƶ�ʷ�ֵ����Ϣ.

�����ź�:

	f(t) = 10 * f( 2*pi * 1000 * t) + 3 * f(2*pi * 2000 * t);

���ʹ��fs = 6000������, ��ô�õ���Ƶ�ʷ�ֵ��Ϣ������������:

	1.  mag : 10  fre : 1000
	2.  mag : 3   fre : 2000

���Եõ�fm_vec�Ĳ���API:

1.	`frequency_magnitude_vec` �ӿڵõ��Ľ������<b>Ƶ�ʴ�С����˳����</b>
2.	`sorted_frequency_magnitude_vec` �ӿڵõ��������<b>��ֵ�Ӵ�С˳����</b>

�õ���fm_vec���������ص�, �����źų���Ϊn(n���Ϊ2�ı���), ����Ƶ��Ϊ fs :

1.	fm_vec�ĳ���Ϊ<b>n/2 + 1</b>.
2.	fm_vec��Ƶ�ʵ���Сֵ��0, ��ʾֱ������, ���ֵΪ `fs/2`, ÿһ������Ƶ�ʵĴ�С���Ϊ `fs/size`, ��Ҳ����Ϊʲô����Ϊ<b>n/2 + 1</b>��ԭ��.

�����ṩ�˴�fm_vec�еõ����ӦƵ�ʺͷ�ֵ�����ı�ݷ���API:

1.	`fm_get_fre` �õ�fm_vec�е�Ƶ�ʷ���
2.	`fm_get_mag` �õ�fm_vec�еķ�ֵ����

* 
*/

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
        os << "Frequency : " << fm.fre << " Magnitude : " << fm.mag;
        return os;
    }
};

/** ����FrequencyMagnitude������ */
typedef std::vector<FrequencyMagnitude> fm_vec;

/**
 * ����ԭʼ�źż���Ƶ��
 */
cx_vec smfe_fft(const vec& source);

/**
 * ����Ƶ�׼������ԭʼ�ź�
 */
vec smfe_ifft(const cx_vec& source);

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
 *	�õ���ǰ<b>Ƶ��-��ֵ</b>�����е�Ƶ�ʷ���, ����packΪһ������
 */
vec fm_get_fre(const fm_vec& fm_vector);

/**
 *	�õ���ǰ<b>Ƶ��-��ֵ</b>�����еķ�ֵ����, ����packΪһ������
 */
vec fm_get_mag(const fm_vec& fm_vector);

/**
* �õ�������<b>Ƶ��-��ֵ</b>����
*
* @note �����շ�ֵ�Ӵ�С��˳������
*
* @sa frequency_magnitude_vec
*/
fm_vec sorted_frequency_magnitude_vec(const vec& source, value_t fs);
fm_vec sorted_frequency_magnitude_vec(const cx_vec& spectrum, value_t fs);

/**
* �õ�����ֵ��Ƶ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ź����, @sa sorted_frequency_magnitude_vec
*/
value_t principal_frequency(const fm_vec& fm_vector);

/**
* �õ���ֵ�м��СƵ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ź����, @sa sorted_frequency_magnitude_vec
*/
value_t median_frequency(const fm_vec& fm_vector);

/**
* �õ�1/4��ֵ��СƵ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ź����, @sa sorted_frequency_magnitude_vec
*/
value_t first_quater_frequency(const fm_vec& fm_vector);

/**
* �õ�3/4��ֵ��СƵ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ź����, @sa sorted_frequency_magnitude_vec
*/
value_t third_quater_frequency(const fm_vec& fm_vector);

/**
* �õ�ǰn������ֵ��Ƶ��
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ź����, @sa sorted_frequency_magnitude_vec
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
*
* @note �����<b>Ƶ��-��ֵ</b>�������Ź����, @sa sorted_frequency_magnitude_vec
*/
value_t frequency_entropy(const fm_vec& fm_vector, int range_num = 8);

/** @}*/
}

#endif // FREQUENCY_DOMAIN_FEATURES_H__

/**
* @example test_frequency_domain_features.cpp
* An example for current module @ref frefeatures
*/

