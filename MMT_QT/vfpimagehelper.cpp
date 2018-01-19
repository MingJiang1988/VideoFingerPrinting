#include "vfpimagehelper.h"

VFPImageHelper::VFPImageHelper()
{
}

void VFPImageHelper::SaveImage24(BYTE* data, int width, int height, const char* filename)
{
    QImage image(data, width, height, QImage::Format_RGB888);
    const QString filenameQ(filename);
    image.save(filenameQ);
}

void VFPImageHelper::SaveImage32(BYTE* data, int width, int height, const char* filename)
{
    QImage image(data, width, height, QImage::Format_RGB32);
    const QString filenameQ(filename);
    image.save(filenameQ);
}

//void RGB32_To_RGB24(
//        BYTE*       pDest,
//        int        lDestStride,
//        const BYTE* pSrc,
//        int        lSrcStride,
//        uint       dwWidthInPixels,
//        uint       dwHeightInPixels
//        )
//{
//    for (uint y = 0; y < dwHeightInPixels; y++)
//    {
//        RGBQUAD     *pSrcPixel = (RGBQUAD*)pSrc;
//        RGBTRIPLE   *pDestPixel = (RGBTRIPLE*)pDest;

//        for (uint x = 0; x < dwWidthInPixels; x++)
//        {
//            pDestPixel[x].rgbtRed = pSrcPixel[x].rgbRed;
//            pDestPixel[x].rgbtGreen = pSrcPixel[x].rgbGreen;
//            pDestPixel[x].rgbtBlue = pSrcPixel[x].rgbBlue;
//        }

//        pDest += lDestStride;
//        pSrc += lSrcStride;
//    }
//}
