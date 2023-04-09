#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , playerController(new PlayerController)
{
    ui->setupUi(this);

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(StartButtonClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartButtonClick() {
    playerController->Start("test.mp4");

}
