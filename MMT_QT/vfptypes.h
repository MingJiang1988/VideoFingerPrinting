#ifndef VFPTYPES_H
#define VFPTYPES_H

#include <inttypes.h>

typedef unsigned char BYTE;

typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;

typedef struct tagRGBTRIPLE {
  BYTE rgbtBlue;
  BYTE rgbtGreen;
  BYTE rgbtRed;
} RGBTRIPLE;


#endif // VFPTYPES_H
