#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vfpsearchind.h"
#include "vfpsearch.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btAddBroadcastFile_clicked();

    void on_btAddAdFile_clicked();

    void on_btStart_clicked();

    void on_edBroadcasts_blockCountChanged(int newBlockCount);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
