//
// Created by Alienso on 23.9.2022.
//

#ifndef GRASSTERRAIN_CONFIGURATION_H
#define GRASSTERRAIN_CONFIGURATION_H

class Configuration{

public:
    //Video
    static inline int windowWidth = 1600;
    static inline int windowHeight = 900;
    static inline float aspectRatio = (float)windowWidth / (float)windowHeight;

    //Mouse
    static float mouseSensitivity;

    //Keyboard
    static float jumpStrength;
    static float jumpBounciness;

    //Sound
    static float masterVolume;

    //Gameplay
    static unsigned int comboDecayAmount; //per second
    static float comboDecayDelay; //in seconds
    static float allowedBeatOffsetPerfect; // % of the second that beat can be off so it is considered perfect (0.01 = 10ms)
    static float allowedBeatOffsetGood; // % of the second that beat can be off so it is considered perfect (0.1 = 100ms)


    //Camera
    static float cameraFollowSpeed;
    static float cameraDeadZone;
    static float cameraBackgroundSpeed;

    //UI
    static float cursorScale; //Scale Percent

    //Physics
    static float gravityStrength;
    static float gravityFallMultiplier;
    static float maxYSpeed;
    static float maxXSpeed;

    Configuration()= default;
};

#endif //GRASSTERRAIN_CONFIGURATION_H
