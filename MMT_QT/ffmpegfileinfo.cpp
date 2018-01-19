#include "ffmpegfileinfo.h"

FFMPEGFileInfo::FFMPEGFileInfo()
{
    // Register all available file formats and codecs
    av_register_all();

    width = 0;
    height = 0;
    duration = 0;
    frameRate = 0;
}

int FFMPEGFileInfo::ReadFile(const char* filename)
{
    int err;

    // Open video file
    format_context = NULL;
    err = avformat_open_input(&format_context, filename, NULL, NULL);
    if (err < 0)
    {
        fprintf(stderr, "ffmpeg: Unable to open input file\n");
        return -1;
    }

    // Retrieve stream information
    err = avformat_find_stream_info(format_context, NULL);
    if (err < 0)
    {
        fprintf(stderr, "ffmpeg: Unable to find stream info\n");
        return -1;
    }

    duration = format_context->duration / 1000;

    // Dump information about file onto standard error
    av_dump_format(format_context, 0, filename, 0);

    // Find the first video stream
    for (video_stream = 0; video_stream < format_context->nb_streams; ++video_stream)
    {
        if (format_context->streams[video_stream]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            break;
        }
    }

    if (video_stream == format_context->nb_streams)
    {
        fprintf(stderr, "ffmpeg: Unable to find video stream\n");
        return -1;
    }

    codec_context = format_context->streams[video_stream]->codec;
    codec = avcodec_find_decoder(codec_context->codec_id);
    err = avcodec_open2(codec_context, codec, NULL);
    if (err < 0)
    {
        fprintf(stderr, "ffmpeg: Unable to open codec\n");
        return -1;
    }

    width = codec_context->width;
    height = codec_context->height;

    frameRate = av_q2d(format_context->streams[video_stream]->avg_frame_rate);

    // Close the codec
    avcodec_close(codec_context);

    // Close the video file
    avformat_close_input(&format_context);

    return 0;
}

double FFMPEGFileInfo::GetFrameRate()
{
    return frameRate;
}

int64_t FFMPEGFileInfo::GetDuration()
{
    return duration;
}

int FFMPEGFileInfo::GetWidth()
{
    return width;
}

int FFMPEGFileInfo::GetHeight()
{
    return height;
}
