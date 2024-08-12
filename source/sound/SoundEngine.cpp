//
// Created by Alienson on 11.8.2024..
//

#include "SoundEngine.h"
#include "iostream"
#include "Assets.h"

static int audioCallback( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData );

SoundEngine::SoundEngine() {
    PaError err = Pa_Initialize();
    if (err != paNoError){
        std::cout << "Pa_init";
        exit(1);
    }

    play(Sounds::MTYN);
}

SoundEngine::~SoundEngine() {
    Pa_Terminate();
}

void SoundEngine::play(Sound *sound) {

    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice) {
        std::cout << "Error: No default output device.\n";
        exit(1);
    }
    outputParameters.channelCount = sound->numChannels;
    outputParameters.sampleFormat = paInt16;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    auto* soundInstance = new SoundInstance(sound);
    PaError err = Pa_OpenStream(
            &soundInstance->paStream,
            nullptr,
            &outputParameters,
            sound->sampleRate,
            FRAMES_PER_BUFFER,
            0,
            audioCallback,
            soundInstance );
    if( err != paNoError ) exit(1);

    err = Pa_StartStream( soundInstance->paStream );
    if( err != paNoError ) exit(1);
}

void SoundEngine::stop(SoundInstance* sound) { //TODO
    PaError err = Pa_CloseStream( sound->paStream );
    if( err != paNoError ) exit(1);
}

void SoundEngine::pause(SoundInstance* sound) {
}

static int audioCallback( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData ){

    unsigned int i;
    auto *out = (int16_t *)outputBuffer;
    auto *sound = (SoundInstance*)userData;
    if (sound->getOffset() + framesPerBuffer >= sound->getDataSize()){
        PaError err = Pa_CloseStream( sound->paStream );
        if( err != paNoError ) exit(1);
        return paComplete;
    }
    for( i=0; i<framesPerBuffer; i++ ){
        *out++ = sound->getNextValue();
        *out++ = sound->getNextValue();
    }

    return paContinue;
}

