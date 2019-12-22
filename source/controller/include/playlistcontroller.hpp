#ifndef PLAYLIST_CONTROLLER_HPP
#define PLAYLIST_CONTROLLER_HPP

#include "playlisttable.hpp"

#include <QObject>

class PlaylistController : public QObject
{
    Q_OBJECT

public:
    PlaylistController(QSqlDatabase &database, QObject *parent = nullptr);

signals:
    void playlistSelected(const QString &title);
    void playlistCreated(const QString &title, int id);
    void playlistRemoved(int id);

public slots:
    void selectPlaylist(int id);
    void createPlaylist(const QString &title);
    void removePlaylist(int id);
    void loadView();

private:
    PlaylistTable playlistTable;

};

#endif // PLAYLIST_CONTROLLER_HPP
