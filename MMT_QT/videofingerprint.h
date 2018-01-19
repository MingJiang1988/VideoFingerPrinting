#ifndef VIDEOFINGERPRINT_H
#define VIDEOFINGERPRINT_H

#include "vfpsearchind.h"
#include "vfpsearch.h"

class VideoFingerPrint
{
public:
    VideoFingerPrint();
    char* generateFingerPrint(char* videofilename);
};

#endif // VIDEOFINGERPRINT_H
