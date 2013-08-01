/**
 * @file mean_filter.h
 * @brief ��ֵ�˲�
 * @author whiledoing
 * @date 2013-07-17
 */

#ifdef _MSC_VER
#pragma once
#endif

#ifndef MEAN_FILTER_H__
#define MEAN_FILTER_H__

#include "../global.h"

#include <boost/assert.hpp>

namespace smfe
{
/**
 * @brief ���������ض�index�µ��˲����
 *
 * @param data ��������
 * @param filter_size ��ֵ�˲���С
 * @param index �˲���indexλ��
 *
 * @return indexλ���µ��˲����
 */
value_t mean_filter_get_one_index(const vec& data, int filter_size, int index);

/**
 * @brief ����һ�������ڵ��˲����
 *
 * @note ���䷶ΧΪ[start_index, end_index)���߶��ǰ�����ϵ
 */
vec mean_filter_get_range(const vec& data, int filter_size, int start_index, int end_index);


/**
 * @brief ���㵱ǰ�������ݵľ�ֵ�˲����
 */
inline vec mean_filter(const vec& data, int filter_size)
{
    return mean_filter_get_range(data, filter_size, 0, data.size());
}

}

#endif // MEAN_FILTER_H__

/**
 * @example test_sensor_features.cpp
 * An example for using mean_filter
 */
