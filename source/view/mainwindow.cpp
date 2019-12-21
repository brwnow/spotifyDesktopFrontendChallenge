#include "mainwindow.hpp"

#include <QSplitter>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QApplication>
#include <QDesktopWidget>

const double MainWindow::windowPercentageOfDesktop = 0.6;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupWindow();
    setupWidgets();
    setupLayout();
    setupConnections();
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

void MainWindow::setupWindow()
{
    this->setWindowTitle("Spotify Desktop");
    this->setCentralWidget(new QWidget());

    setGeometry(QApplication::desktop()->size().width() * (1.0 - windowPercentageOfDesktop) / 2.0,
                QApplication::desktop()->size().height() * (1.0 - windowPercentageOfDesktop) / 2.0,
                QApplication::desktop()->size().width() * windowPercentageOfDesktop,
                QApplication::desktop()->size().height() * windowPercentageOfDesktop);
}

void MainWindow::setupWidgets()
{
    playlistContainer = new DeletableListView();
    songListView = new DeletableListView();
    playerView = new PlayerView();
    newPlaylistTextEdit = new QLineEdit();
    addPlaylistButton = new QPushButton("+");
}

void MainWindow::setupLayout()
{
    QGridLayout *playlistContainerLayout = new QGridLayout();
    playlistContainerLayout->addWidget(newPlaylistTextEdit, 0, 0);
    playlistContainerLayout->addWidget(addPlaylistButton, 0, 1);
    playlistContainerLayout->addWidget(playlistContainer, 1, 0, 1, 2);
    playlistContainerLayout->setRowStretch(0, 0);
    playlistContainerLayout->setRowStretch(1, 1);
    playlistContainerLayout->setColumnStretch(0, 1);
    playlistContainerLayout->setColumnStretch(1, 0);

    QGroupBox *playlistContainerWdgt = new QGroupBox();
    playlistContainerWdgt->setTitle("Playlists");
    playlistContainerWdgt->setLayout(playlistContainerLayout);

    QSplitter *splitter = new QSplitter();
    splitter->addWidget(songListView);
    splitter->addWidget(playlistContainerWdgt);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 0);
    splitter->setCollapsible(0, false);
    splitter->setCollapsible(1, false);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(splitter, 1);
    layout->addWidget(playerView, 0);

    this->centralWidget()->setLayout(layout);
}

void MainWindow::setupConnections()
{
    connect(addPlaylistButton, SIGNAL(clicked()),
            this, SLOT(onAddPlaylistTriggered()));
    connect(newPlaylistTextEdit, SIGNAL(returnPressed()),
            this, SLOT(onAddPlaylistTriggered()));
}

void MainWindow::onAddPlaylistTriggered()
{
    QString playlistTitle = newPlaylistTextEdit->text();

    if(!playlistTitle.isEmpty())
    {
        newPlaylistTextEdit->setText("");

        emit playlistAddRequested(playlistTitle);
    }
}

