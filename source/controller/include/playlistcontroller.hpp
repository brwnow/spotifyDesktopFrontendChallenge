#ifndef PLAYLIST_CONTROLLER_HPP
#define PLAYLIST_CONTROLLER_HPP

#include "playlisttable.hpp"

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(PlaylistTable &playlistTable, QObject *parent = nullptr);

signals:
    void playlistCreated(const QString &title, int id);
    void playlistRemoved(int id);

public slots:
    void createPlaylist(const QString &title);
    void removePlaylist(int id);
    void loadView();

private:
    PlaylistTable &playlistTable;

};

#endif // PLAYLIST_CONTROLLER_HPP
