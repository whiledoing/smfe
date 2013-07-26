#include <boost/test/unit_test.hpp>

#include <boost/assign/std/vector.hpp>

#include <smfe/global.h>
#include <smfe/feature/statistic_features.h>

using namespace smfe;

BOOST_AUTO_TEST_CASE(test_common_func)
{
    value_t d[] = {5, 1, 4, 3, 2};
    vec data = make_vec(d, 5);

    value_t total_sum = smfe::sum(data);
    value_t error = 1e-9;

    BOOST_REQUIRE_CLOSE_FRACTION(smfe::sum(data), total_sum, error);
    BOOST_REQUIRE_CLOSE_FRACTION(smfe::mean(data), total_sum/data.size(), error);

    BOOST_REQUIRE_CLOSE_FRACTION(smfe::var(data), 2.5, error);
    BOOST_REQUIRE_CLOSE_FRACTION(smfe::stddev(data), sqrt(2.5), error);

    BOOST_REQUIRE_CLOSE_FRACTION(smfe::min(data), 1, error);
    BOOST_REQUIRE_CLOSE_FRACTION(smfe::max(data), 5, error);

    BOOST_REQUIRE_CLOSE_FRACTION(smfe::median(data), 3, error);

    vec data2("6 3 4 2 1 5");
    BOOST_REQUIRE_CLOSE_FRACTION(smfe::median(data2), 3.5, error);

    value_t entropy_sum = 0;
    for(int i = 0; i < data.size(); ++i) {
        value_t p = data[i]/total_sum;
        entropy_sum += p*log(p);
    }

    {
        using namespace boost::assign;
        std::vector<int> count_data;
        count_data += 5, 1, 4, 3, 2;
        BOOST_REQUIRE_CLOSE_FRACTION(entropy(count_data), -entropy_sum, error);
    }

    BOOST_REQUIRE_CLOSE_FRACTION(energy(data), 55.0, error);
    BOOST_REQUIRE_CLOSE_FRACTION(power(data), 55.0/data.size(), error);
    BOOST_REQUIRE_CLOSE_FRACTION(norm(data), sqrt(55.0), error);
    BOOST_REQUIRE_CLOSE_FRACTION(rms(data), sqrt(55.0/data.size()), error);

    BOOST_REQUIRE_CLOSE_FRACTION(first_quater(data), 2.0, error);
    BOOST_REQUIRE_CLOSE_FRACTION(third_quater(data), 4.0, error);

}