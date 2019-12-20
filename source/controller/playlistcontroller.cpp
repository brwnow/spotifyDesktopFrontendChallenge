#include "playlistcontroller.hpp"

PlaylistController::PlaylistController(PlaylistTable &playlistTable, QObject *parent) :
    QObject(parent),
    playlistTable(playlistTable)
{
    connect(&playlistTable, SIGNAL(playlistInserted(const QString&, int)),
            this, SIGNAL(playlistCreated(const QString&, int)));
}

void PlaylistController::createPlaylist(const QString &title)
{
    playlistTable.insert(title);
}

void PlaylistController::removePlaylist(int id)
{
    playlistTable.remove(id);
}

void PlaylistController::loadView()
{
    list<PlaylistTable::Tuple> playlists = playlistTable.getAllPlaylists();

    for(list<PlaylistTable::Tuple>::iterator it = playlists.begin(); it != playlists.end(); ++it)
    {
        emit playlistCreated(it->name, it->id);
    }
}
