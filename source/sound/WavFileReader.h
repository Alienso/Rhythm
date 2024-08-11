//
// Created by Alienson on 11.8.2024..
//

#ifndef RHYTHM_WAVFILEREADER_H
#define RHYTHM_WAVFILEREADER_H

#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <valarray>


typedef struct header_file{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;			// sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;			// subchunk2_size denotes the number of samples.
} header;

typedef struct header_file* header_p;


void readWav(const char* path, std::vector<int16_t>& audioData){
    FILE * infile = fopen(path,"rb");		// Open wave file in read mode
    //FILE * outfile = fopen("Output.wav","wb");		// Create output ( wave format) file in write mode

    constexpr int BUFSIZE = 512;					// BUFSIZE can be changed according to the frame size required (eg:512)
    int count = 0;						// For counting number of frames in wave file.
    int16_t buff16[BUFSIZE];				// short int used for 16 bit as input data format is 16 bit PCM audio
    header_p meta = (header_p)malloc(sizeof(header));	// header_p points to a header struct that contains the wave file metadata fields
    int nb;							// variable storing number of byes returned
    if (infile){
        fread(meta, 1, sizeof(header), infile);
        //fwrite(meta,1, sizeof(*meta), outfile);
        std::cout << " Size of Header file is "<<sizeof(*meta)<<" bytes" << std::endl;
        std::cout << " Sampling rate of the input wave file is "<< meta->sample_rate <<" Hz" << std::endl;
        std::cout << " Number of samples in wave file are " << meta->subchunk2_size << " samples" << std::endl;


        while (!feof(infile)){
            nb = fread(buff16, sizeof(int16_t), BUFSIZE / (sizeof(int16_t)), infile);
            //cout << nb <<endl;

            for (int i=0;i<nb;i++)
                audioData.push_back(buff16[i]);

            count++;					// Incrementing Number of frames

            //memcpy(song_data+count*BUFSIZ,buff16,nb);

            //fwrite(buff16,1,nb,outfile);			// Writing read data into output file
        }
        std::cout << " Number of frames in the input wave file are " <<count << std::endl;
        //fwrite(song_data,1,(count-1)*BUFSIZE,outfile);
        //fwrite(song_data,1,nb,outfile);
    }

    free(meta);
}

#endif //RHYTHM_WAVFILEREADER_H
