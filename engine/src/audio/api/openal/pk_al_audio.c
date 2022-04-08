

// TODO(parsecffo): Remove this
#include <memory.h>
#include <stdio.h>

// TODO(parsecffo): Remove this
#include <windows.h>

#include "audio/pk_audio.h"
#include "core/pk_logger.h"
#include "core/pk_memory.h"

typedef struct WAV_HEADER {
    /* RIFF Chunk Descriptor */
    u8 RIFF[4];     // RIFF Header Magic header
    u32 ChunkSize;  // RIFF Chunk Size
    u8 WAVE[4];     // WAVE Header
    /* "fmt" sub-chunk */
    u8 fmt[4];          // FMT header
    u32 Subchunk1Size;  // Size of the fmt chunk
    u16 AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    u16 NumOfChan;      // Number of channels 1=Mono 2=Sterio
    u32 SamplesPerSec;  // Sampling Frequency in Hz
    u32 bytesPerSec;    // bytes per second
    u16 blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    u16 bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    u8 Subchunk2ID[4];  // "data"  string
    u32 Subchunk2Size;  // Sampled data length
} wav_hdr;

// Function prototypes
int get_file_size(FILE* in_file);

internal b8
audio_initialize() {
    wav_hdr wav_header;
    i32 header_size = sizeof(wav_hdr);
    i32 file_length = 0;

    const char* file_path = "C:\\Projects\\pekora\\2.wav";

    FILE* wav_file = fopen(file_path, "r");
    if (wav_file == (void*)0) {
        return false;
    }

    // Read the header
    u64 bytes_read = fread(&wav_header, 1, header_size, wav_file);
    file_length = get_file_size(wav_file);

    if (bytes_read > 0) {
        // Read the data
        // u16 bytes_per_sample = wav_header.bitsPerSample / 8;        // Number     of bytes per sample
        // u64 num_samples = wav_header.ChunkSize / bytes_per_sample;  // How many samples are in the wav file?

        void* block = malloc(file_length);
        memset(block, 0, file_length);
        i8* file_buffer = (i8*)block;

        while ((bytes_read = fread(file_buffer, sizeof file_buffer[0], file_length / (sizeof file_buffer[0]), wav_file)) > 0) {
        }
    }
    fclose(wav_file);

    return true;
}

internal b8
audio_shutdow() {
    return true;
}

// find the file size
int get_file_size(FILE* in_file) {
    int fileSize = 0;
    fseek(in_file, 0, SEEK_END);

    fileSize = ftell(in_file);

    fseek(in_file, 0, SEEK_SET);
    return fileSize;
}