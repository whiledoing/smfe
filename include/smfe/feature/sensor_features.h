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
                 int station_count_threshold = INT_MAX,				 bool using_ave_filter = false,
				 int filter_size = 2,
				 int degree = 3
);

/**  @} */
}

#endif // SENSOR_FEATURES_H__

/**
 * @example test_sensor_features.cpp
 * An example for current module @ref sensorfeatures
 */
