//
// Created by Alienson on 11.8.2024..
//

#include "SoundEngine.h"
#include "iostream"
#include "reference/Reference.h"

static int audioCallback(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);
static int audioCallbackMono(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);

SoundEngine::SoundEngine() {
    PaError err = Pa_Initialize();
    if (err != paNoError){
        std::cout << err << "Pa_init";
        exit(1);
    }

    for (auto & i : soundsPlaying)
        i = nullptr;

    //play(Sounds::MTYN);
}

SoundEngine::~SoundEngine() {
    Pa_Terminate();
}

void SoundEngine::onUpdate(float deltaTime){

    if (onUpdateTimer > 0){
        onUpdateTimer-=deltaTime;
        return;
    }
    onUpdateTimer = 1.0f;

    for (auto & sound : soundsPlaying){
        if (sound != nullptr){
            if(!Pa_IsStreamActive( sound->paStream )){
                stop(sound);
                delete sound;
                sound = nullptr;
            }
        }
    }
}

void SoundEngine::play(Sound *sound, float volume) {

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

    auto* soundInstance = new SoundInstance(sound, volume);
    int (*callbackFunction) (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);
    callbackFunction = sound->numChannels == 1 ? audioCallbackMono : audioCallback;

    PaError err = Pa_OpenStream(
            &soundInstance->paStream,
            nullptr,
            &outputParameters,
            sound->sampleRate,
            FRAMES_PER_BUFFER,
            0,
            callbackFunction,
            soundInstance );
    if( err != paNoError ){
        std::cout << err << "Pa_Open\n";
        exit(1);
    }

    err = Pa_StartStream( soundInstance->paStream );
    if( err != paNoError ){
        std::cout << err << "Pa_Start\n";
        exit(1);
    }

    bool soundAdded = false;
    for (auto & s : soundsPlaying){
        if (s == nullptr){
            s = soundInstance;
            soundAdded = true;
            break;
        }
    }
    if (!soundAdded){
        soundsPlaying.push_back(soundInstance);
    }

}

void SoundEngine::stop(SoundInstance* sound) {
    PaError err = Pa_CloseStream( sound->paStream );
    if( err != paNoError ) {
        std::cout << err << "Pa_Close\n";
        exit(1);
    }
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
    if (sound->getOffset() + 2 * framesPerBuffer >= sound->getDataSize()){ //TODO some frames are not being played (< 2*framesPerBuffer)
        return paComplete;
    }
    for( i=0; i<framesPerBuffer; i++ ){
        *out++ = sound->getNextValue() * sound->volume;
        *out++ = sound->getNextValue() * sound->volume;
    }

    return paContinue;
}

static int audioCallbackMono( const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData ){

    unsigned int i;
    auto *out = (int16_t *)outputBuffer;
    auto *sound = (SoundInstance*)userData;
    if (sound->getOffset() + 2 * framesPerBuffer >= sound->getDataSize()){ //TODO some frames are not being played (< 2*framesPerBuffer)
        return paComplete;
    }
    for( i=0; i<framesPerBuffer; i++ ){
        *out++ = sound->getNextValue() * sound->volume;
    }

    return paContinue;
}

