#include "smfe/feature/wavelet_features.h"
#include <wavelet2d.h>

#include <boost/assert.hpp>
#include <boost/format.hpp>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

#include <aquila/tools/TextPlot.h>

namespace smfe
{
void check_signal_size_validation(const vec& data, int level)
{
	if(level <= 0)
        throw SMFEException("dwt need level bigger than 0");

    int max_level = (int) ceil(log(double(data.size()))/log (2.0)) - 2;
	auto err = boost::format("dwt level should be less than %1% when signal size is %2%") % max_level % data.size();
    if(level > max_level)
        throw SMFEException(err.str());
}


vector<double> change_to_std_vector(const vec &data)
{
    if(typeid(vec::value_type) == typeid(double))
        return vector<double>(data.memptr(), data.memptr() + data.size());
    else {
		vector<double> res(data.size());
        for(int i = 0u; i < data.size(); ++i)
            res[i] = data[i];

		return res;
    }
}

vec dwt(const vec& time_signal, std::string wavelet_name, int wavlet_level)
{
    dwt_length_vec length;
    return dwt(time_signal, wavelet_name, wavlet_level, length);
}

vec dwt(const vec& data, std::string wavelet_name, int level, std::vector<int>& length)
{
	dwt_flag_vec flag;
	return dwt(data, wavelet_name, level, length, flag);
}

vec dwt(const vec& data, std::string wavelet_name, int level, dwt_length_vec& length, dwt_flag_vec& flag)
{
    check_signal_size_validation(data, level);

    vector<double> input =  change_to_std_vector(data);
    vector<double> res;

    ::dwt(input, level, wavelet_name, res, flag, length);

    // last elem is not useful
    length.pop_back();

    return make_vec(res);
}

vec dwt_approximation_coeff(const vec& time_signal, std::string wavelet_name, int wavelet_level)
{
    dwt_length_vec length;
    auto wavelet_signal = dwt(time_signal, wavelet_name, wavelet_level, length);

    return dwt_approximation_coeff(wavelet_signal, length);
}

vec dwt_approximation_coeff(const vec& wavelet_signal, const dwt_length_vec& length)
{
	check_signal_size_validation(wavelet_signal, length.size() - 1);
    return make_sub_range(wavelet_signal, 0, length[0]);
}

vec dwt_detail_coeff(const vec& time_signal, std::string wavelet_name, int wavelet_level, int detail_coeff_level)
{
    dwt_length_vec length;
    auto wavelet_signal = dwt(time_signal, wavelet_name, wavelet_level, length);

    return dwt_detail_coeff(wavelet_signal, length, detail_coeff_level);
}

vec dwt_detail_coeff(const vec& wavelet_signal, const dwt_length_vec& length, int detail_coeff_level)
{
	check_signal_size_validation(wavelet_signal, length.size() - 1);

	if(detail_coeff_level < 1)
		throw SMFEException("dwt_detail_coeff: detail_coeff_level must bigger than 1");

	if(detail_coeff_level >= length.size())
		throw SMFEException("dwt_detail_coeff: detail_coeff_level must less equal than dwt level");

	int start_index = wavelet_signal.size();
	int i = length.size() - 1;
	for(int count = 0; count < detail_coeff_level; ++count, --i) {
		start_index -= length[i];
	}

	return make_sub_range(wavelet_signal, start_index, start_index + length[i+1]);
}

vec idwt(const vec& wavelet_signal, std::string wavelet_name, int wavelet_level, const dwt_length_vec& length, const dwt_flag_vec& flag)
{
	check_signal_size_validation(wavelet_signal, wavelet_level);

	vector<double> res;
	::idwt(change_to_std_vector(wavelet_signal), const_cast<dwt_flag_vec&>(flag), wavelet_name, res, const_cast<dwt_length_vec&>(length));

	return res;
}

}
