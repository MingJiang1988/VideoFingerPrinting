#ifndef FFMPEGFILEINFO_H
#define FFMPEGFILEINFO_H

#include "vfptypes.h"

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

}

class FFMPEGFileInfo
{
private:
    AVFormatContext* format_context;
    AVCodecContext* codec_context;
    AVCodec* codec;
    AVPacket packet;

    uint video_stream;
    int64_t duration;
    double frameRate;
    int width;
    int height;
public:
    FFMPEGFileInfo();

    int ReadFile(const char* filename);

    double GetFrameRate();
    int64_t GetDuration();
    int GetWidth();
    int GetHeight();
};

#endif // FFMPEGFILEINFO_H
