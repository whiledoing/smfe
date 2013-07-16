#ifdef _MSC_VER
    #pragma once
#endif
#ifndef ENSURE_EXISTS_H__
#define ENSURE_EXISTS_H__

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/exception/all.hpp>

namespace capg { namespace sensor
{
    namespace fs = boost::filesystem;

    inline void ensure_exists(const fs::path &path)
    {
        if (!fs::exists(path))
        {
            BOOST_THROW_EXCEPTION(std::runtime_error(str(
                boost::format("file not found: %1%") % path
            )));
        }
    }
}}

#endif // __625B765E_F718_4BC6_9EDD_7FE51D1E01CE__
