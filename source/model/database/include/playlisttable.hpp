#ifndef PLAYLIST_TABLE_HPP
#define PLAYLIST_TABLE_HPP

#include <list>

#include <QObject>
#include <QSqlDatabase>

using std::list;

class PlaylistTable : public QObject
{
    Q_OBJECT

public:
    static const QString ID_FIELD;
    static const QString NAME_FIELD;

    class Tuple
    {
    public:
        const int id;
        const QString name;

        Tuple(int id, const QString name);
    };

    PlaylistTable(QSqlDatabase &database);

    list<Tuple> getAllPlaylists();
    void insert(const QString &title);
    void remove(int id);

signals:
    void playlistInserted(const QString &title, int id);
    void insertionFailed(const QString &title);
    void playlistRemoved(int id);

private:
    QSqlDatabase &database;

};

#endif // PLAYLIST_TABLE_HPP
