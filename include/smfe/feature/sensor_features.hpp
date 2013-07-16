#ifdef _MSC_VER
#pragma once
#endif

#ifndef SENSOR_FEATURES_HPP__
#define SENSOR_FEATURES_HPP__

#include "sensor_features.h"
#include "integral_calculus.h"
#include "mean_filter.h"
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

template<typename ContainterType>
ContainterType velocity_impl(const ContainterType& acce_data,
                             value_t delta,
                             value_t still_acce_threshold,
                             int station_count_threshold,
                             value_t init_velocity
                            )
{
    std::vector<double> two_value_filtered_data = acce_data;

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
    std::vector<double> res_velocity(two_value_filtered_data.size());
    res_velocity[0] = init_velocity;

    for(int i = 1; i < res_velocity.size(); ++i) {
        if(is_zero(two_value_filtered_data[i]))
            ++station_count;
        else
            station_count = 0;

        /* 静态检测 : 如果有连续多个加速度数据为静止零值，将速度强制为零. */
        if(station_count >= station_count_threshold)
            res_velocity[i] = 0.0;
        else
            res_velocity[i] = ((two_value_filtered_data[i-1]+two_value_filtered_data[i])/2)*delta + res_velocity[i-1];
    }

    return res_velocity;
}

template<typename ContainterType>
value_t distance_impl(const ContainterType& velocity_data,
                      value_t delta
                     )
{
	return delta * integration(velocity_data, 3);
}

template<typename ContainterType>
ContainterType velocity(const ContainterType& acce_data,
                        value_t delta,
                        value_t still_acce_threshold,
                        int station_count_threshold,
                        value_t init_velocity,
                        bool using_ave_filter,
                        int filter_size
                       )
{
    BOOST_ASSERT(filter_size >= 0);
    BOOST_ASSERT(still_acce_threshold >= 0.0);
    BOOST_ASSERT(station_count_threshold > 0);

    // mean filter all the vector
    if(using_ave_filter) {
        auto after_mean = mean_filter(acce_data, filter_size);
        return velocity_impl(after_mean, delta, still_acce_threshold, station_count_threshold, init_velocity)
    }

    return velocity_impl(acce_data, delta, still_acce_threshold, station_count_threshold, init_velocity);
}

template<typename ContainterType>
value_t distance(const ContainterType& velocity_data,
                 value_t delta,
                 bool using_ave_filter,
                 int filter_size
                )
{
    BOOST_ASSERT(filter_size >= 0);

    if(using_ave_filter) {
        auto after_mean = mean_filter(velocity_data, filter_size);
        return distance_impl(after_mean, delta);
    }

    return distance_impl(velocity_data, delta);
}

}

#endif // SENSOR_FEATURES_HPP__

