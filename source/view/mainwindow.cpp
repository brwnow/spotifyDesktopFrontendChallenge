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

void MainWindow::setCurrentPlaylistTitle(const QString &title)
{
    playlistTitle->setText(title);
}

void MainWindow::setNoCurrentPlaylist()
{
    playlistTitle->setText("");
}

void MainWindow::appendSongSearchResult(const QString &songName)
{
    searchResultList->addItem(new QListWidgetItem(songName));
}

void MainWindow::clearSongSearchResults()
{
    searchResultList->clear();
}

void MainWindow::setupWindow()
{
    this->setWindowTitle("Spotify Desktop");
    this->setCentralWidget(new QWidget());
    this->setWindowIcon(QIcon(":/icons/spotify.png"));

    setGeometry(QApplication::desktop()->size().width() * (1.0 - windowPercentageOfDesktop) / 2.0,
                QApplication::desktop()->size().height() * (1.0 - windowPercentageOfDesktop) / 2.0,
                QApplication::desktop()->size().width() * windowPercentageOfDesktop,
                QApplication::desktop()->size().height() * windowPercentageOfDesktop);
}

void MainWindow::setupWidgets()
{
    playlistContainer = new DeletableListView();
    playlistContainer->setItemTitlePointSize(18);
    songListView = new DeletableListView();
    songListView->setItemTitlePointSize(12);
    playerView = new PlayerView();
    newPlaylistTextEdit = new QLineEdit();
    addPlaylistButton = new QPushButton();
    addPlaylistButton->setIcon(QIcon(":/icons/add.png"));
    addPlaylistButton->setFlat(true);
    addPlaylistButton->setToolTip("Add a playlist");

    playlistTitle = new QLabel();
    songSearchTextEdit = new QLineEdit();
    searchButton = new QPushButton(QIcon(":/icons/search.png"), "SEARCH");
    searchButton->setToolTip("Search for songs");
    searchResultList = new QListWidget();

    QFont playlistTitleFont = QGuiApplication::font();
    playlistTitleFont.setPointSize(25);
    playlistTitle->setFont(playlistTitleFont);
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

    QGridLayout *songListLayout = new QGridLayout();
    songListLayout->addWidget(playlistTitle, 0, 0, 1, 2, Qt::AlignCenter);
    songListLayout->addWidget(songSearchTextEdit, 1, 0);
    songListLayout->addWidget(searchButton, 1, 1);
    songListLayout->addWidget(searchResultList, 2, 0, 1, 2);
    songListLayout->addWidget(songListView, 3, 0, 1, 2);
    songListLayout->setRowStretch(0, 0);
    songListLayout->setRowStretch(1, 0);
    songListLayout->setRowStretch(2, 0);
    songListLayout->setRowStretch(3, 1);
    songListLayout->setColumnStretch(0, 1);
    songListLayout->setColumnStretch(1, 0);

    QGroupBox *songListWidget = new QGroupBox();
    songListWidget->setTitle("Songs");
    songListWidget->setLayout(songListLayout);

    QSplitter *splitter = new QSplitter();
    splitter->addWidget(songListWidget);
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
    connect(searchButton, SIGNAL(clicked()), this, SLOT(onSongSearchClicked()));
    connect(songSearchTextEdit, SIGNAL(returnPressed()), this, SLOT(onSongSearchClicked()));
    connect(searchResultList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onSearchResultItemClicked(QListWidgetItem*)));
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

void MainWindow::onSongSearchClicked()
{
    QString searchQuery = songSearchTextEdit->text();

    if(!searchQuery.isEmpty())
    {
        songSearchTextEdit->clear();

        emit songSearchRequested(searchQuery);
    }
}

void MainWindow::onSearchResultItemClicked(QListWidgetItem *item)
{
    emit saveSongFromSearch(searchResultList->row(item));
}

