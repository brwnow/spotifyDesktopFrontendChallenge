#include "playlistcontainerview.hpp"

#include <exception>

#include "playlistview.hpp"

#include <QVBoxLayout>

using std::exception;

PlaylistContainerView::PlaylistContainerView(QWidget *parent) :
    QWidget(parent)
{
    setupWidgets();
    setupLayout();
    setupConnections();
}

PlaylistContainerView::~PlaylistContainerView()
{

}

void PlaylistContainerView::createPlaylist(const QString &title, int playlistID)
{
    PlaylistView *playlistView = new PlaylistView(title, playlistID);
    QListWidgetItem *playlistItem = new QListWidgetItem();

    playlistItem->setSizeHint(playlistView->sizeHint());

    connect(playlistView, SIGNAL(deleteTriggered(int)), this, SIGNAL(playlistDeleted(int)));

    removePlaylist(playlistID);

    playlistIdMap[playlistID] = playlistItem;

    listOfPlaylists->addItem(playlistItem);
    listOfPlaylists->setItemWidget(playlistItem, playlistView);
}

void PlaylistContainerView::removePlaylist(int playlistID)
{
    map<int, QListWidgetItem*>::iterator it = playlistIdMap.find(playlistID);

    if(it != playlistIdMap.end())
    {
        int playlistRow = listOfPlaylists->row(it->second);

        // We need to manually delete the item since Qt doesn't handle it anymore when we take it
        delete listOfPlaylists->takeItem(playlistRow);
        playlistIdMap.erase(it);
    }
}

void PlaylistContainerView::setupWidgets()
{
    titleLabel = new QLabel(QString("Playlists"));
    listOfPlaylists = new QListWidget();
    listOfPlaylists->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    listOfPlaylists->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
}

void PlaylistContainerView::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(titleLabel, 0);
    layout->addWidget(listOfPlaylists, 1);

    this->setLayout(layout);
}

void PlaylistContainerView::setupConnections()
{
    connect(listOfPlaylists, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onPlaylistSelected(QListWidgetItem*)));
}

void PlaylistContainerView::onPlaylistSelected(QListWidgetItem *playlistItem)
{
    try
    {
        const PlaylistView *playlist = dynamic_cast<PlaylistView*>(listOfPlaylists->itemWidget(playlistItem));

        if(playlist != nullptr)
        {
            emit playlistClicked(playlist->getPlaylistID());
        }
    }
    catch(exception &ex)
    {

    }
}
