#ifndef SONG_TABLE_HPP
#define SONG_TABLE_HPP

#include <QObject>
#include <QSqlDatabase>

class SongTable : public QObject
{
public:
    SongTable(QSqlDatabase &database, QObject *parent = nullptr);

private:
    QSqlDatabase &database;

};

#endif // SONG_TABLE_HPP
