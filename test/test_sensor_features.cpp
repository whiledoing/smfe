#include <boost/test/unit_test.hpp>
#include <boost/assign/std/vector.hpp>

#include <smfe/feature/sensor_features.h>
#include <smfe/feature/mean_filter.h>
#include <smfe/feature/statistic_features.h>
#include <smfe/feature/integral_calculus.h>
using namespace smfe;

#include <numeric>
#include <algorithm>
using namespace std;

const static value_t error = 1e-7;

BOOST_AUTO_TEST_CASE(test_mean_filter)
{
    int size = 10;
    vector<value_t> test_data(size);

    value_t gene_scale = 5.0;
    auto gene_fun = [gene_scale]() {
        return ((value_t)rand()/RAND_MAX)*gene_scale;
    };
    generate_n(test_data.begin(), size, gene_fun);

    {
        int filter_size = 2;
        {
            value_t result = mean_filter_get_one_index(test_data, filter_size, 0);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(test_data, 0, filter_size)), error);
        }
        {
            auto result = mean_filter_get_one_index(test_data, filter_size, 1);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(test_data, 0, filter_size+1)), error);
        }
        {
            auto result = mean_filter_get_one_index(test_data, filter_size, 2);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(test_data, 0, filter_size+2)), error);
        }
        {
            auto result = mean_filter_get_one_index(test_data, filter_size, 5);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(test_data, 5-filter_size, 5+filter_size)), error);
        }
        {
            auto result = mean_filter_get_one_index(test_data, filter_size, size-1-filter_size);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(test_data, size-1-2*filter_size, size-1)), error);
        }
        {
            auto result = mean_filter_get_one_index(test_data, filter_size, size-filter_size);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(test_data, size-2*filter_size, size-1)), error);
        }
        {
            auto result = mean_filter_get_one_index(test_data, filter_size, size+1-filter_size);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(test_data, size+1-2*filter_size, size-1)), error);
        }

        // test mean_filter_get_range
        auto result = mean_filter_get_range(test_data, filter_size, 0, test_data.size()-1);
        BOOST_REQUIRE_CLOSE_FRACTION(result[0], mean(make_sub_range(test_data, 0, filter_size)), error);
        BOOST_REQUIRE_CLOSE_FRACTION(result[1], mean(make_sub_range(test_data, 0, 1+filter_size)), error);
        BOOST_REQUIRE_CLOSE_FRACTION(result[2], mean(make_sub_range(test_data, 0, 2+filter_size)), error);
        BOOST_REQUIRE_CLOSE_FRACTION(result[4], mean(make_sub_range(test_data, 4-filter_size, 4+filter_size)), error);
        BOOST_REQUIRE_CLOSE_FRACTION(result[size-filter_size], mean(make_sub_range(test_data, size-2*filter_size, size-1)), error);

        {
            int filter_size = 0;
            auto result = mean_filter_get_range(test_data, filter_size, 0, test_data.size() - 1);
            BOOST_REQUIRE(equal(test_data.begin(), test_data.end(), result.begin()));
        }
    }

    {
        auto data = make_vec(test_data);

        int filter_size = 2;
        {
            value_t result = mean_filter_get_one_index(data, filter_size, 0);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(data, 0, filter_size)), error);
        }
        {
            auto result = mean_filter_get_one_index(data, filter_size, 1);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(data, 0, filter_size+1)), error);
        }
        {
            auto result = mean_filter_get_one_index(data, filter_size, 2);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(data, 0, filter_size+2)), error);
        }
        {
            auto result = mean_filter_get_one_index(data, filter_size, 5);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(data, 5-filter_size, 5+filter_size)), error);
        }
        {
            auto result = mean_filter_get_one_index(data, filter_size, size-1-filter_size);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(data, size-1-2*filter_size, size-1)), error);
        }
        {
            auto result = mean_filter_get_one_index(data, filter_size, size-filter_size);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(data, size-2*filter_size, size-1)), error);
        }
        {
            auto result = mean_filter_get_one_index(data, filter_size, size+1-filter_size);
            BOOST_REQUIRE_CLOSE_FRACTION(result, mean(make_sub_range(data, size+1-2*filter_size, size-1)), error);
        }

        // test mean_filter_get_range
        auto result = mean_filter_get_range(data, filter_size, 0, data.size()-1);
        BOOST_REQUIRE_CLOSE_FRACTION(result[0], mean(make_sub_range(data, 0, filter_size)), error);
        BOOST_REQUIRE_CLOSE_FRACTION(result[1], mean(make_sub_range(data, 0, 1+filter_size)), error);
        BOOST_REQUIRE_CLOSE_FRACTION(result[2], mean(make_sub_range(data, 0, 2+filter_size)), error);
        BOOST_REQUIRE_CLOSE_FRACTION(result[4], mean(make_sub_range(data, 4-filter_size, 4+filter_size)), error);
        BOOST_REQUIRE_CLOSE_FRACTION(result[size-filter_size], mean(make_sub_range(data, size-2*filter_size, size-1)), error);

        {
            int filter_size = 0;
            auto result = mean_filter_get_range(data, filter_size, 0, data.size() - 1);
            BOOST_REQUIRE(equal(data.begin(), data.end(), result.begin()));
        }
    }
}

BOOST_AUTO_TEST_CASE(test_velocity)
{
    using namespace boost::assign;

    std::vector<value_t> stdvec;
    stdvec += 1, -2, 6, 7, 3, 10, 21, 15, -5, 2;

    {
        std::vector<value_t> stdres;
        stdres += 0.0, -0.5, 2, 6.5, 5, 6.5, 15.5, 18, 5, -1.5;
        partial_sum(stdres.begin(), stdres.end(), stdres.begin());

        auto res = velocity(stdvec);
        BOOST_REQUIRE_EQUAL(res.size(), stdres.size());
        BOOST_REQUIRE(equal(res.begin(), res.end(), stdres.begin()));
    }

    {
        std::vector<value_t> stdres;
        stdres += 0.0, 0.0, 3, 6.5, 5, 6.5, 15.5, 18, 5, -2.5;
        partial_sum(stdres.begin(), stdres.end(), stdres.begin());

        auto res = velocity(stdvec, 1.0, 0.0, 3.0);
        BOOST_REQUIRE_EQUAL(res.size(), stdres.size());
        BOOST_REQUIRE(equal(res.begin(), res.end(), stdres.begin()));
    }

    {
        std::vector<value_t> stdres;
        stdres += 0.0, 0.0, 3, 6.5, 5, 6.5, 15.5, 18, 5, -2.5;
        partial_sum(stdres.begin(), stdres.end(), stdres.begin());

        auto res = velocity(stdvec, 1.0, 0.0, 3.0);
        BOOST_REQUIRE_EQUAL(res.size(), stdres.size());
        BOOST_REQUIRE(equal(res.begin(), res.end(), stdres.begin()));
    }

    {
        std::vector<value_t> stdres;
        stdres += 0.0, 0.0, 0.0, 3.5, 7, 12, 27.5, 45.5, 53, 0.0;

        auto res = velocity(stdvec, 1.0, 0.0, 7.0, 1);
        BOOST_REQUIRE_EQUAL(res.size(), stdres.size());
        BOOST_REQUIRE(equal(res.begin(), res.end(), stdres.begin()));
    }

    // using vec
    {
        std::vector<value_t> stdres;
        stdres += 0.0, -0.5, 2, 6.5, 5, 6.5, 15.5, 18, 5, -1.5;
        partial_sum(stdres.begin(), stdres.end(), stdres.begin());

        auto res = velocity(make_vec(stdvec));
        BOOST_REQUIRE_EQUAL(res.size(), stdres.size());
        BOOST_REQUIRE(equal(res.begin(), res.end(), stdres.begin()));
    }

    {
        std::vector<value_t> stdres;
        stdres += 0.0, 0.0, 3, 6.5, 5, 6.5, 15.5, 18, 5, -2.5;
        partial_sum(stdres.begin(), stdres.end(), stdres.begin());

        auto res = velocity(make_vec(stdvec), 1.0, 0.0, 3.0);
        BOOST_REQUIRE_EQUAL(res.size(), stdres.size());
        BOOST_REQUIRE(equal(res.begin(), res.end(), stdres.begin()));
    }

    {
        std::vector<value_t> stdres;
        stdres += 0.0, 0.0, 3, 6.5, 5, 6.5, 15.5, 18, 5, -2.5;
        partial_sum(stdres.begin(), stdres.end(), stdres.begin());

        auto res = velocity(make_vec(stdvec), 1.0, 0.0, 3.0);
        BOOST_REQUIRE_EQUAL(res.size(), stdres.size());
        BOOST_REQUIRE(equal(res.begin(), res.end(), stdres.begin()));
    }

    {
        std::vector<value_t> stdres;
        stdres += 0.0, 0.0, 0.0, 3.5, 7, 12, 27.5, 45.5, 53, 0.0;

        auto res = velocity(make_vec(stdvec), 1.0, 0.0, 7.0, 1);
        BOOST_REQUIRE_EQUAL(res.size(), stdres.size());
        BOOST_REQUIRE(equal(res.begin(), res.end(), stdres.begin()));
    }
}

BOOST_AUTO_TEST_CASE(test_distance)
{
    using namespace boost::assign;

    std::vector<value_t> stdvec;
    stdvec += 1, -2, 6, 7, 3, 10, 21, 15, -5, 2;

    std::vector<value_t> stdres;
    stdres += 0.0, -0.5, 2, 6.5, 5, 6.5, 15.5, 18, 5, -1.5;
    partial_sum(stdres.begin(), stdres.end(), stdres.begin());

    {
        auto vel_vec = velocity(stdvec);
        BOOST_REQUIRE_CLOSE_FRACTION(distance(vel_vec, 2.0, 3), 2.0 * integration(stdres, 3), error);
    }

    {
        auto vel_vec = velocity(make_vec(stdvec));
        BOOST_REQUIRE_CLOSE_FRACTION(distance(vel_vec, 2.0, 3), 2.0 * integration(stdres, 3), error);
    }
}