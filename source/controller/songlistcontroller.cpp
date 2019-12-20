#include "songlistcontroller.hpp"

const int SongListController::INVALID_PLAYLIST_ID = -1;

SongListController::SongListController(QObject *parent) :
    QObject(parent),
    openedPlaylistId(INVALID_PLAYLIST_ID)
{
}

void SongListController::createSong(const QString &title, int songID)
{
    Q_UNUSED(title);
    Q_UNUSED(songID);
}

void SongListController::removeSong(int songID)
{
    Q_UNUSED(songID);
}

void SongListController::loadPlaylist(int playlistId)
{
    Q_UNUSED(playlistId);
}

void SongListController::clearPlaylist(int playlistId)
{
    Q_UNUSED(playlistId);
}
