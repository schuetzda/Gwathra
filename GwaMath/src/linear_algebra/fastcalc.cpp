#include "fastcalc.h"
#include <cstdint>

namespace gwm {

    const float fast_rsqrt(const float number) {
        //https://stackoverflow.com/questions/12923657/is-there-a-fast-c-or-c-standard-library-function-for-double-precision-inverse

        union {
            float f;
            uint32_t i;
        } conv;

        float x2;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        conv.f = number;
        conv.i = 0x5f3759df - (conv.i >> 1);
        conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f));
        return conv.f;
    }
}