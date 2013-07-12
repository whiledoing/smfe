#include <boost/test/unit_test.hpp>

#include <smfe/global.h>
#include <smfe/common_function.h>
using namespace smfe;

BOOST_AUTO_TEST_CASE(test_common_func)
{
	vec data("5 1 4 3 2");

	value_t sum = 15;
	value_t error = 1e-9;

	BOOST_REQUIRE_CLOSE_FRACTION(mean(data), sum/data.size(), error);

	value_t entropy_sum = 0;
	for(int i = 0; i < data.size(); ++i) {
		value_t p = data[i]/sum;
		entropy_sum += p*log(p);
	}
	BOOST_REQUIRE_CLOSE_FRACTION(entropy(data), -entropy_sum, error);

	BOOST_REQUIRE_CLOSE_FRACTION(energy(data), 55.0, error);
	BOOST_REQUIRE_CLOSE_FRACTION(power(data), 55.0/data.size(), error);
	BOOST_REQUIRE_CLOSE_FRACTION(norm(data), sqrt(55.0), error);
	BOOST_REQUIRE_CLOSE_FRACTION(rms(data), sqrt(55.0/data.size()), error);

	BOOST_REQUIRE_CLOSE_FRACTION(first_quater(data), 2.0, error);
	BOOST_REQUIRE_CLOSE_FRACTION(third_quater(data), 4.0, error);
}