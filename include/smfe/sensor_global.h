#ifdef _MSC_VER
	#pragma once
#endif

#ifndef SENSOR_GLOBAL_H__
#define SENSOR_GLOBAL_H__

#include <exception>
#include <string>

namespace smfe 
{

enum ChannelType {
    Acce,
    Mag,
    Gyro,
    Rot
};

inline ChannelType channel_type_from_string(const std::string& str)
{
    if(str == "Acce")
        return ChannelType::Acce;
    if(str == "Mag")
        return ChannelType::Mag;
    if(str == "Gyro")
        return ChannelType::Gyro;
    if(str == "Rot")
        return ChannelType::Rot;

	throw std::invalid_argument(str + " is not a valid channel type");
}

}

#endif // SENSOR_GLOBAL_H__

