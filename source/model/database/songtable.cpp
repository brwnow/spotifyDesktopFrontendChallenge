#include "songtable.hpp"

#include <QDebug>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

const QString SongTable::ID_FIELD("ID");
const QString SongTable::NAME_FIELD("NAME");

SongTable::SongTable(QSqlDatabase &database, QObject *parent) :
    QObject(parent),
    database(database)
{
}

list<SongTable::Tuple> SongTable::getPlaylist(int playlistID)
{
    QSqlQuery query(database);
    list<Tuple> playlist;

    qDebug() << "<SongTable::getPlaylist playlistID = " << playlistID << ">";

    query.prepare("SELECT ID, NAME FROM SONG WHERE PLAYLIST_ID = ?");
    query.bindValue(0, playlistID);

    if(!query.exec())
    {
        qDebug() << "Query error: " << query.lastError();
    }
    else
    {
        int idFieldNum = query.record().indexOf(ID_FIELD);
        int nameFieldNum = query.record().indexOf(NAME_FIELD);

        while(query.next())
        {
            int id = query.value(idFieldNum).toInt();
            QString name = query.value(nameFieldNum).toString();

            playlist.push_back(Tuple(id, name));
        }

        qDebug() << "Query returned " << playlist.size() << " records";
    }

    qDebug() << "</SongTable::getPlaylist>";

    return playlist;
}

void SongTable::insert(const QString &title, int playlistID)
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO SONG (NAME, PLAYLIST_ID) VALUES (?, ?)");
    query.bindValue(0, title);
    query.bindValue(1, playlistID);

    qDebug() << "<SongTable::insert title = " << title << " playlistID = " << playlistID << ">";
    qDebug() << "Running query " << query.lastQuery();

    if(query.exec())
    {
        qDebug() << "Query executed succesfully";

        emit songInserted(title, query.lastInsertId().toInt());
    }
    else
    {
        qDebug() << "Query error: " << query.lastError();

        emit insertionFailed(title);
    }

    qDebug() << "</SongTable::insert>";
}

void SongTable::remove(int id)
{
    QSqlQuery query(database);
    query.prepare("DELETE FROM SONG WHERE ID = ?");
    query.bindValue(0, id);

    if(query.exec())
        emit songRemoved(id);
}

SongTable::Tuple::Tuple(int id, const QString &name) :
    id(id),
    name(name)
{
}
