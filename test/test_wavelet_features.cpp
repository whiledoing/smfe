#include <boost/test/unit_test.hpp>
#include <boost/filesystem/path.hpp>
namespace bf = boost::filesystem;

#include <config.h>
#include <smfe/feature/wavelet_features.h>

#include <string>
#include <vector>
#include <fstream>

using namespace std;

using namespace smfe;

template<typename T>
void print_vec(const T& data, string msg = "")
{
    if(msg != "")
        cout << msg << ": " << endl;

    cout << "size : " << data.size() << endl;
    for(int i = 0; i < data.size(); ++i) {
        if((i+1)%5 == 0)
            cout << endl;
        cout << data[i] << " ";
    }
    cout << endl;
}

smfe::vec get_test_signal()
{
    string inp = (bf::path(ROOT) / "time_signal.txt").generic_string();

    vector<double> sig;
    ifstream sig_inp(inp);
    if (!sig_inp.good()) {
        cout << "the file doesn't exist"<< endl;
    }

    while(sig_inp) back_inserter(sig) = *istream_iterator<double>(sig_inp);
    return smfe::make_vec(sig);
}

BOOST_AUTO_TEST_CASE(test_wavelet)
{
    auto input = get_test_signal();

    int level = 6;
    string wavelet_name = "db2";

    dwt_length_vec length;
    auto dwt_output = smfe::dwt(input, wavelet_name, level, length);

    BOOST_REQUIRE_EQUAL(input.size(), 256);
    BOOST_REQUIRE_EQUAL(dwt_output.size(), 256);
    BOOST_REQUIRE_EQUAL(length.size(), level+1);

    {
        auto res = smfe::dwt_approximation_coeff(dwt_output, length);
        BOOST_REQUIRE_EQUAL_COLLECTIONS(res.begin(), res.end(), dwt_output.begin(), dwt_output.begin() + 4);
    }

    {
        auto res = smfe::dwt_approximation_coeff(input, wavelet_name, level);
        BOOST_REQUIRE_EQUAL_COLLECTIONS(res.begin(), res.end(), dwt_output.begin(), dwt_output.begin() + 4);
    }

    {
        auto res = smfe::dwt_detail_coeff(input, wavelet_name, level, 6);
        BOOST_REQUIRE_EQUAL(res.size(), 4);
        BOOST_REQUIRE_EQUAL_COLLECTIONS(res.begin(), res.end(), dwt_output.begin() + 4, dwt_output.begin() + 8);
    }

    {
        auto res = smfe::dwt_detail_coeff(dwt_output, length, 1);
        BOOST_REQUIRE_EQUAL(res.size(), 128);
        BOOST_REQUIRE_EQUAL_COLLECTIONS(res.begin(), res.end(), dwt_output.begin() + 128, dwt_output.end());
    }

    {
        auto res = smfe::dwt_detail_coeff(dwt_output, length, 6);
        BOOST_REQUIRE_EQUAL(res.size(), 4);
        BOOST_REQUIRE_EQUAL_COLLECTIONS(res.begin(), res.end(), dwt_output.begin() + 4, dwt_output.begin() + 8);
    }
}

BOOST_AUTO_TEST_CASE(test_idwt)
{
	auto input = get_test_signal();

    {
		auto signal = input;
	    int level = 1;
	    string wavelet_name = "db3";
	
	    dwt_length_vec length;
	    dwt_flag_vec flag;
	    auto dwt_output = smfe::dwt(signal, wavelet_name, level, length, flag);
	
		auto idwt_output = smfe::idwt(dwt_output, wavelet_name, level, length, flag);
	
		static double error = 1e-5;
		BOOST_REQUIRE_EQUAL(signal.size(), idwt_output.size());
		for(int i = 0u; i < dwt_output.size(); ++i)
			BOOST_REQUIRE_CLOSE_FRACTION(signal[i], idwt_output[i], error);
    }

	// 使用奇数长度的数据
    {
		auto signal = make_vec(input.begin(), input.begin()+47);
	    int level = 1;
	    string wavelet_name = "db3";
	
	    dwt_length_vec length;
	    dwt_flag_vec flag;
	    auto dwt_output = smfe::dwt(input, wavelet_name, level, length, flag);
	
		auto idwt_output = smfe::idwt(dwt_output, wavelet_name, level, length, flag);
	
		static double error = 1e-5;
		BOOST_REQUIRE_EQUAL(input.size(), idwt_output.size());
		for(int i = 0u; i < dwt_output.size(); ++i)
			BOOST_REQUIRE_CLOSE_FRACTION(input[i], idwt_output[i], error);
    }

	// 使用不同level下进行idwt的测试
    {
        auto signal = input;
        int level = 3;
        string wavelet_name = "db5";

        dwt_length_vec length;
        dwt_flag_vec flag;
        auto dwt_output = smfe::dwt(signal, wavelet_name, level, length, flag);

        auto idwt_output = smfe::idwt(dwt_output, wavelet_name, level, length, flag);

        static double error = 1e-5;
        BOOST_REQUIRE_EQUAL(signal.size(), idwt_output.size());
        for(int i = 0u; i < dwt_output.size(); ++i)
            BOOST_REQUIRE_CLOSE_FRACTION(signal[i], idwt_output[i], error);
    }
}


BOOST_AUTO_TEST_CASE(test_range_detail_coeff)
{
    auto input = get_test_signal();

    {
        auto signal = input;
        int level = 1;
        string wavelet_name = "db3";

		auto coef_vec = dwt_detail_coeff_of_range(signal, wavelet_name, level, 1, 2);
		BOOST_REQUIRE_EQUAL(coef_vec.size(), 1);

		auto level_coeff = dwt_detail_coeff(signal, wavelet_name, level, 1);	
		BOOST_REQUIRE_EQUAL_COLLECTIONS(coef_vec[0].begin(), coef_vec[0].end(), level_coeff.begin(), level_coeff.end());
    }

    {
        auto signal = input;
        int level = 4;
        string wavelet_name = "db1";

        auto coef_vec = dwt_detail_coeff_of_range(signal, wavelet_name, level, 1, 4);
        BOOST_REQUIRE_EQUAL(coef_vec.size(), 3);

        for(int i = 1; i < 4; ++i) {
            auto level_coeff = dwt_detail_coeff(signal, wavelet_name, level, i);	
			BOOST_REQUIRE_EQUAL(coef_vec[i-1].size(), level_coeff.size());
            BOOST_REQUIRE_EQUAL_COLLECTIONS(coef_vec[i-1].begin(), coef_vec[i-1].end(), level_coeff.begin(), level_coeff.end());
        }
    }
}