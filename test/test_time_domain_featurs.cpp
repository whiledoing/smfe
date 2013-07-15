#include <boost/test/unit_test.hpp>
#include <smfe/global.h>
#include <smfe/time_domain_features.h>
#include <smfe/common_function.h>

#include <boost/assign/std/vector.hpp>
#include <iostream>
using namespace std;
using namespace smfe;
using namespace boost::assign;

BOOST_AUTO_TEST_CASE(test_time_domain)
{
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

            BOOST_REQUIRE_CLOSE_FRACTION(cross_correlation_coefficient(make_vec(x, 4), make_vec(y, y+4)), -0.370842, error);
        }

        BOOST_REQUIRE_CLOSE_FRACTION(mean(data), 5.0, error);
        BOOST_REQUIRE_CLOSE_FRACTION(mean_absolute_deviation(data), 2.4, error);
    }

    {
        value_t d[] = { 2, 7, 4, 9, 3};
        std::vector<value_t> data(d, d+5);

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

            BOOST_REQUIRE_CLOSE_FRACTION(cross_correlation_coefficient(make_vec(x, 4), make_vec(y, y+4)), -0.370842, error);
        }

        BOOST_REQUIRE_CLOSE_FRACTION(mean(data), 5.0, error);
        BOOST_REQUIRE_CLOSE_FRACTION(mean_absolute_deviation(data), 2.4, error);
    }
}