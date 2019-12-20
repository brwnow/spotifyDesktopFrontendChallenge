#include "playlistcontroller.hpp"

Controller::Controller(PlaylistTable &playlistTable, QObject *parent) :
    QObject(parent),
    playlistTable(playlistTable)
{
    connect(&playlistTable, SIGNAL(playlistInserted(const QString&, int)),
            this, SIGNAL(playlistCreated(const QString&, int)));
}

void Controller::createPlaylist(const QString &title)
{
    playlistTable.insert(title);
}

void Controller::removePlaylist(int id)
{
    playlistTable.remove(id);
}

void Controller::loadView()
{
    list<PlaylistTable::Tuple> playlists = playlistTable.getAllPlaylists();

    for(list<PlaylistTable::Tuple>::iterator it = playlists.begin(); it != playlists.end(); ++it)
    {
        emit playlistCreated(it->name, it->id);
    }
}
