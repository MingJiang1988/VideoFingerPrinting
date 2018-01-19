#ifndef FFMPEGREADER_H
#define FFMPEGREADER_H

#include "vfptypes.h"

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class FFMPEGReader
{
public:
    FFMPEGReader();

    int OpenFile(const char* filename);
    void CloseFile();
    bool GrabFrame(BYTE** videoFrame, int* step, int64_t* timestamp);
    double GetFrameRate();
    int64_t GetDuration();
    int GetWidth();
    int GetHeight();
private:
    AVFormatContext* format_context;
    AVCodecContext* codec_context;
    AVCodec* codec;
    struct SwsContext *swsContext;
    AVFrame* frame;
    AVPicture frameRgb;
    AVPacket packet;
    uint video_stream;
    int64_t duration;
    double frameRate;
    int width;
    int height;
    u_int8_t* grabFrame;
};

#endif // FFMPEGREADER_H
