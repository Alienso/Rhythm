//
// Created by Alienso on 23.9.2022.
//
#include "Configuration.h"

//Video
/*int Configuration:: windowWidth = 900;
int Configuration:: windowHeight = 900;
float Configuration::aspectRatio = (float)Configuration::windowWidth / (float)Configuration::windowHeight;*/

//Mouse
float Configuration::mouseSensitivity = 1.0f;

//Keyboard
float Configuration::jumpStrength = 3.5f;
float Configuration::jumpBounciness = 3.0f;

//Sound
float Configuration::masterVolume = 1.0f;

//Gameplay
float Configuration::comboDecayDelay = 2.0f;
unsigned int Configuration::comboDecayAmount = 10;
float Configuration::allowedBeatOffsetPerfect = 0.01f;
float Configuration::allowedBeatOffsetGood = 0.1f;

//Camera
float Configuration::cameraDeadZone = 0.25;
float Configuration::cameraFollowSpeed = 4.0f;
float Configuration::cameraBackgroundSpeed = 0.3f;

//UI
float Configuration::cursorScale = 1.0;

//Physics
float Configuration::gravityStrength = 9.81f;
float Configuration::gravityFallMultiplier = 1.5f;
float Configuration::maxXSpeed = 10.0;
float Configuration::maxYSpeed = 10.0;