#include "songtable.hpp"

#include <QDebug>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

const QString SongTable::TABLE_NAME("SONG");
const QString SongTable::ID_FIELD("ID");
const QString SongTable::NAME_FIELD("NAME");
const QString SongTable::PLAYLIST_ID("PLAYLIST_ID");
const QString SongTable::SPOTIFY_ID("SPOTIFY_ID");
const QString SongTable::SPOTIFY_URI("SPOTIFY_URI");

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

    query.prepare(QString("SELECT ") + ID_FIELD + ", " + NAME_FIELD + " FROM " +
                  TABLE_NAME + " WHERE " + PLAYLIST_ID + " = ?");
    query.bindValue(0, playlistID);

    if(!query.exec())
    {
        qCritical() << "Query error: " << query.lastError();
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

void SongTable::insert(const QString &title,
                       int playlistID,
                       const QString &spotifyId,
                       const QString &spotifyUri)
{
    QSqlQuery query(database);
    query.prepare(QString("INSERT INTO ") + TABLE_NAME +
                  " (" + NAME_FIELD + ", " + PLAYLIST_ID + ", " +
                  SPOTIFY_ID + ", " + SPOTIFY_URI + ") " +
                  "VALUES (?, ?, ?, ?)");
    query.bindValue(0, title);
    query.bindValue(1, playlistID);
    query.bindValue(2, spotifyId);
    query.bindValue(3, spotifyUri);

    qDebug() << "<SongTable::insert title =" << title << " playlistID =" << playlistID <<
                "spotifyId =" << spotifyId << " spotifyUri =" << spotifyUri << ">";
    qDebug() << "Running query " << query.lastQuery();

    if(query.exec())
    {
        qDebug() << "Query executed succesfully";

        emit songInserted(title, query.lastInsertId().toInt());
    }
    else
    {
        qCritical() << "Query error: " << query.lastError();

        emit insertionFailed(title);
    }

    qDebug() << "</SongTable::insert>";
}

void SongTable::remove(int id)
{
    QSqlQuery query(database);
    query.prepare(QString("DELETE FROM ") + TABLE_NAME + " WHERE " + ID_FIELD + " = ?");
    query.bindValue(0, id);

    if(query.exec())
        emit songRemoved(id);
}

SongTable::Tuple::Tuple(int id, const QString &name) :
    id(id),
    name(name)
{
}
