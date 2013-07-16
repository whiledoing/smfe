#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_generate_fm)
{

}

#include <iostream>
using namespace std;

#include <smfe/feature/time_domain_features.h>
#include <smfe/feature/statistic_function.h>
#include <smfe/feature/frequency_domain_features.h>
using namespace smfe;

#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"

BOOST_AUTO_TEST_CASE(test_fft)
{
    const std::size_t SIZE = 64;
    const Aquila::FrequencyType sampleFreq = 4000;
    const Aquila::FrequencyType f1 = 125, f2 = 700;

    Aquila::SineGenerator sineGenerator1 = Aquila::SineGenerator(sampleFreq);
    sineGenerator1.setAmplitude(32).setFrequency(f1).generate(SIZE);
    Aquila::SineGenerator sineGenerator2 = Aquila::SineGenerator(sampleFreq);
    sineGenerator2.setAmplitude(8).setFrequency(f2).setPhase(0.75).generate(SIZE);
    auto sum = sineGenerator1 + sineGenerator2;

    // calculate the FFT using aquila
    auto fft = Aquila::FftFactory::getFft(SIZE);
    Aquila::SpectrumType spectrum = fft->fft(sum.toArray());

    fm_vec aquila_fm(spectrum.size() / 2);
    for(int i = 0u; i < spectrum.size()/2; ++i) {
        aquila_fm[i] = FrequencyMagnitude(i*sampleFreq/SIZE, 2*abs(spectrum[i])/SIZE);
    }
	sort(aquila_fm.begin(), aquila_fm.end(), greater<FrequencyMagnitude>());

	// get fft using smfe library
    fm_vec fm = sorted_frequency_magnitude_vec(vec(sum.toArray(), sum.length()), sampleFreq);

	// check frequency_magnitue array is equal
    BOOST_CHECK_EQUAL_COLLECTIONS(aquila_fm.begin(), aquila_fm.end(), fm.begin(), fm.end());

	const static value_t error = 1e-6;

	BOOST_REQUIRE_CLOSE_FRACTION(median_frequency(fm), 1000, error);
	BOOST_REQUIRE_CLOSE_FRACTION(principal_frequency(fm), 125, error);
	BOOST_REQUIRE_CLOSE_FRACTION(frequency_energy(fm), 1091.14, error);
	BOOST_REQUIRE_CLOSE_FRACTION(frequency_entropy(fm), 0.27711335, error);
}