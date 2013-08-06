#ifdef _MSC_VER
#pragma once
#endif

#ifndef CONFIG_GLOBAL_H__
#define CONFIG_GLOBAL_H__

#include <string>

#include "sensor_global.h"

#include <boost/format.hpp>
#include <boost/exception/all.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

namespace pt = boost::property_tree;
namespace fs = boost::filesystem;

namespace smfe
{

inline void throw_invalid_config(const std::string& err_str)
{
    BOOST_THROW_EXCEPTION(std::logic_error(str(
        boost::format("invalid config para : %1%") % err_str
        )));
}

template<typename T>
inline T data_value_from_string(const std::string& str)
{
    return boost::lexical_cast<T>(str);
}

template<>
inline ChannelType data_value_from_string<ChannelType>(const std::string& str)
{
    return channel_type_from_string(str);
}

template<typename T>
inline void get_value_from_ptree(
    const pt::ptree& config,
    const std::string& key,
    T& dst_value
)
{
    auto res = config.get_optional<std::string>(key);
    if(res)
        dst_value = data_value_from_string<T>(res.get());
    else
        throw_invalid_config("not exist " + key);
}

template<typename T>
inline void get_value_from_ptree(
    const pt::ptree& config,
    const std::string& key,
    T& dst_value,
    const T& default_value
)
{
    auto res = config.get_optional<std::string>(key);
    if(res)
        dst_value = data_value_from_string<T>(res.get());
    else
        dst_value = default_value;
}

}

#endif // FEATURE_EXTRACTION_HPP__

