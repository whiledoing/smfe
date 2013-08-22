/**
 * @file sensor_features.h
 * @brief 和运动信号相关的特征
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
 * 运动传感相关的特征
 *
 * @{ */

/**
 * 计算一定时间运动的速度
 *
 * 输入的数据必须为加速度数据
 *
 * @note 求解的数值没有量纲,每一个相邻数据之间的间隔被认为为delta的大小.比如
 * 等间隔采样的加速度速度数据,delta就是采样时间fs.
 *
 * @param acce_data 输入的加速度数据向量
 * @param delta 相邻数据之间间隔大小
 * @param init_velocity 初始时刻加速度
 * @param still_acce_threshold 被认定为数值0的加速度阈值(比如0.5,就表示所有加速度数值绝对值小于0.5的都认为是静止状态)
 * @param station_count_threshold 被认定为处于静止状态说需要最小的0数值加速度帧数,默认设置为最大int值,表示不进行静止状态的检测
 * @param using_ave_filter 是否使用均值滤波对数据进行预处理
 * @param filter_size 均值滤波使用filter的大小. i帧的数据,使用[i-filter, i+filter_size]之间的数值进行平滑
 *
 * @return 最后时刻的速度数值
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
 * 计算短时间内(2s)内运动传感器移动的位移(也可以理解为角度,如果使用角速度作为输入参数的话)
 *
 * 输入数据必须是表示加速度的数据
 *
 * @note
 * 1.	求解的数值没有量纲,每一个相邻数据之间的间隔被认为为delta的大小.比如
 * 等间隔采样的加速度速度数据,delta就是采样时间fs.
 * 2.	degree的数值在[2,4]之间
 *
 * @sa integration
 *
 * @param acce_data 输入的加速度数据
 * @param delta 相邻数据之间间隔大小
 * @param init_velocity 初始时刻加速度
 * @param still_acce_threshold 被认定为数值0的加速度阈值(比如0.5,就表示所有加速度数值绝对值小于0.5的都认为是静止状态)
 * @param using_ave_filter 是否使用均值滤波对数据进行预处理
 * @param filter_size 均值滤波使用filter的大小. i帧的数据,使用[i-filter, i+filter_size]之间的数值进行平滑
 * @param degree 积分算法使用的degree数目
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
 * @brief make_rotate 生成一个四元数向量
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
 * @brief make_3dvec 生成一个3d向量
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
 * @brief make_rotate 根据轴-角对产生四元数向量
 *
 * @param radian_angle 角度(单位弧度)
 * @param axis 轴, 三轴的向量
 *
 * @return  四元数
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
 * @brief normalise_vec 归一化一个向量, 3d或者4d都支持
 *
 * @param v 输入向量
 */
void normalise_vec(vec& v);

extern vec identity_rot;    /**< 单位四元数 */
extern vec x_unit_vec;      /**< 单位x向量 */
extern vec y_unit_vec;      /**< 单位y向量 */
extern vec z_unit_vec;      /**< 单位z向量 */

/**
 * @brief rotate_3dvec 使用一个四元数旋转一个向量v
 *
 * @param rot 四元数, @pre rot.size() == 4
 * @param v 向量v, @pre v.size() == 3
 *
 * @return 旋转后的向量v
 */
vec rotate_3dvec(const vec& rot, const vec& v);

/**
 * @brief pack_amg_vec 打包一个amg向量
 *
 * amg向量是一个包含9个元素的列向量, 格式为:
 *
 *  [a.x a.y a.z m.x m.y m.z g.x g.y g.z]
 *
 * @param a 加速度向量
 * @param m 磁通向量
 * @param g 陀螺仪向量
 *
 * @return 打包好的amg向量
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
 * @brief unpack_amg_vec 解包一个amg向量
 *
 * @param amg_v amg向量
 * @param channel_type 0表示加速度, 1表示磁通, 2表示陀螺仪
 *
 * @return 长度为3的a/m/g向量之一
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
 * @brief unpack_amg_mat 解包一个amg矩阵
 *
 * amg矩阵是amg向量的集合, 每一个amg向量可以看成一个数据帧存放在amg矩阵的一列中,
 * 所以amg矩阵的行数为9, 列数为amg帧的个数
 *
 * 解包后的数据是一个行数为3, 列数为amg帧的个数. 比如提取的是加速度数据,
 * 那么返回结果中, 每一列就是一帧的加速度3轴数据.
 *
 * @param amg_mat
 * @param channel_type 0表示加速度, 1表示磁通, 2表示陀螺仪
 *
 * @return  解包后的数据矩阵
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
 * @brief rotate_amg_vec 旋转amg向量
 *
 * @param rot 旋转四元数 @pre rot.size() == 3
 * @param amg_v amg数据向量, 长度为9的列向量
 *
 * @return 旋转后的amg向量
 */
vec rotate_amg_vec(const vec& rot, const vec& amg_v);

/**
 * @brief rotate_amg_mat 旋转后的amg矩阵 @sa pack_amg_vec @sa unpack_amg_mat
 *
 * @pre amg_mat.n_rows == 9 && rot_mat.n_rows == 4 && rot_mat.n_cols == amg_mat.n_cols
 * 
 * @param rot_mat 对应每一帧下的四元数矩阵
 * @param amg_mat amg矩阵
 *
 * @return 旋转后amg矩阵 
 */
mat rotate_amg_mat(const mat& rot_mat, const mat& amg_mat);

/**
 * @brief moving_distance_of_amg_vec amg 计算一段时间类传感器的移动距离, 无量纲.  @sa distance
 *
 * 输入表示所有数据帧的amg矩阵, 和当前每一个amg帧的旋转量.
 *
 * 该旋转量表示当前帧在<b>全局坐标下的朝向</b>, amg数据表示在<b>传感器局部
 * 坐标下的数据</b>, 经过旋转之后, 就可以得到amg数据在<b>全局坐标下的数据</b>
 *
 * 该计算只是用到了加速度数据, 计算了加速度数据在全局坐标下的移动距离.
 *
 * 相比于distance @sa distance 接口, 计算参数需要改为一个三维的vec, 比如delta
 * 表示 <b>x, y, z轴上的采样时间间隔</b>
 *
 * @param rot 全局坐标下旋转量矩阵
 * @param amg_mat 局部坐标系下的amg数据
 *
 * @return 该数据对应在全局坐标下移动距离, 三维向量对应x, y, z轴上的移动距离
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
 * @brief last_velocity_of_amg_vec 计算一段时间内传感器最后时刻的移动速度, 无量纲, @sa velocity
 *
 * 详细说明查看接口 <b>moving_distance_of_amg_vec</b> 和 <b>velocity</b> @sa * moving_distance_of_amg_vec @sa velocity
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
 * @brief rotated_angle_of_amg_vec 计算一段时间类传感器陀螺仪转动的角度, 无量纲
 *
 * 单纯使用积分的方式 @sa integration
 *
 * @param rot 全局坐标下旋转量矩阵
 * @param amg_mat 局部坐标系下的amg数据
 * @param delta 每一个轴上相邻数据之间间隔大小
 * @param using_ave_filter 是否使用均值滤波对数据进行预处理
 * @param filter_size 滤波参数大小
 * @param degree 积分阶数 @sa integration
 *
 * @return 三轴上陀螺仪转动的角度
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
