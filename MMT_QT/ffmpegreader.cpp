#include "ffmpegreader.h"

#include "vfpimagehelper.h"

FFMPEGReader::FFMPEGReader()
{
    // Register all available file formats and codecs
    av_register_all();

    width = 0;
    height = 0;
    duration = 0;
    frameRate = 0;
    grabFrame = NULL;
}

int FFMPEGReader::OpenFile(const char* filename)
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

    swsContext = sws_getContext(codec_context->width,
                                codec_context->height,
                                codec_context->pix_fmt,
                                codec_context->width,
                                codec_context->height,
                                AV_PIX_FMT_BGR24,
                                SWS_BICUBIC,
                                NULL,
                                NULL,
                                NULL);

    if (swsContext == NULL)
    {
        fprintf(stderr, "Cannot initialize the conversion context\n");
        return -1;
    }

    frame = avcodec_alloc_frame();

    frameRgb.linesize[0] = codec_context->width * 3;
    frameRgb.data[0]     = (uint8_t*)malloc( frameRgb.linesize[0] * codec_context->height );

    frameRate = av_q2d(format_context->streams[video_stream]->avg_frame_rate);

    return 0;
}

double FFMPEGReader::GetFrameRate()
{
    return frameRate;
}

int64_t FFMPEGReader::GetDuration()
{
    return duration;
}

int FFMPEGReader::GetWidth()
{
    return width;
}

int FFMPEGReader::GetHeight()
{
    return height;
}

bool FFMPEGReader::GrabFrame(BYTE** videoFrame, int* step, int64_t* timestamp)
{
    *timestamp = 0;
    *step = 0;

    while (av_read_frame(format_context, &packet) >= 0)
    {
        if (packet.stream_index == video_stream)
        {
            int frame_finished;
            avcodec_decode_video2(codec_context, frame, &frame_finished, &packet);

            if (frame_finished)
            {
                double pts = frame->pkt_dts;
                if (pts == AV_NOPTS_VALUE) {
                    pts = frame->pkt_pts;
                }

                if (pts == AV_NOPTS_VALUE) {
                    pts = 0;
                }

                pts *= av_q2d(format_context->streams[video_stream]->time_base);
                int64_t ts = (int64_t)(pts * 1000);

                *timestamp = ts;

                sws_scale(swsContext, frame->data, frame->linesize, 0, codec_context->height, frameRgb.data, frameRgb.linesize);

                *videoFrame = frameRgb.data[0];

                *step = frameRgb.linesize[0];

                // Free the packet that was allocated by av_read_frame
                av_free_packet(&packet);

                return true;
            }

            // Free the packet that was allocated by av_read_frame
            av_free_packet(&packet);
        }
    }

    return false;
}

void FFMPEGReader::CloseFile()
{
    sws_freeContext(swsContext);

    // Free the YUV frame
    av_free(frame);

    // Close the codec
    avcodec_close(codec_context);

    // Close the video file
    avformat_close_input(&format_context);

    if (grabFrame != NULL)
    {
        free(grabFrame);
        grabFrame = NULL;
    }
}
