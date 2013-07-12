#include <boost/test/unit_test.hpp>
#include <smfe/global.h>
#include <smfe/time_domain_features.h>

#include <iostream>
using namespace std;
using namespace smfe;

BOOST_AUTO_TEST_CASE(test_time_domain)
{
    vec data("2 7 4 9 3");

	const value_t error = 1e-6;
    BOOST_REQUIRE_CLOSE_FRACTION(skewness(data), 0.406040288214, error);
	BOOST_REQUIRE_CLOSE_FRACTION(kurtosis(data), -1.39965397924, error);

	BOOST_REQUIRE_EQUAL(quartile_deviation(data), 4);
	BOOST_REQUIRE_EQUAL(first_quater(data), 3);
	BOOST_REQUIRE_EQUAL(third_quater(data), 7);

    {
        BOOST_REQUIRE_CLOSE_FRACTION(cross_correlation_coefficient(data, data), 1.0, error);

        double x[4] = {3 , 7 , 5 , 6 };
        double y[4] = {4 , 3 , 7 , 1 };

        BOOST_REQUIRE_CLOSE_FRACTION(cross_correlation_coefficient(vec(x, 4), vec(y, 4)), -0.2781315, error);
    }
}