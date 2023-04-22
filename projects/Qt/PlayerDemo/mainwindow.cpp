#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , playerController(new PlayerController)
    
{
    ui->setupUi(this);

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(StartButtonClick()));
    
//    playerController->Start("/Users/chenxiangyu/Documents/Samples/test_avc_2160x3840_10M_23.98fps_faststart.mp4");
//    playerController->Start("/Users/chenxiangyu/Documents/4035d397-17db85911c1.mov");
    
    playerController->Start("/Users/chenxiangyu/Documents/Samples/test.webm");
    isPlaying = true;
    playerController->SetDisplayView(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    playerController->SetDisplayView(NULL);
    delete ui;
}

void MainWindow::StartButtonClick() {
    
    if(!isPlaying) {
        playerController->Play();
    } else {
        playerController->Pause();
    }
    
    isPlaying = !isPlaying;

}

