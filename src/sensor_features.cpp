#include "smfe/feature/sensor_features.hpp"

#include <vector>

namespace smfe
{
typedef std::vector<value_t> stdvec;

template<>
vec velocity<vec>(const vec& acce_data,
                  value_t scale_factor,
                  value_t still_acce_threshold,
                  int station_count_threshold,
                  value_t init_velocity,
                  bool using_ave_filter,
                  int filter_size
                 );

template<>
stdvec velocity<stdvec>(const stdvec& acce_data,
                        value_t scale_factor,
                        value_t still_acce_threshold,
                        int station_count_threshold,
                        value_t init_velocity,
                        bool using_ave_filter,
                        int filter_size
                       );

template<>
value_t distance(const vec& velocity_data,
                 value_t scale_factor,
                 bool using_ave_filter,
                 int filter_size
                );

template<>
value_t distance(const stdvec& velocity_data,
                 value_t scale_factor,
                 bool using_ave_filter,
                 int filter_size
                );
}
