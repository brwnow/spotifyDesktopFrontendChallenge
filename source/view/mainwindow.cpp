#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupWidgets();
    setupLayout();
    setupWindow();
}

MainWindow::~MainWindow()
{
}

MainWindow &MainWindow::getInstance()
{
    static MainWindow instance;

    return instance;
}

void MainWindow::setupWidgets()
{
    playlistContainer = new PlaylistContainerView();
}

void MainWindow::setupLayout()
{

}

void MainWindow::setupWindow()
{
    this->setWindowTitle(QString("Spotify Desktop"));

    this->setCentralWidget(playlistContainer);
}

