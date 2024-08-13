//
// Created by Alienson on 13.8.2024..
//

#ifndef RHYTHM_LPFILTER_H
#define RHYTHM_LPFILTER_H

class LpFilter {

public:
    static int16_t process(int16_t input);

    static constexpr float Wc = 0.01f; // cutoff frequency in rad/s
    static inline float K = std::tan(M_PI * Wc);
    static inline float norm = 1 / (K*K*K + 2*K*K + 2*K + 1);

    static inline float a0 = K*K*K*norm;
    static inline float a1 = 3 * a0;
    static inline float a2 = a1;
    static inline float a3 = a0;
    static inline float b1 = (3*K*K*K + 2*K*K - 2*K - 3) * norm;
    static inline float b2 = (3*K*K*K - 2*K*K - 2*K + 3) * norm;
    static inline float b3 = (K*K*K - 2*K*K + 2*K - 1) * norm;
    static inline float z1,z2,z3;
    static inline float p0,p1,p2;

};


#endif //RHYTHM_LPFILTER_H
