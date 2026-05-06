//
// Created by Alienson on 11.8.2024.
//

#include "SoundEngine.h"
#include <iostream>
#include "reference/Reference.h"
#include "reference/Global.h"

static int audioCallback(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);
static int audioCallbackMono(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void *);

SoundEngine::SoundEngine() {

    Global::soundEngine = this;

    PaError err = Pa_Initialize();
    if (err != paNoError){
        std::cout << err << "Pa_init";
        exit(1);
    }

    currentSong = playStream(Sounds::DEVASTATION, 0.2f);
}

SoundEngine::~SoundEngine() {
    delete currentSong;
    Pa_Terminate();
}

void SoundEngine::onUpdate(float deltaTime){

    if (onUpdateTimer > 0){
        onUpdateTimer-=deltaTime;
        return;
    }
    onUpdateTimer = 1.0f;

    for (auto & sound : soundsPlaying){
        if (sound == nullptr)
            continue;
        if(!Pa_IsStreamActive( sound->paStream )){
            stop(sound);
            delete sound;
            sound = nullptr;
        }
    }

    if(!Pa_IsStreamActive( currentSong->paStream )){
        stop(currentSong);
        delete currentSong;
        currentSong = playStream(Sounds::DEVASTATION, 0.2f);
    }
}

SoundInstance* SoundEngine::playStream(Sound *sound, float volume) {
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

    return soundInstance;
}

void SoundEngine::play(Sound *sound, float volume) {
    SoundInstance* soundInstance = playStream(sound, volume);

    bool soundAdded = false;
    for (auto &s : soundsPlaying){
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

// TODO need a function for getting exact offset in millis. Also does this logic belong here? Getting diff is correct,
//  but converting it to BeatOffsetEnum seems like application wide logic.
//  When beat occurs there should be event that. There also needs to be a guarantee that same beat is not processed twice
//  Maybe add a time frame for each beat and compare with that?
BeatOffset* SoundEngine::getBeatOffset() const {
    //TODO next/previous beat can be calculated from one, no need to calculate both
    unsigned long nextBeat = currentSong->getNextBeatOffset();
    unsigned long previousBeat = currentSong->getPreviousBeatOffset();
    //std::cout << "Next: " << nextBeat << '\n';
    //std::cout << "Prev: " << previousBeat << '\n';

    unsigned long current = currentSong->getOffset() / currentSong->getNumberOfChannels();
    /*std::cout << "Current: " << current << '\n';
    std::cout << "N-P: " << nextBeat - previousBeat << '\n';
    std::cout << "---------------------\n";*/


    int nextOffset = glm::abs((long)nextBeat - (long)current);
    int previousOffset = glm::abs((long)previousBeat - (long)current);
    //std::cout << "Next: " << nextOffset << '\n';
    //std::cout << "Prev: " << previousOffset << '\n';

    int missOffset = nextOffset < previousOffset ? nextOffset : previousOffset;
    //return (float)(missOffset) / (float)currentSong->getSampleRate() < 0.2f;
    //TODO maybe account for weapon audio delay, but then each weapon should have the same one so gameplay isn't affected
    return BeatOffset::from((float)missOffset / (float)currentSong->getSampleRate());
}

void SoundEngine::seek(int seconds) {
    currentSong->seek(seconds);
}

static inline void playFramesStereo(unsigned long frames, int16_t* outStream, SoundInstance* sound){
    for(size_t i=0; i<frames; i++ ){
        *outStream++ = sound->getNextValue() * sound->volume * Configuration::masterVolume;
        *outStream++ = sound->getNextValue() * sound->volume * Configuration::masterVolume;
    }
}


static int audioCallback( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData ){

    auto *out = (int16_t *)outputBuffer;
    auto *sound = (SoundInstance*)userData;

    if (sound->getOffset() + 2 * framesPerBuffer >= sound->getDataSize()){
        playFramesStereo((sound->getDataSize() - sound->getOffset()) / 2 - 1, out, sound);
        return paComplete;
    }

    playFramesStereo(framesPerBuffer, out, sound);
    return paContinue;
}

static int audioCallbackMono( const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData ){

    /*auto *out = (int16_t *)outputBuffer;
    auto *sound = (SoundInstance*)userData;

    if (sound->getOffset() + 2 * framesPerBuffer >= sound->getDataSize()){
        for(size_t i=0; i<sound->getDataSize() - sound->getOffset(); i++ ){
            *out++ = sound->getNextValue() * sound->volume * Configuration::masterVolume;
        }
        return paComplete;
    }
    for(size_t i=0; i<framesPerBuffer; i++ ){
        *out++ = sound->getNextValue() * sound->volume * Configuration::masterVolume;
    }

    return paContinue;*/
    return paComplete;
}

