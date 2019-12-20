#include "mainwindow.hpp"

#include <QSplitter>
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

DeletableListView *MainWindow::getPlaylistContainer()
{
    return playlistContainer;
}

DeletableListView *MainWindow::getSongListView()
{
    return songListView;
}

PlayerView *MainWindow::getPlayerView()
{
    return playerView;
}

void MainWindow::setupWidgets()
{
    playlistContainer = new DeletableListView(QString("Playlists"));
    songListView = new DeletableListView(QString(""));
    playerView = new PlayerView();
}

void MainWindow::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout();
    QSplitter *splitter = new QSplitter();

    splitter->addWidget(songListView);
    splitter->addWidget(playlistContainer);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 0);
    splitter->setCollapsible(0, false);
    splitter->setCollapsible(1, false);

    layout->addWidget(splitter, 1);
    layout->addWidget(playerView, 0);

    this->centralWidget()->setLayout(layout);
}

void MainWindow::setupWindow()
{
    this->setWindowTitle(QString("Spotify Desktop"));
    this->setCentralWidget(new QWidget());
}

