
#ifndef SOUND_SYSTEM_AUDIO_EXTRACTOR_SYNCHRONOUS_FFMPEG_EXTRACTOR_H
#define SOUND_SYSTEM_AUDIO_EXTRACTOR_SYNCHRONOUS_FFMPEG_EXTRACTOR_H

#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <media/NdkMediaCodec.h>
#include <media/NdkMediaExtractor.h>

#include <audio/SoundSystem.h>

#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>

class SynchronousFfmpegExtractor {
public:

    SynchronousFfmpegExtractor(SoundSystem *soundSystem, const unsigned short frameRate);

    ~SynchronousFfmpegExtractor();

    bool extract(const char *path);

private:

    const unsigned short _frameRate;
    short *_extractedData;
    int32_t _file_sample_rate;
    int32_t _file_number_channels;
    int64_t _file_duration;
    unsigned int _file_total_frames;
    int _size;
    SoundSystem *_soundSystem;

    void extractMetadata(
            const AVFormatContext *format,
            const AVCodecContext *codec);

    int decodeAudioFile(
            AVFormatContext *format,
            AVStream *stream,
            AVCodecContext *codec,
            short **data,
            int *size);
};

#endif // SOUND_SYSTEM_AUDIO_EXTRACTOR_SYNCHRONOUS_FFMPEG_EXTRACTOR_H
