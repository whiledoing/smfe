#ifdef _MSC_VER
	#pragma once
#endif

#ifndef INTEGRAL_CALCULUS_H__
#define INTEGRAL_CALCULUS_H__

#include "../global.h"
#include <boost/assert.hpp>

namespace smfe
{

/**
 * ������ɢ���ݵĻ���
 * 
 * 1.	�������ݱ����ǵȼ���ֲ���,���ｫ���ͳһ����Ϊ��λ1,���ݼ�����Ҫ��ͬ��degree
 * ʹ�ò�ͬ����ֵ�����㷨.
 *	
 * 2.	��ͬ��\c degreeӰ����ּ���������.Խ�ߵ�\c degree��Ҫ�����������ĿԽ��,����
 * \c degreeΪ3��ʱ��,��Ҫ�������������ݼ������ǰС��������.����\c degreeΪ3��ʱ��,���
 * һ�����ݶ�Ӧ�Ļ�������û�б�����.
 * 
 * ���Բο�: <a href="http://en.wikipedia.org/wiki/Newton%E2%80%93Cotes_formulas">wiki</a> http://en.wikipedia.org/wiki/Newton%E2%80%93Cotes_formulas
 *
 * @param data ��������
 * @param degree ������Ҫ�Ľ���
 *
 * @pre degree�ķ�ΧΪ[2,4]
 */
value_t integration(vec const& data, int degree = 2);

/**
 *	����Ƿֵȼ���������ݵĻ���
 *	
 *	1.	����������ɢ���ݵļ���в���delta_vec����
 *	2.	����data[1]��data[0]֮��ļ��Ϊdelta_vec[0],	data[2]��data[1]֮����Ϊdelta_vec[1],etc...
 *	3.	ʹ��degreeΪ2�Ļ����㷨
 *	
 *	@param data ����������
 *	@param delta_vec ��������֮����
 *	
 *	@pre <strong class="paramname">data</strong>�����ݳ��ȱ�<strong class="paramname">delta_vec</strong>�ĳ��ȴ�һ
 */
value_t integration(vec const& data, vec const& delta_vec);

}

#endif // INTEGRAL_CALCULUS_H__

