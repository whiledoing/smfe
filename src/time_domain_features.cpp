#include "smfe/time_domain_features.h"

#include <iostream>

#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"

namespace smfe
{

void f()
{
    vec data("2 7 4 9 3");

    value_t res = skewness(data);
}

}