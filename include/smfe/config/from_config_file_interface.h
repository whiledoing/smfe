#ifdef _MSC_VER
	#pragma once
#endif

#ifndef FROM_CONFIG_FILE_INTERFACE_H__
#define FROM_CONFIG_FILE_INTERFACE_H__

#include <istream>

#include "feature_extraction.hpp"
#include "ensure_exists.hpp"

#include <boost/static_assert.hpp>

namespace smfe
{

template<typename T>
class FromConfigFileInterface
{
public:
	typedef T this_type;
	static this_type from_config(const fs::path& path);
	static this_type from_config(std::istream& is);
	static this_type from_ptree(std::istream& is);
};

template<typename this_type>
this_type FromConfigFileInterface<this_type>::from_config(std::istream& is)
{
	pt::ptree config;
	read_info(is, config);

	return this_type::from_ptree(config);
}

template<typename this_type>
this_type FromConfigFileInterface<this_type>::from_config(const fs::path& path)
{
	ensure_exists(path);

	pt::ptree config;
	pt::read_info(path.generic_string(), config);

	return this_type::from_ptree(config);
}

template<typename this_type>
this_type FromConfigFileInterface<this_type>::from_ptree(const fs::path& path)
{
    BOOST_STATIC_ASSERT_MSG(false, "The class derived from FromConfigFileInterface<T> mast implement its own from_ptree method");
}

}

#endif // FROM_CONFIG_FILE_INTERFACE_HPP__
