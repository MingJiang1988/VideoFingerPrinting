#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

#include "ffmpegfileinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QString adFile = "c:\\Projects\\_Projects\\VideoFingerPrinting\\_SOURCES\\VFP CPP Version\\SOURCES\\data\\ad2.wmv";
//    adFile.append("\nc:\\Projects\\_Projects\\VideoFingerPrinting\\_SOURCES\\VFP CPP Version\\SOURCES\\data\\ad1.wmv");
//    QString broadcastFile = "c:\\Projects\\_Projects\\VideoFingerPrinting\\_SOURCES\\VFP CPP Version\\SOURCES\\data\\2012.09.01.15.35.wmv";
//    broadcastFile.append("\nc:\\Projects\\_Projects\\VideoFingerPrinting\\_SOURCES\\VFP CPP Version\\SOURCES\\data\\2012.09.01.16.05.wmv");

    //ui->edAdSamples->setPlainText(adFile);
    //ui->edBroadcasts->setPlainText(broadcastFile);
}

bool fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btAddBroadcastFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open broadcast video file"), "", tr("Video files (*.*)"));

    ui->edBroadcasts->setPlainText(ui->edBroadcasts->toPlainText() + fileName + "\n");
}

void MainWindow::on_btAddAdFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open ad video file"), "", tr("Video files (*.*)"));

    ui->edAdSamples->setPlainText(ui->edAdSamples->toPlainText() + fileName + "\n");
}

void MainWindow::on_btStart_clicked()
{
    QString adFilesStr = ui->edAdSamples->toPlainText();
    QString broadcastFilesStr = ui->edBroadcasts->toPlainText();

    QStringList adFiles = adFilesStr.split("\n");
    QStringList broadcastFiles = broadcastFilesStr.split("\n");

    QList<int64_t> adFilesDuration;

    FFMPEGFileInfo info;

    for (int i = 0; i < adFiles.length(); i++)
    {
        QString file = adFiles[i];

        if (!fileExists(file))
        {
            continue;
        }

        QString fileSig = file + ".sig";

        info.ReadFile(file.toStdString().c_str());

        // getFileDurationMSec(file.toStdString().c_str()) / 1000;
        int64_t dur = info.GetDuration() / 1000;
        vfpsearchind(file.toStdString().c_str(), fileSig.toStdString().c_str(), 0, dur);
    }

    for (int i = 0; i < broadcastFiles.length(); i++)
    {
        QString file = broadcastFiles[i];

        if (!fileExists(file))
        {
            continue;
        }

        QString fileSig = file + ".sig";

        info.ReadFile(file.toStdString().c_str());

        int64_t dur = info.GetDuration() / 1000;
        vfpsearchind(file.toStdString().c_str(), fileSig.toStdString().c_str(), 0, dur);
    }

    for (int i = 0; i < adFiles.length(); i++)
    {
        if (!fileExists(adFiles[i]))
        {
            continue;
        }

        for (int j = 0; j < broadcastFiles.length(); j++)
        {
            if (!fileExists(broadcastFiles[j]))
            {
                continue;
            }

            int timeSeconds = 0;

            QString fileSrc = adFiles[i];
            QString fileSrcSig = fileSrc + ".sig";

            QString fileDst = broadcastFiles[j];
            QString fileDstSig = fileDst + ".sig";

            int hr = vfpsearch(fileSrcSig.toStdString().c_str(), fileDstSig.toStdString().c_str(), &timeSeconds);
            if (hr == 0)
            {
                QString hours = QString::number( timeSeconds / (60 * 60) );
                if (hours.length() == 1)
                {
                    hours.insert(0, '0');
                }

                QString minutes = QString::number( timeSeconds / 60 );
                if (minutes.length() == 1)
                {
                    minutes.insert(0, '0');
                }

                QString seconds = QString::number( timeSeconds % 60 );
                if (seconds.length() == 1)
                {
                    seconds.insert(0, '0');
                }

                QString results = ui->edResults->toPlainText();
                results += "Found! Ad file: \"" + fileSrc + "\", broadcast file: \"" + fileDst + "\", position: " + hours + ":" + minutes + ":" + seconds + "\n";
                ui->edResults->setPlainText(results);
            }
        }
    }
}

void MainWindow::on_edBroadcasts_blockCountChanged(int newBlockCount)
{

}
