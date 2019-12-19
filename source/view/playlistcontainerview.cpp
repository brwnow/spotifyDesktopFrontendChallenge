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

    listOfPlaylists->addItem(playlistItem);
    listOfPlaylists->setItemWidget(playlistItem, playlistView);
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
    connect(listOfPlaylists, SIGNAL(itemActivated), this, SLOT(onPlaylistSelected()));
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
