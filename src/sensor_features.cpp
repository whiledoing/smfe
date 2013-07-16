#include "smfe/feature/sensor_features.hpp"

#include <vector>

typedef std::vector<smfe::value_t> stdvec;

namespace smfe
{
template
vec velocity<vec>(const vec& acce_data,
                  value_t delta,
                  value_t init_velocity,
                  value_t still_acce_threshold,
                  int station_count_threshold,
                  bool using_ave_filter,
                  int filter_size
                 );

template
stdvec velocity<stdvec>(const stdvec& acce_data,
                        value_t delta,
                        value_t init_velocity,
                        value_t still_acce_threshold,
                        int station_count_threshold,
                        bool using_ave_filter,
                        int filter_size
                       );
template
value_t distance(const vec& velocity_data,
                 value_t delta,
				 int degree,
                 bool using_ave_filter,
                 int filter_size
                );

template
value_t distance(const stdvec& velocity_data,
                 value_t delta,
				 int degree,
                 bool using_ave_filter,
                 int filter_size
                );
}