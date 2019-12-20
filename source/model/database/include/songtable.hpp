#ifndef SONG_TABLE_HPP
#define SONG_TABLE_HPP

#include <list>

#include <QObject>
#include <QSqlDatabase>

using std::list;

class SongTable : public QObject
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

        Tuple(int id, const QString &name);
    };

    SongTable(QSqlDatabase &database, QObject *parent = nullptr);

    list<Tuple> getPlaylist(int playlistID);
    void insert(const QString &title);
    void remove(int id);

signals:
    void songInserted(const QString &title, int id);
    void insertionFailed(const QString &title);
    void songRemoved(int id);

private:
    QSqlDatabase &database;

};

#endif // SONG_TABLE_HPP
