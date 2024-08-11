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
    outputParameters.hostApiSpecificStreamInfo = NULL;

    PaError err = Pa_OpenStream(
            &sound->paStream,
            NULL,
            &outputParameters,
            sound->sampleRate,
            FRAMES_PER_BUFFER,
            0,
            audioCallback,
            sound );
    if( err != paNoError ) exit(1);

    err = Pa_StartStream( sound->paStream );
    if( err != paNoError ) exit(1);
}

void SoundEngine::stop(Sound* sound) {
    PaError err = Pa_CloseStream( sound->paStream );
    if( err != paNoError ) exit(1);
}

void SoundEngine::pause(Sound* sound) {
}

static int audioCallback( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData ){

    unsigned int i;
    auto *out = (int16_t *)outputBuffer;
    auto *sound = (Sound*)userData;
    if (sound->dataIndex + framesPerBuffer >= sound->audioData.size()){ //TODO check
        return paComplete;
    }
    for( i=0; i<framesPerBuffer; i++ ){
        *out++ = sound->audioData[sound->dataIndex++];
        *out++ = sound->audioData[sound->dataIndex++];
    }

    return paContinue;
}

