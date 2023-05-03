#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , playerController(nullptr)
{
    ui->setupUi(this);
    
    this->setAcceptDrops(true);
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(StartButtonClick()));
    
    startPlay("rtsp://video:test_cam@192.168.50.95", ui->openGLWidget);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void MainWindow::startPlay(std::string url, void *view) {

    
    if(!view) {
        return;
    }
    
    if(url.empty()) {
        return;
    }
    
    if (isPlaying && playerController) {
        playerController->Stop();
        delete playerController;
        playerController = nullptr;
    }
    if (!playerController) {
        playerController = new PlayerController();
        playerController->SetDisplayView(ui->openGLWidget);
        playerController->Start(url);
        isPlaying = true;
        ui->startButton->setText("||");
    }
    
}

void MainWindow::dropEvent(QDropEvent *event) {
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty()) {
        return;
    }
    QString fileName = urls.first().toLocalFile();
    if(fileName.isEmpty()) {
        return;
    }
    //qDebug() << "laod file = " << fileName;
    startPlay(fileName.toStdString(), ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    if(playerController) {
        playerController->SetDisplayView(NULL);
        delete ui;
    }
}

void MainWindow::StartButtonClick() {
    if(playerController) {
        if(!isPlaying) {
            playerController->Play();
            ui->startButton->setText("||");
        } else {
            playerController->Pause();
            ui->startButton->setText(">");
        }
        
        isPlaying = !isPlaying;
    }
}

