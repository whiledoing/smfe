#include <boost/test/unit_test.hpp>

#include <iostream>
using namespace std;

#include <smfe/feature/time_domain_features.h>
#include <smfe/feature/statistic_features.h>
#include <smfe/feature/frequency_domain_features.h>
using namespace smfe;

#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"

BOOST_AUTO_TEST_CASE(test_fft)
{
    const std::size_t SIZE = 16;
    const Aquila::FrequencyType sampleFreq = 1000;
    const Aquila::FrequencyType f1 = 125, f2 = 250;

    Aquila::SineGenerator sineGenerator1 = Aquila::SineGenerator(sampleFreq);
    sineGenerator1.setAmplitude(32).setFrequency(f1).generate(SIZE);
    Aquila::SineGenerator sineGenerator2 = Aquila::SineGenerator(sampleFreq);
    sineGenerator2.setAmplitude(8).setFrequency(f2).setPhase(0.75).generate(SIZE);
    auto sum = sineGenerator1 + sineGenerator2;
	auto source = make_vec(sum.toArray(), sum.length());

	// get frequency-magnitude vector using smfe library
    fm_vec fm = sorted_frequency_magnitude_vec(source, sampleFreq);

	const static value_t error = 1e-6;
	BOOST_REQUIRE_CLOSE_FRACTION(principal_frequency(fm), 125, error);
	BOOST_REQUIRE_CLOSE_FRACTION(fm[1].fre, 250.0, error);
	BOOST_REQUIRE_CLOSE_FRACTION(fm[1].mag, 8.0, error);

	/* 加入直流分量 */
	source += 12.3;

	for(auto v : fm)
		cout << v << endl;
	/* 按照频率大小排序的频率-幅度特征 */
	fm_vec unsorted_fm = frequency_magnitude_vec(source, sampleFreq);
	BOOST_REQUIRE_CLOSE_FRACTION(unsorted_fm[0].fre, 0, error);
	BOOST_REQUIRE_CLOSE_FRACTION(unsorted_fm[0].mag, 12.3, error);
	BOOST_REQUIRE_CLOSE_FRACTION(unsorted_fm[1].fre, 62.5, error);
	BOOST_REQUIRE_CLOSE_FRACTION(unsorted_fm[2].fre, 125, error);
	BOOST_REQUIRE_CLOSE_FRACTION(unsorted_fm[2].mag, 32, error);
}

BOOST_AUTO_TEST_CASE(test_ifft)
{
    const std::size_t SIZE = 64;
    const Aquila::FrequencyType sampleFreq = 4000;
    const Aquila::FrequencyType f1 = 125, f2 = 700;

    Aquila::SineGenerator sineGenerator1 = Aquila::SineGenerator(sampleFreq);
    sineGenerator1.setAmplitude(32).setFrequency(f1).generate(SIZE);
    Aquila::SineGenerator sineGenerator2 = Aquila::SineGenerator(sampleFreq);
    sineGenerator2.setAmplitude(8).setFrequency(f2).setPhase(0.75).generate(SIZE);
    auto sum = sineGenerator1 + sineGenerator2;

	// using smfe fft
	auto fft_res = smfe::smfe_fft(make_vec(sum.toArray(), sum.length()));

	// using smfe ifft
	auto back_res = smfe::smfe_ifft(fft_res);

	// check equality with original signal
	BOOST_REQUIRE_EQUAL(back_res.size(), SIZE);
	const static value_t error = 1e-6;
	int i = 0;
	for(auto ite = sum.begin(); ite != sum.end(); ++ite, ++i) {
		BOOST_REQUIRE_CLOSE_FRACTION(*ite, back_res[i], error);
	}
}