/**
 * @file sensor_features.h
 * @brief ���˶��ź���ص�����
 * @author whiledoing
 * @date 2013-07-17
 */

#ifdef _MSC_VER
	#pragma once
#endif

#ifndef SENSOR_FEATURES_H__
#define SENSOR_FEATURES_H__

#include "../sensor_global.h"

namespace smfe 
{
/**
 * @defgroup sensorfeatures sensor-features
 *
 * �˶�������ص�����
 *
 * @{ */

/**
 * ����һ��ʱ���˶����ٶ�
 * 
 * ��������ݱ���Ϊ���ٶ�����
 * 
 * @note ������ֵû������,ÿһ����������֮��ļ������ΪΪdelta�Ĵ�С.����
 * �ȼ�������ļ��ٶ��ٶ�����,delta���ǲ���ʱ��fs.
 * 
 * @param acce_data ����ļ��ٶ���������
 * @param delta ��������֮������С
 * @param init_velocity ��ʼʱ�̼��ٶ�
 * @param still_acce_threshold ���϶�Ϊ��ֵ0�ļ��ٶ���ֵ(����0.5,�ͱ�ʾ���м��ٶ���ֵ����ֵС��0.5�Ķ���Ϊ�Ǿ�ֹ״̬)
 * @param station_count_threshold ���϶�Ϊ���ھ�ֹ״̬˵��Ҫ��С��0��ֵ���ٶ�֡��,Ĭ������Ϊ���intֵ,��ʾ�����о�ֹ״̬�ļ��
 * @param using_ave_filter �Ƿ�ʹ�þ�ֵ�˲������ݽ���Ԥ����
 * @param filter_size ��ֵ�˲�ʹ��filter�Ĵ�С. i֡������,ʹ��[i-filter, i+filter_size]֮�����ֵ����ƽ��
 * 
 * @return ���ʱ�̵��ٶ���ֵ
 */
value_t velocity(const vec& acce_data, 
						value_t delta = 1.0,
                        value_t init_velocity = 0.0, 
                        value_t still_acce_threshold = 0.0, 
						int station_count_threshold = INT_MAX,
                        bool using_ave_filter = false,
						int filter_size = 2
);

/**
 * �����ʱ����(2s)���˶��������ƶ���λ��(Ҳ�������Ϊ�Ƕ�,���ʹ�ý��ٶ���Ϊ��������Ļ�)
 *
 * �������ݱ����Ǳ�ʾ���ٶȵ�����
 * 
 * @note 
 * 1.	������ֵû������,ÿһ����������֮��ļ������ΪΪdelta�Ĵ�С.����
 * �ȼ�������ļ��ٶ��ٶ�����,delta���ǲ���ʱ��fs.
 * 2.	degree����ֵ��[2,4]֮��
 * 
 * @sa integration
 * 
 * @param acce_data ����ļ��ٶ�����
 * @param delta ��������֮������С
 * @param init_velocity ��ʼʱ�̼��ٶ�
 * @param still_acce_threshold ���϶�Ϊ��ֵ0�ļ��ٶ���ֵ(����0.5,�ͱ�ʾ���м��ٶ���ֵ����ֵС��0.5�Ķ���Ϊ�Ǿ�ֹ״̬)
 * @param using_ave_filter �Ƿ�ʹ�þ�ֵ�˲������ݽ���Ԥ����
 * @param filter_size ��ֵ�˲�ʹ��filter�Ĵ�С. i֡������,ʹ��[i-filter, i+filter_size]֮�����ֵ����ƽ��
 * @param degree �����㷨ʹ�õ�degree��Ŀ
 * 
 * @return moving distance 
 */
value_t distance(const vec& acce_data, 
				 value_t delta = 1.0,
                 value_t init_velocity = 0.0, 
                 value_t still_acce_threshold = 0.0, 
                 int station_count_threshold = INT_MAX,
				 bool using_ave_filter = false,
				 int filter_size = 2,
				 int degree = 3
);

inline vec make_rotate(value_t w, value_t x, value_t y, value_t z)
{
	vec res(4);
	res[0] = w; res[1] = x; res[2] = y; res[3] = z;
	return res;
}

inline vec make_3dvec(value_t x, value_t y, value_t z)
{
	vec res(3);
	res[0] = x; res[1] = y; res[2] = z;
	return res;
}

inline vec make_rotate(const value_t radian_angle, const vec& axis)
{
	// assert:  axis[] is unit length
	//
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	value_t fHalfAngle(0.5*radian_angle);
	value_t fSin = sin(fHalfAngle);

	value_t w,x,y,z;
	w = cos(fHalfAngle);
	x = fSin*axis[0];
	y = fSin*axis[1];
	z = fSin*axis[2];
	return make_rotate(w, x, y, z);
}

void smfe_normalise_vec(vec& v);

extern vec smfe_identity_rot; 

vec rotate_vector(const vec& rot, const vec& v);
/**  @} */
}

#endif // SENSOR_FEATURES_H__

/**
 * @example test_sensor_features.cpp
 * An example for current module @ref sensorfeatures
 */
