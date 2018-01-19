#include "mainwindow.h"
#include "ffmpegfileinfo.h"
#include "iostream"

void generate_sig(char* filename)
{
    QString fileSig = QString(filename) + ".sig";
    FFMPEGFileInfo info;
    info.ReadFile(filename);
    // getFileDurationMSec(file.toStdString().c_str()) / 1000;
    int64_t dur = info.GetDuration() / 1000;
    vfpsearchind(filename, fileSig.toStdString().c_str(), 0, dur);
}

void generate_sig_img(char* imagefile)
{
    int64_t dur = 0;
    QString fileSig = QString(imagefile) + ".sig";
    ifpsearchind(imagefile, fileSig.toStdString().c_str(), 0, dur);
}

int main(int argc, char *argv[])
{

    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //QStringList args = app.arguments();
    if(argc==1)
    {
        exit(0);
    }
    char* filename1 = argv[1];
    char* filename2 = argv[2];
    generate_sig(filename1);
    generate_sig(filename2);
    int timeSeconds = 0;
    QString src_fileSig = QString(filename1) + ".sig";
    QString dst_fileSig = QString(filename2) + ".sig";
    int hr = vfpsearch(src_fileSig.toStdString().c_str(), dst_fileSig.toStdString().c_str(), &timeSeconds);

    if(hr == 0)
    {
        std::cout << "Detected" << std::endl;
    }

    //generate_sig_img(filename1);


    return 0;
}
