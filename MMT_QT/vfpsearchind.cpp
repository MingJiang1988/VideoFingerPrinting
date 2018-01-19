#include <stdio.h>
#include <stdlib.h>

#include "vfpsearchind.h"
#include "vfpimagehelper.h"

#include "VisioForge_VFP_Types.h"
#include <iostream>
#include <fstream>


#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

extern "C"
{
#define HAVE_FFMPEG_SWSCALE 1
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

#include "ffmpegreader.h"


using namespace std;


bool GetImageSize(const char *fn, int *x,int *y)
{
    FILE *f=fopen(fn,"rb");
    if (f==0) return false;
    fseek(f,0,SEEK_END);
    long len=ftell(f);
    fseek(f,0,SEEK_SET);
    if (len<24) {
        fclose(f);
        return false;
        }
    cout << fn << endl;
  // Strategy:
  // reading GIF dimensions requires the first 10 bytes of the file
  // reading PNG dimensions requires the first 24 bytes of the file
  // reading JPEG dimensions requires scanning through jpeg chunks
  // In all formats, the file is at least 24 bytes big, so we'll read that always
  unsigned char buf[24]; fread(buf,1,24,f);

  // For JPEGs, we need to read the first 12 bytes of each chunk.
  // We'll read those 12 bytes at buf+2...buf+14, i.e. overwriting the existing buf.
  if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F')
  { long pos=2;
    while (buf[2]==0xFF)
    { if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB) break;
      pos += 2+(buf[4]<<8)+buf[5];
      if (pos+12>len) break;
      fseek(f,pos,SEEK_SET); fread(buf+2,1,12,f);
    }
  }

  fclose(f);

  // JPEG: (first two bytes of buf are first two bytes of the jpeg file; rest of buf is the DCT frame
  if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF)
  { *y = (buf[7]<<8) + buf[8];
    *x = (buf[9]<<8) + buf[10];
    //cout << *x << endl;
    return true;
  }

  // GIF: first three bytes say "GIF", next three give version number. Then dimensions
  if (buf[0]=='G' && buf[1]=='I' && buf[2]=='F')
  { *x = buf[6] + (buf[7]<<8);
    *y = buf[8] + (buf[9]<<8);
    return true;
  }

  // PNG: the first frame is by definition an IHDR frame, which gives dimensions
  if ( buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' && buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A && buf[6]==0x1A && buf[7]==0x0A
    && buf[12]=='I' && buf[13]=='H' && buf[14]=='D' && buf[15]=='R')
  { *x = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);
    *y = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);
    return true;
  }

  return false;
}


int ifpsearchind(const char* imagefile, const char* destFile, int pos, int length)
{
//    const char *theFile = imagefile;
//    int the_x =0;
//    int the_y =0;
//    bool didRun = false;

//    didRun = GetImageSize(theFile, &the_x, &the_y);

//      cout << "Dimensions: " << the_x << " x " << the_y << endl;
//    VFS_TMP* vfp = new VFS_TMP();
//    int wData = the_x;
//    int hData = the_y;
//    int wStep = 1;
//    int64_t timestamp = 1000;
//    BYTE* img = NULL;



//    //Do what ever with buffer
//    img = buf;


//    VFPImageHelper helper;
//    helper.SaveImage24(img, wData, hData, "image.bmp");
//    VFPSearch_Process(img, wData, hData, wStep, timestamp, vfp);

//    int n = 0;
//    char* p = VFPSearch_Build(&n, vfp);
//    cout << n << endl;
//    if(n)
//    {
//        cout << "sssss" << endl;
//        FILE* pFile = fopen(destFile, "w+b");

//        int i=0;
//        for(i=0; i<n; i += fwrite(p+i, 1, n-i, pFile))
//        {

//        }
//        fclose(pFile);
//    }
    return 1;
}

int vfpsearchind(const char* sourceFile, const char* destFile, int pos, int length)
{

    //	if(argc!=5)
    //        {
    //		printf("\nUsage: index SOURCE DEST POS LENG\n\n");
    //		printf("Index LENG seconds of a SOURCE video, starting from POS, and store signature to the DEST.\n\n");
    //		return 1;
    //	}

    const char* pPathI = sourceFile; // argv[1];
    const char* pPathO = destFile; // argv[2];

    int start = pos; // atoi(argv[3]);
    int count = length; // atoi(argv[4]);

    VFS_TMP* vfp = new VFS_TMP();
    VFPSearch_Init(count, vfp);

    try
    {
        FFMPEGReader ffmpegReader;
        int hr = ffmpegReader.OpenFile(pPathI);

        //CvCapture_FFMPEG* pCapture = cvCreateFileCapture_FFMPEG(, start, count);
        if(hr != 0)
        {
            ffmpegReader.CloseFile();
            return 1;
        }

//        if(!cvGrabFrame_FFMPEG(pCapture))
//        {
//            cvReleaseCapture_FFMPEG(&pCapture);
//            return 1;
//        }

        //unsigned char* pData = NULL;
        int            wStep = 0;
        int            wData = ffmpegReader.GetWidth();
        int            hData = ffmpegReader.GetHeight();
//        int            nChannels = 0;

//        if(!cvRetrieveFrame_FFMPEG(pCapture, &pData, &wStep, &wData, &hData, &nChannels))
//        {
//            cvReleaseCapture_FFMPEG(&pCapture);
//            return 1;
//        }

        double fps = ffmpegReader.GetFrameRate();
        //        cvGetCaptureProperty_FFMPEG(pCapture, CV_FFMPEG_CAP_PROP_FPS);
        if(fps<=0)
        {
            ffmpegReader.CloseFile();
            //cvReleaseCapture_FFMPEG(&pCapture);
            return 1;
        }

        int iFrame = 1;
        //double dTime = 0;
        double dEnd = (double)(start + count);
        int64_t timestamp = 0;

        while(timestamp < dEnd * 1000)
        {
            BYTE* frame = NULL;

            ffmpegReader.GrabFrame(&frame, &wStep, &timestamp);
            if(frame == NULL)
            {
                printf("warning: reached the end before indexing finished\n");
                break;
            }

            //VFPImageHelper helper;
            //helper.SaveImage24(frame, wData, hData, "v.bmp");

            //dTime = (double)timestamp / 1000.0; //((double)iFrame)/fps;
            if(timestamp >= start * 1000)
            {
                VFPSearch_Process(frame, wData, hData, wStep, timestamp, vfp);
                //VFPSearch_Process(frame, wData, hData, wStep, dTime * 1000, vfp);
            }

            iFrame++;
        }

        ffmpegReader.CloseFile();
        //cvReleaseCapture_FFMPEG(&pCapture);

        int n = 0;
        char* p = VFPSearch_Build(&n, vfp);
        if(n)
        {
            FILE* pFile = fopen(pPathO, "w+b");

            int i=0;
            for(i=0; i<n; i += fwrite(p+i, 1, n-i, pFile))
            {

            }
            fclose(pFile);
        }
    }
    catch(...)
    {
        return 0;
    }


    VFPSearch_Clear(vfp);

    return 1;
}



