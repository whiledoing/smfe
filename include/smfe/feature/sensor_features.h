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

/**
 * @brief make_rotate ����һ����Ԫ������
 */
inline vec make_rotate(value_t w, value_t x, value_t y, value_t z)
{
    vec res(4);
    res[0] = w;
    res[1] = x;
    res[2] = y;
    res[3] = z;
    return res;
}

/**
 * @brief make_3dvec ����һ��3d����
 */
inline vec make_3dvec(value_t x, value_t y, value_t z)
{
    vec res(3);
    res[0] = x;
    res[1] = y;
    res[2] = z;
    return res;
}

/**
 * @brief make_rotate ������-�ǶԲ�����Ԫ������
 *
 * @param radian_angle �Ƕ�(��λ����)
 * @param axis ��, ���������
 *
 * @return  ��Ԫ��
 */
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

/**
 * @brief normalise_vec ��һ��һ������, 3d����4d��֧��
 *
 * @param v ��������
 */
void normalise_vec(vec& v);

extern vec identity_rot;    /**< ��λ��Ԫ�� */
extern vec x_unit_vec;      /**< ��λx���� */
extern vec y_unit_vec;      /**< ��λy���� */
extern vec z_unit_vec;      /**< ��λz���� */

/**
 * @brief rotate_3dvec ʹ��һ����Ԫ����תһ������v
 *
 * @param rot ��Ԫ��, @pre rot.size() == 4
 * @param v ����v, @pre v.size() == 3
 *
 * @return ��ת�������v
 */
vec rotate_3dvec(const vec& rot, const vec& v);

/**
 * @brief pack_amg_vec ���һ��amg����
 *
 * amg������һ������9��Ԫ�ص�������, ��ʽΪ:
 *
 *  [a.x a.y a.z m.x m.y m.z g.x g.y g.z]
 *
 * @param a ���ٶ�����
 * @param m ��ͨ����
 * @param g ����������
 *
 * @return ����õ�amg����
 */
inline vec pack_amg_vec(const vec& a, const vec& m, const vec& g)
{
    vec res(9);
    res[0] = a[0];
    res[1] = a[1];
    res[2] = a[2];
    res[3] = m[0];
    res[4] = m[1];
    res[5] = m[2];
    res[6] = g[0];
    res[7] = g[1];
    res[8] = g[2];
    return res;
}

/**
 * @brief unpack_amg_vec ���һ��amg����
 *
 * @param amg_v amg����
 * @param channel_type 0��ʾ���ٶ�, 1��ʾ��ͨ, 2��ʾ������
 *
 * @return ����Ϊ3��a/m/g����֮һ
 */
inline vec unpack_amg_vec(const vec& amg_v, int channel_type)
{
    vec res;
    if(channel_type == 0) {
        res = make_3dvec(amg_v[0], amg_v[1], amg_v[2]);
    } else if(channel_type == 1) {
        res = make_3dvec(amg_v[3], amg_v[4], amg_v[5]);
    } else if(channel_type == 2) {
        res = make_3dvec(amg_v[6], amg_v[7], amg_v[8]);
    }

    return res;
}

/**
 * @brief unpack_amg_mat ���һ��amg����
 *
 * amg������amg�����ļ���, ÿһ��amg�������Կ���һ������֡�����amg�����һ����,
 * ����amg���������Ϊ9, ����Ϊamg֡�ĸ���
 *
 * ������������һ������Ϊ3, ����Ϊamg֡�ĸ���. ������ȡ���Ǽ��ٶ�����,
 * ��ô���ؽ����, ÿһ�о���һ֡�ļ��ٶ�3������.
 *
 * @param amg_mat
 * @param channel_type 0��ʾ���ٶ�, 1��ʾ��ͨ, 2��ʾ������
 *
 * @return  ���������ݾ���
 */
inline mat unpack_amg_mat(const mat& amg_mat, int channel_type)
{
    BOOST_ASSERT(amg_mat.n_rows == 9);

    mat res;
    if(channel_type == 0) {
        res = amg_mat(arma::span(0, 2), arma::span::all);
    } else if(channel_type == 1) {
        res = amg_mat(arma::span(3, 5), arma::span::all);
    } else if(channel_type == 2) {
        res = amg_mat(arma::span(6, 8), arma::span::all);
    }

    return res;
}

/**
 * @brief rotate_amg_vec ��תamg����
 *
 * @param rot ��ת��Ԫ�� @pre rot.size() == 3
 * @param amg_v amg��������, ����Ϊ9��������
 *
 * @return ��ת���amg����
 */
vec rotate_amg_vec(const vec& rot, const vec& amg_v);

/**
 * @brief rotate_amg_mat ��ת���amg���� @sa pack_amg_vec @sa unpack_amg_mat
 *
 * @pre amg_mat.n_rows == 9 && rot_mat.n_rows == 4 && rot_mat.n_cols == amg_mat.n_cols
 * 
 * @param rot_mat ��Ӧÿһ֡�µ���Ԫ������
 * @param amg_mat amg����
 *
 * @return ��ת��amg���� 
 */
mat rotate_amg_mat(const mat& rot_mat, const mat& amg_mat);

/**
 * @brief moving_distance_of_amg_vec amg ����һ��ʱ���ഫ�������ƶ�����, ������.  @sa distance
 *
 * �����ʾ��������֡��amg����, �͵�ǰÿһ��amg֡����ת��.
 *
 * ����ת����ʾ��ǰ֡��<b>ȫ�������µĳ���</b>, amg���ݱ�ʾ��<b>�������ֲ�
 * �����µ�����</b>, ������ת֮��, �Ϳ��Եõ�amg������<b>ȫ�������µ�����</b>
 *
 * �ü���ֻ���õ��˼��ٶ�����, �����˼��ٶ�������ȫ�������µ��ƶ�����.
 *
 * �����distance @sa distance �ӿ�, ���������Ҫ��Ϊһ����ά��vec, ����delta
 * ��ʾ <b>x, y, z���ϵĲ���ʱ����</b>
 *
 * @param rot ȫ����������ת������
 * @param amg_mat �ֲ�����ϵ�µ�amg����
 *
 * @return �����ݶ�Ӧ��ȫ���������ƶ�����, ��ά������Ӧx, y, z���ϵ��ƶ�����
 */
vec moving_distance_of_amg_vec(const vec& rot, const mat& amg_mat,
                               vec delta = make_3dvec(1.0, 1.0, 1.0),
                               vec init_velocity = make_3dvec(0.0, 0.0, 0.0),
                               vec still_acce_threshold = make_3dvec(0.0, 0.0, 0.0),
                               int station_count_threshold = INT_MAX,
                               bool using_ave_filter = false,
                               int filter_size = 2,
                               int degree = 3
                              );

/**
 * @brief last_velocity_of_amg_vec ����һ��ʱ���ڴ��������ʱ�̵��ƶ��ٶ�, ������, @sa velocity
 *
 * ��ϸ˵���鿴�ӿ� <b>moving_distance_of_amg_vec</b> �� <b>velocity</b> @sa * moving_distance_of_amg_vec @sa velocity
 */
vec last_velocity_of_amg_vec(const vec& rot, const mat& amg_mat,
                             vec delta = make_3dvec(1.0, 1.0, 1.0),
                             vec init_velocity = make_3dvec(0.0, 0.0, 0.0),
                             vec still_acce_threshold = make_3dvec(0.0, 0.0, 0.0),
                             int station_count_threshold = INT_MAX,
                             bool using_ave_filter = false,
                             int filter_size = 2
                            );

/**
 * @brief rotated_angle_of_amg_vec ����һ��ʱ���ഫ����������ת���ĽǶ�, ������
 *
 * ����ʹ�û��ֵķ�ʽ @sa integration
 *
 * @param rot ȫ����������ת������
 * @param amg_mat �ֲ�����ϵ�µ�amg����
 * @param delta ÿһ��������������֮������С
 * @param using_ave_filter �Ƿ�ʹ�þ�ֵ�˲������ݽ���Ԥ����
 * @param filter_size �˲�������С
 * @param degree ���ֽ��� @sa integration
 *
 * @return ������������ת���ĽǶ�
 */
vec rotated_angle_of_amg_vec(const vec& rot, const mat& amg_mat,
                             vec delta = make_3dvec(1.0, 1.0, 1.0),
                             bool using_ave_filter = false,
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
