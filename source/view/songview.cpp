#include "songview.hpp"

#include <QVBoxLayout>

SongView::SongView(const QString &title, int songID, QWidget *parent) :
    QWidget(parent),
    songID(songID)
{
    setupWidgets(title);
    setupLayout();
    setupConnections();
}

SongView::~SongView()
{

}

int SongView::getSongID() const
{
    return songID;
}

void SongView::setupWidgets(const QString &title)
{
    songTitle = new QLabel(title);
    deleteButton = new QPushButton(QString("Del"));
}

void SongView::setupLayout()
{
    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(songTitle, 1);
    layout->addWidget(deleteButton, 0);

    this->setLayout(layout);
}

void SongView::setupConnections()
{
    connect(deleteButton, SIGNAL(clicked()), this, SIGNAL(deleteTriggered(songID)));
}
