#include "videofingerprint.h"
#include "ffmpegfileinfo.h"


VideoFingerPrint::VideoFingerPrint()
{

}
char* VideoFingerPrint::generateFingerPrint(char* file)
{
    FFMPEGFileInfo info;
    info.ReadFile(file);
    int64_t dur = info.GetDuration()/1000;
    std::string file_str(file);
    std::string fileSig = file_str + ".sig";
    vfpsearchind(file, fileSig.c_str(), 0, dur);

}
