#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player_controller.h"
#include "video_gl_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void StartButtonClick();

private:
    Ui::MainWindow *ui;
    PlayerController *playerController;
    
    bool isPrepared = false;
    bool isPlaying = false;
};
#endif // MAINWINDOW_H
