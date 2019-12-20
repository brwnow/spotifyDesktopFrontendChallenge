#ifndef SONG_LIST_CONTROLLER_HPP
#define SONG_LIST_CONTROLLER_HPP

#include <QObject>

class SongListController : public QObject
{
    Q_OBJECT

public:
    SongListController(QObject *parent = nullptr);

signals:
    void songCreated(const QString &title, int songID);
    void songRemoved(int songID);
    void playlistCleared();

public slots:
    void createSong(const QString &title, int songID);
    void removeSong(int songID);
    void loadPlaylist(int playlistId);

    // Clear the loaded playlist. If playlistId is INVALID_PLAYLIST_ID then
    // clear the playlist no matter what id it has, otherwise clear the playlist
    // only if the given playlistId matches the loaded playlist id
    void clearPlaylist(int playlistId = INVALID_PLAYLIST_ID);

private:
    static const int INVALID_PLAYLIST_ID;

    int openedPlaylistId;
};

#endif // SONG_LIST_CONTROLLER_HPP
