#include "songlistview.hpp"

#include <exception>

#include "songview.hpp"

#include <QVBoxLayout>

using std::exception;

SongListView::SongListView(QWidget *parent) :
    QWidget(parent)
{
    setupWidgets();
    setupLayout();
    setupConnections();
}

SongListView::~SongListView()
{

}

void SongListView::createSong(const QString &songName, int songID)
{
    Q_UNUSED(songName);
    Q_UNUSED(songID);
}

void SongListView::removeSong(int songID)
{
    Q_UNUSED(songID);
}

void SongListView::setupWidgets()
{
    playlistName = new QLabel();
    listOfSongs = new QListWidget();
}

void SongListView::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(playlistName, 0);
    layout->addWidget(listOfSongs, 1);

    this->setLayout(layout);
}

void SongListView::setupConnections()
{
    connect(listOfSongs, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onSongSelected(QListWidgetItem*)));
}

void SongListView::onSongSelected(QListWidgetItem *songItem)
{
    Q_UNUSED(songItem);

    try
    {

    }
    catch(exception &ex)
    {

    }
}
