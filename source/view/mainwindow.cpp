#include "mainwindow.hpp"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupWindow();
    setupWidgets();
    setupLayout();
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
    playerView = new PlayerView();
}

void MainWindow::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(playlistContainer, 1);
    layout->addWidget(playerView, 0);

    this->centralWidget()->setLayout(layout);
}

void MainWindow::setupWindow()
{
    this->setWindowTitle(QString("Spotify Desktop"));
    this->setCentralWidget(new QWidget());
}

