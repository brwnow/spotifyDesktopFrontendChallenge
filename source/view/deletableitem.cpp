#include "playlistview.hpp"

#include <QVBoxLayout>

PlaylistView::PlaylistView(const QString &title, int playlistID, QWidget *parent) :
    QWidget(parent),
    playlistID(playlistID)
{
    setupWidgets(title);
    setupLayout();
    setupConnections();
}

PlaylistView::~PlaylistView()
{

}

int PlaylistView::getPlaylistID() const
{
    return playlistID;
}

void PlaylistView::setupWidgets(const QString &title)
{
    playlistName = new QLabel(title);
    deleteButton = new QPushButton(QString("Del"));
}

void PlaylistView::setupLayout()
{
    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(playlistName, 1);
    layout->addWidget(deleteButton, 0);

    this->setLayout(layout);
}

void PlaylistView::setupConnections()
{
    connect(deleteButton, SIGNAL(clicked()), this, SIGNAL(deleteTriggered(playlistID)));
}
