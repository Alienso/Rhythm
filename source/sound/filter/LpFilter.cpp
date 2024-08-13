//
// Created by Alienson on 13.8.2024..
//

#include <complex>
#include "LpFilter.h"

int16_t LpFilter::process(int16_t input){
    float output = input * a0 + z1;
    z1 = input * a1 + z2 - b1 * output;
    z2 = input * a2 + z3 - b2 * output;
    z3 = input * a3 - b3 * output;
    p0 = p1; p1 = p2; p2 = input;
    return (int16_t)output;
}
