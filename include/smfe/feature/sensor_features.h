#ifdef _MSC_VER
	#pragma once
#endif

#ifndef SENSOR_FEATURES_H__
#define SENSOR_FEATURES_H__

#include "../sensor_global.h"

namespace smfe 
{

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
 * @param still_acce_threshold ���϶�Ϊ��ֵ0�ļ��ٶ���ֵ(����0.5,�ͱ�ʾ���м��ٶ���ֵ����ֵС��0.5�Ķ���Ϊ�Ǿ�ֹ״̬)
 * @param station_count_threshold ���϶�Ϊ���ھ�ֹ״̬˵��Ҫ��С��0��ֵ���ٶ�֡��
 * @param init_velocity ��ʼʱ�̼��ٶ�
 * @param using_ave_filter �Ƿ�ʹ�þ�ֵ�˲������ݽ���Ԥ����
 * @param filter_size ��ֵ�˲�ʹ��filter�Ĵ�С. i֡������,ʹ��[i-filter, i+filter_size]֮�����ֵ����ƽ��
 * 
 * @return velocity collection 
 */
template<typename ContainterType>
ContainterType velocity(const ContainterType& acce_data, 
						value_t delta = 1.0,
                        value_t still_acce_threshold = 0.0, 
						int station_count_threshold = 1,
                        value_t init_velocity = 0.0, 
                        bool using_ave_filter = false,
						int filter_size = 2
);

/**
 * �����ʱ����(2s)���˶��������ƶ���λ��(Ҳ�������Ϊ�Ƕ�,���ʹ�ý��ٶ���Ϊ��������Ļ�)
 *
 * �������ݱ����Ǳ�ʾ�ٶȵ�����
 * 
 * @note ������ֵû������,ÿһ����������֮��ļ������ΪΪdelta�Ĵ�С.����
 * �ȼ�������ļ��ٶ��ٶ�����,delta���ǲ���ʱ��fs.
 * 
 * @param velocity_data ������ٶ�����
 * @param delta ��������֮������С
 * @param using_ave_filter �Ƿ�ʹ�þ�ֵ�˲������ݽ���Ԥ����
 * @param filter_size ��ֵ�˲�ʹ��filter�Ĵ�С. i֡������,ʹ��[i-filter, i+filter_size]֮�����ֵ����ƽ��
 * 
 * @return moving distance
 */
template<typename ContainterType>
value_t distance(const ContainterType& velocity_data, 
				 value_t delta = 1.0,
				 bool using_ave_filter = false,
				 int filter_size = 2
);

}

#endif // SENSOR_FEATURES_H__

