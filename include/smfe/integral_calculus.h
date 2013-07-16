#ifdef _MSC_VER
	#pragma once
#endif

#ifndef INTEGRAL_CALCULUS_H__
#define INTEGRAL_CALCULUS_H__

#include "global.h"
#include <boost/assert.hpp>

namespace smfe
{

/**
 * ������ɢ���ݵĻ���
 * 
 * 1.	�������ݱ����ǵȼ���ֲ���,���ｫ���ͳһ����Ϊ��λ1,���ݼ�����Ҫ��ͬ��degree
 * ʹ�ò�ͬ����ֵ�����㷨.
 *	
 * 2.	��ͬ��degreeӰ����ּ���������.Խ�ߵ�degree��Ҫ�����������ĿԽ��,����
 * degreeΪ3��ʱ��,��Ҫ�������������ݼ������ǰС��������.����degreeΪ3��ʱ��,���
 * һ�����ݶ�Ӧ�Ļ�������û�б�����.
 * 
 * ���Բο�:http://en.wikipedia.org/wiki/Newton%E2%80%93Cotes_formulas
 *
 * @param data ��������
 * @param degree ������Ҫ�Ľ���,��Ч��Χ[2,4]
 */
template<typename ContainterType>
value_t integration(ContainterType const& data, int degree = 2)
{
	CHECK_VALUE_TYPE(data);

	BOOST_ASSERT(degree >= 2 && degree <= 4);

    value_t sum = 0.0;

    for(int i = degree-1; i < data.size() - (degree-1); ++i)
        sum += data[i];

    if(degree == 2) {
        sum += (data[0] + data[data.size()-1])/2;
    }

    if(degree == 3) {
        sum += (data[0] + 5*data[1] + 5*data[data.size()-2] + data[data.size()-1]) / 6;
        return sum;
    }

    if(degree == 4) {
        sum += (data[0] + 4*data[1] + 7*data[2] + 7*data[data.size()-3] + 4*data[data.size()-2] + data[data.size()-1]) / 8;
        return sum;
    }

    return sum;
}

}

#endif // INTEGRAL_CALCULUS_H__

