//
// Created by Alienso on 23.9.2022..
//

#ifndef GRASSTERRAIN_CONFIGURATION_H
#define GRASSTERRAIN_CONFIGURATION_H

class Configuration{

public:
    static inline int windowWidth = 1600;
    static inline int windowHeight = 900;
    static inline float aspectRatio = (float)windowWidth / (float)windowHeight;
    static float mouseSensitivity;

    static float masterVolume;

    static unsigned int comboDecayAmount; //per second
    static float comboDecayDelay; //in seconds

    Configuration()= default;
};

#endif //GRASSTERRAIN_CONFIGURATION_H
