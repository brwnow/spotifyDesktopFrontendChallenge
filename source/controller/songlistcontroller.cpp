#include "songlistcontroller.hpp"

#include <QDebug>

const int SongListController::INVALID_PLAYLIST_ID = -1;

SongListController::SongListController(QSqlDatabase &database, QObject *parent) :
    QObject(parent),
    songTable(database),
    openedPlaylistId(INVALID_PLAYLIST_ID)
{
    connect(&songTable, SIGNAL(songInserted(const QString&, int)),
            this, SIGNAL(songCreated(const QString&, int)));
    connect(&songTable, SIGNAL(songRemoved(int)),
            this, SIGNAL(songRemoved(int)));
}

void SongListController::createSong(const QString &title,
                                    const QString &spotifyId,
                                    const QString &spotifyUri)
{
    qDebug() << "<SongListController::createSong title =" << title <<
                " spotifyId =" << spotifyId << " spotifyUri =" << spotifyUri << ">";
    if(openedPlaylistId != INVALID_PLAYLIST_ID)
    {
        qDebug() << "Inserting song in playlist id" << openedPlaylistId;

        songTable.insert(title, openedPlaylistId, spotifyId, spotifyUri);
    }
    else
    {
        qWarning() << "Song insertion failed. There is no opened playlist";
    }

    qDebug() << "</SongListController::createSong>";
}

void SongListController::removeSong(int songID)
{
    songTable.remove(songID);
}

void SongListController::loadPlaylist(int playlistId)
{
    qDebug() << "<SongListController::loadPlaylist playlistId = " << playlistId << ">";

    if(playlistId != INVALID_PLAYLIST_ID)
    {
        list<SongTable::Tuple> playlist = songTable.getPlaylist(playlistId);

        qDebug() << "playlist loaded with " << playlist.size() << " elements";

        if(openedPlaylistId != INVALID_PLAYLIST_ID)
        {
            qDebug() << "Playlist with id " << openedPlaylistId << "was opened. Cleaning view";

            clearPlaylist();
        }

        openedPlaylistId = playlistId;

        for(list<SongTable::Tuple>::iterator it = playlist.begin(); it != playlist.end(); ++it)
        {
            emit songCreated(it->name, it->id);
        }
    }

    qDebug() << "</SongListController::loadPlaylist>";
}

void SongListController::clearPlaylist(int playlistId)
{
    if(playlistId == INVALID_PLAYLIST_ID || playlistId == openedPlaylistId)
    {
        openedPlaylistId = INVALID_PLAYLIST_ID;

        emit playlistCleared();
    }
}
