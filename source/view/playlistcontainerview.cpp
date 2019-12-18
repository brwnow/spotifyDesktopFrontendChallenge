#include "playlistcontainerview.hpp"

#include "playlistview.hpp"

#include <QVBoxLayout>

PlaylistContainerView::PlaylistContainerView(QWidget *parent) :
    QWidget(parent)
{
    setupWidgets();
    setupLayout();
}

PlaylistContainerView::~PlaylistContainerView()
{

}

void PlaylistContainerView::createPlaylist(const QString &title)
{
    PlaylistView *playlistView = new PlaylistView(title);
    QListWidgetItem *playlistItem = new QListWidgetItem();

    listOfPlaylists->addItem(playlistItem);
    listOfPlaylists->setItemWidget(playlistItem, playlistView);
}

void PlaylistContainerView::setupWidgets()
{
    titleLabel = new QLabel(QString("Playlists"));
    listOfPlaylists = new QListWidget();
}

void PlaylistContainerView::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(titleLabel, 0);
    layout->addWidget(listOfPlaylists, 1);

    this->setLayout(layout);
}
