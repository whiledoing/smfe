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

#include "common_test.h"
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

    auto data = make_vec(test_data);

    int filter_size = 2;
    {
        value_t result = smfe::mean_filter_get_one_index(data, filter_size, 0);
        BOOST_REQUIRE_CLOSE_FRACTION(result, smfe::mean(make_sub_range(data, 0, filter_size+1)), error);
    }
    {
        auto result = smfe::mean_filter_get_one_index(data, filter_size, 1);
        BOOST_REQUIRE_CLOSE_FRACTION(result, smfe::mean(make_sub_range(data, 0, filter_size+2)), error);
    }
    {
        auto result = smfe::mean_filter_get_one_index(data, filter_size, 2);
        BOOST_REQUIRE_CLOSE_FRACTION(result, smfe::mean(make_sub_range(data, 0, filter_size+3)), error);
    }
    {
        auto result = smfe::mean_filter_get_one_index(data, filter_size, 5);
        BOOST_REQUIRE_CLOSE_FRACTION(result, smfe::mean(make_sub_range(data, 5-filter_size, 6+filter_size)), error);
    }
    {
        auto result = smfe::mean_filter_get_one_index(data, filter_size, size-1-filter_size);
        BOOST_REQUIRE_CLOSE_FRACTION(result, smfe::mean(make_sub_range(data, size-1-2*filter_size, size)), error);
    }
    {
        auto result = smfe::mean_filter_get_one_index(data, filter_size, size-filter_size);
        BOOST_REQUIRE_CLOSE_FRACTION(result, smfe::mean(make_sub_range(data, size-2*filter_size, size)), error);
    }
    {
        auto result = smfe::mean_filter_get_one_index(data, filter_size, size+1-filter_size);
        BOOST_REQUIRE_CLOSE_FRACTION(result, smfe::mean(make_sub_range(data, size+1-2*filter_size, size)), error);
    }

    // test smfe::mean_filter_get_range
    auto result = smfe::mean_filter_get_range(data, filter_size, 0, data.size());
    BOOST_REQUIRE_CLOSE_FRACTION(result[0], smfe::mean(make_sub_range(data, 0, 1+filter_size)), error);
    BOOST_REQUIRE_CLOSE_FRACTION(result[1], smfe::mean(make_sub_range(data, 0, 2+filter_size)), error);
    BOOST_REQUIRE_CLOSE_FRACTION(result[2], smfe::mean(make_sub_range(data, 0, 3+filter_size)), error);
    BOOST_REQUIRE_CLOSE_FRACTION(result[4], smfe::mean(make_sub_range(data, 4-filter_size, 5+filter_size)), error);
    BOOST_REQUIRE_CLOSE_FRACTION(result[size-filter_size], smfe::mean(make_sub_range(data, size-2*filter_size, size)), error);

    {
        int filter_size = 0;
        auto result = smfe::mean_filter_get_range(data, filter_size, 0, data.size());
        BOOST_REQUIRE(equal(data.begin(), data.end(), result.begin()));
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

        auto res = velocity(make_vec(stdvec));
        BOOST_REQUIRE_EQUAL(res, stdres.back());
    }

    {
        std::vector<value_t> stdres;
        stdres += 0.0, 0.0, 3, 6.5, 5, 6.5, 15.5, 18, 5, -2.5;
        partial_sum(stdres.begin(), stdres.end(), stdres.begin());

        auto res = velocity(make_vec(stdvec), 1.0, 0.0, 3.0);
        BOOST_REQUIRE_EQUAL(res, stdres.back());
    }

    {
        std::vector<value_t> stdres;
        stdres += 0.0, 0.0, 3, 6.5, 5, 6.5, 15.5, 18, 5, -2.5;
        partial_sum(stdres.begin(), stdres.end(), stdres.begin());

        auto res = velocity(make_vec(stdvec), 1.0, 0.0, 3.0);
        BOOST_REQUIRE_EQUAL(res, stdres.back());
    }

    {
        std::vector<value_t> stdres;
        stdres += 0.0, 0.0, 0.0, 3.5, 7, 12, 27.5, 45.5, 53, 0.0;

        auto res = velocity(make_vec(stdvec), 1.0, 0.0, 7.0, 1);
        BOOST_REQUIRE_EQUAL(res, stdres.back());
    }
}

BOOST_AUTO_TEST_CASE(test_distance)
{
    using namespace boost::assign;

    std::vector<value_t> stdvec;
    stdvec += 1, -2, 6, 7, 3, 10, 21, 15, -5, 2;

    std::vector<value_t> stdres;
    stdres += 0.0, -1.0, 4.0, 13.0, 10.0, 13.0, 31.0, 36.0, 10.0, -3.0;
    partial_sum(stdres.begin(), stdres.end(), stdres.begin());

    BOOST_REQUIRE_CLOSE_FRACTION(distance(make_vec(stdvec), 2.0), 2.0 * integration(stdres, 3), error);
}

BOOST_AUTO_TEST_CASE(test_rotate_vector)
{
    auto v = make_3dvec(10, 20, 30.33);
    smfe_normalise_vec(v);

    {
        // 单位四元数
        auto res = rotate_vector(smfe_identity_rot, v);
        check_vec_equal(res, v);
    }

    {
		// x轴90度
        auto unit_y = make_3dvec(0, 1, 0);
		auto unit_x = make_3dvec(1, 0, 0);
        auto rot_x_90 = make_rotate(0.5 * 3.1415926, unit_x);

		auto res = rotate_vector(rot_x_90, unit_y);
		check_vec_equal(res, make_3dvec(0.0, 0.0, 1.0));
    }

    {
		// random rot and vec, result got frm ogre library
		auto rot = make_rotate(10, 20, 30, 1.0);
		smfe_normalise_vec(rot);

		auto vec = make_3dvec(3, 2, 1);
		smfe_normalise_vec(vec);

		auto res = rotate_vector(rot, vec);
		check_vec_equal(res, make_3dvec(0.342804, 0.861875, -0.373708));
	}
}