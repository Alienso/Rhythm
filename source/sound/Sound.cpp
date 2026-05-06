//
// Created by Alienson on 11.8.2024.
//

#include <cstdio>
#include <iostream>
#include <cmath>
#include "Sound.h"

typedef struct __attribute__((packed)) WAV_HEADER {
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
} wav_hdr;

Sound::Sound(const char *path, unsigned int bpm, unsigned int initialOffset) : bpm(bpm), beatInitialOffset(initialOffset) {

    static unsigned int indexID = 0;
    ID = indexID++;

    FILE * infile = fopen(path,"rb");
    if (!infile){
        std::cout << "Could not open file: " << path << '\n';
        exit(1);
    }

    wav_hdr wavHeader;
    if (fread(&wavHeader, 1, sizeof(wav_hdr), infile) != sizeof(wav_hdr)){
        std::cout << "Could not read WAV header\n";
        exit(1);
    }

    size_t totalSamplesToRead = wavHeader.Subchunk2Size / sizeof(int16_t);
    audioData.reserve(wavHeader.Subchunk2Size / sizeof(int16_t));

    constexpr int BUFFER_SAMPLES  = 256;
    int16_t buff16[BUFFER_SAMPLES];

    double currentLoudness = 0, soundLoudness = 0;
    size_t sampleCount = 0;

    while (totalSamplesToRead > 0){
        //currentLoudness = 0;

        size_t chunk = totalSamplesToRead < BUFFER_SAMPLES ? totalSamplesToRead : BUFFER_SAMPLES;
        size_t samplesRead = fread(buff16, sizeof(int16_t), chunk, infile);

        if (samplesRead == 0)
            break;

        for (size_t i = 0; i < samplesRead; i++) {
            audioData.push_back(buff16[i]);
            //currentLoudness+=buff16[i] * buff16[i];
        }
        totalSamplesToRead -= samplesRead;

        //soundLoudness+= log10(sqrt(currentLoudness / (double)bytesRead));
        //sampleCount+=bytesRead;
    }

    //soundLoudness /= (double)sampleCount;
    //soundLoudness = log10(sqrt(currentLoudness / (double)sampleCount));

    sampleRate = wavHeader.SamplesPerSec;
    numChannels = wavHeader.NumOfChan;

    //std::cout << "Audio file: " << path << " loaded\n";
    //std::cout << "Loudness: " << soundLoudness << '\n';
    //std::cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << '\n';
    //std::cout << "Number of channels         :" << wavHeader.NumOfChan << '\n';
}

SoundInstance::SoundInstance(Sound *sound, float volume) : volume(volume), sound(sound) {
    spb = 60.0f/(float)sound->bpm;
}

size_t SoundInstance::getDataSize() const {
    return sound->audioData.size();
}

int16_t SoundInstance::getNextValue() {
    return sound->audioData[offset++];
}

unsigned long SoundInstance::getOffset() const {
    return offset;
}

unsigned int SoundInstance::getNumberOfChannels() const{
    return sound->numChannels;
}

unsigned int SoundInstance::getSampleRate() const {
    return sound->sampleRate;
}

unsigned long SoundInstance::getNextBeatOffset() const{
    float currentSecond = offset/sound->numChannels * 1.0f /sound->sampleRate;
    float nextBeat = currentSecond - fmodf(currentSecond - sound->beatInitialOffset * 1.0f / sound->sampleRate, spb)+ spb;
    unsigned long ret = nextBeat * sound->sampleRate;
    if (ret < offset/sound->numChannels){
        std::cout << "Err: Next < Current: " << ret << " " << offset/sound->numChannels << '\n';
    }
    return ret;
}

unsigned long SoundInstance::getPreviousBeatOffset() const{
    float currentSecond = offset/sound->numChannels * 1.0f / sound->sampleRate;
    float previousBeat = currentSecond - fmodf(currentSecond - sound->beatInitialOffset * 1.0f / sound->sampleRate, spb);
    unsigned long ret = previousBeat * sound->sampleRate;
    if (ret > offset/sound->numChannels){
        std::cout << "Err: Prev > Current: " << ret << " " << offset/sound->numChannels << '\n';
    }
    return ret;
}

void SoundInstance::seek(int seconds) {
    offset += seconds * sound->sampleRate * sound->numChannels;
}
