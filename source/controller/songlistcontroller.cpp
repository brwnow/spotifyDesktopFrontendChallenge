#include "songlistcontroller.hpp"

const int SongListController::INVALID_PLAYLIST_ID = -1;

SongListController::SongListController(QSqlDatabase &database, QObject *parent) :
    QObject(parent),
    songTable(database),
    openedPlaylistId(INVALID_PLAYLIST_ID)
{
    connect(&songTable, SIGNAL(songInserted(const QString&, int)),
            this, SIGNAL(songCreated(const QString&, int)));
    connect(&songTable, SIGNAL(songRemoved(int)),
            this, SLOT(songRemoved(int)));
}

void SongListController::createSong(const QString &title)
{
    songTable.insert(title);
}

void SongListController::removeSong(int songID)
{
    songTable.remove(songID);
}

void SongListController::loadPlaylist(int playlistId)
{
    if(playlistId != INVALID_PLAYLIST_ID)
    {
        list<SongTable::Tuple> playlist = songTable.getPlaylist(playlistId);

        if(openedPlaylistId != INVALID_PLAYLIST_ID)
            clearPlaylist();

        openedPlaylistId = playlistId;

        for(list<SongTable::Tuple>::iterator it = playlist.begin(); it != playlist.end(); ++it)
        {
            emit songCreated(it->name, it->id);
        }
    }
}

void SongListController::clearPlaylist(int playlistId)
{
    if(playlistId == INVALID_PLAYLIST_ID || playlistId == openedPlaylistId)
    {
        openedPlaylistId = INVALID_PLAYLIST_ID;

        emit playlistCleared();
    }
}
