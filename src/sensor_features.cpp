#include "smfe/feature/sensor_features.h"
#include "smfe/feature/integral_calculus.h"
#include "smfe/feature/mean_filter.h"
#include "smfe/feature/statistic_features.h"
#include <boost/assert.hpp>

namespace smfe
{
inline bool is_noise(value_t value, value_t noise_value)
{
    return abs(value) < noise_value;
}

inline bool is_zero(value_t value)
{
    static const value_t error = 1e-7;
    return abs(value) < error;
}

inline value_t last_elem(const vec& d)
{
    return d[d.size()-1];
}

vec velocity_impl(const vec& acce_data,
                  value_t delta,
                  value_t still_acce_threshold,
                  int station_count_threshold,
                  value_t init_velocity,
                  bool using_ave_filter,
                  int filter_size
                 )
{
    vec two_value_filtered_data;

    // 是否进行均值滤波
    if(using_ave_filter)
        two_value_filtered_data = mean_filter(acce_data, filter_size);
    else
        two_value_filtered_data = acce_data;

    // 预处理，小于阈值的都认为是传感器静止状态下的数据
    for(int i = 0; i < two_value_filtered_data.size(); ++i) {
        if(is_noise(two_value_filtered_data[i], still_acce_threshold))
            two_value_filtered_data[i] = 0.0;
    }

    /*
    // 如果两边都是零点，那么也认为是零点
    for(int i = 1; i < two_value_filtered_data.size() - 1; ++i) {
        if(!is_zero(two_value_filtered_data[i]) && is_zero(two_value_filtered_data[i-1])
            && is_zero(two_value_filtered_data[i+1]))
            two_value_filtered_data[i] = 0;
    }
    */

    int station_count = 0;
    vec res_velocity(two_value_filtered_data.size());
    res_velocity[0] = init_velocity;

    for(int i = 1; i < res_velocity.size(); ++i) {
        if(is_zero(two_value_filtered_data[i]))
            ++station_count;
        else
            station_count = 0;

        /* 静态检测 : 如果有连续多个加速度数据为静止零值，将速度强制为零. */
        if(station_count > station_count_threshold)
            res_velocity[i] = 0.0;
        else
            res_velocity[i] = ((two_value_filtered_data[i-1]+two_value_filtered_data[i])/2)*delta + res_velocity[i-1];
    }

    return res_velocity;
}

value_t distance_impl(const vec& velocity_data,
                      value_t delta,
                      int degree
                     )
{
    return delta * integration(velocity_data, degree);
}

value_t velocity(const vec& acce_data,
                 value_t delta,
                 value_t init_velocity,
                 value_t still_acce_threshold,
                 int station_count_threshold,
                 bool using_ave_filter,
                 int filter_size
                )
{
    BOOST_ASSERT(filter_size >= 0);
    BOOST_ASSERT(still_acce_threshold >= 0.0);
    BOOST_ASSERT(station_count_threshold > 0);

    return last_elem(
               velocity_impl(acce_data, delta, still_acce_threshold, station_count_threshold,
                             init_velocity, using_ave_filter, filter_size)
           );
}

value_t distance(const vec& acce_data, value_t delta /*= 1.0*/, value_t init_velocity /*= 0.0*/,
                       value_t still_acce_threshold /*= 0.0*/, int station_count_threshold /*= INT_MAX*/, 
                       bool using_ave_filter /*= false*/, int filter_size /*= 2*/, int degree /*= 3 */)
{
    BOOST_ASSERT(filter_size >= 0);

    auto velocity_data = velocity_impl(acce_data, delta, still_acce_threshold, station_count_threshold,
                                       init_velocity, using_ave_filter, filter_size);
    return distance_impl(velocity_data, delta, degree);
}

vec smfe_identity_rot = make_rotate(1, 0, 0, 0);

inline vec vec3d_cross_product(const vec& lhs, const vec& rhs)
{
	BOOST_ASSERT(lhs.size() == 3 && rhs.size() == 3);

	vec res(3);
	res[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
	res[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
	res[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
	return res;

/* copy from orge :
  
	return Vector3(
		y * rkVector.z - z * rkVector.y,
		z * rkVector.x - x * rkVector.z,
		x * rkVector.y - y * rkVector.x);
*/
}

inline void vec3d_multiply(vec& v, value_t m)
{
	BOOST_ASSERT(v.size() == 3);
	v[0] *= m;
	v[1] *= m;
	v[2] *= m;
}

vec rotate_vector(const vec& rot, const vec& v)
{
	BOOST_ASSERT(rot.size() == 4 && v.size() == 3);

/*  copy form orge :
   
    Vector3 uv, uuv;
    Vector3 qvec(x, y, z);
    uv = qvec.crossProduct(v);
    uuv = qvec.crossProduct(uv);
    uv *= (2.0f * w);
    uuv *= 2.0f;

    return v + uv + uuv;
*/

    vec uv, uuv;
    vec qvec(3);
	value_t w = rot[0], x = rot[1], y = rot[2], z = rot[3];
    qvec[0] = x; qvec[1] = y; qvec[2] = z;

    uv = vec3d_cross_product(qvec, v);
	uuv = vec3d_cross_product(qvec, uv);

	vec3d_multiply(uv, 2.0 * w);
	vec3d_multiply(uuv, 2.0);

    return v + uv + uuv;
}

void smfe_normalise_vec(vec& v)
{
	value_t norm_len = norm(v);

	for(int i = 0; i < v.size(); ++i)
		v[i] /= norm_len;
}

} // namespace smfe