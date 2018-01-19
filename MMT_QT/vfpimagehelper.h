#ifndef VFPIMAGEHELPER_H
#define VFPIMAGEHELPER_H

#include "vfptypes.h"

#include <QImage>

class VFPImageHelper
{
public:
    VFPImageHelper();

    void SaveImage24(BYTE* data, int width, int height, const char* filename);
    void SaveImage32(BYTE* data, int width, int height, const char* filename);
};

#endif // VFPIMAGEHELPER_H

