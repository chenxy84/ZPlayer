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
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
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
    qDebug() << "laod file = " << fileName;
    if (isPlaying) {
        playerController->Stop();
        delete playerController;
        playerController = nullptr;
    }
    if (!playerController) {
        playerController = new PlayerController();
        playerController->SetDisplayView(ui->openGLWidget);
        playerController->Start(fileName.toStdString());
        isPlaying = true;
        ui->startButton->setText("||");
    }
}

MainWindow::~MainWindow()
{
    playerController->SetDisplayView(NULL);
    delete ui;
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

