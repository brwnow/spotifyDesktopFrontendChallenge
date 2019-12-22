#include "playlisttable.hpp"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

const QString PlaylistTable::TABLE_NAME("PLAYLIST");
const QString PlaylistTable::ID_FIELD("ID");
const QString PlaylistTable::NAME_FIELD("NAME");

PlaylistTable::PlaylistTable(QSqlDatabase &database) :
    database(database)
{
}

QString PlaylistTable::getPlaylistTitle(int id)
{
    QSqlQuery query(database);
    QString name;

    qDebug() << "<PlaylistTable::selectPlaylist id =" << id << ">";

    query.prepare(QString("SELECT ") + NAME_FIELD +
                  " FROM "+ TABLE_NAME + " WHERE " + ID_FIELD + " = ?");
    query.bindValue(0, id);

    if(!query.exec())
    {
        qCritical() << "Query error:" << query.lastError();
    }
    else
    {
        int nameFieldNum = query.record().indexOf(NAME_FIELD);

        qDebug() << "Query:" << query.lastQuery();

        if(query.next())
        {
            name = query.value(nameFieldNum).toString();
            qDebug() << "Query got playlist name:" << name;
        }
        else
        {
            name = "";
            qCritical() << "Playlist not found in database";
        }
    }

    qDebug() << "</PlaylistTable::selectPlaylist return =" << name << ">";

    return name;
}

list<PlaylistTable::Tuple> PlaylistTable::getAllPlaylists()
{
    QSqlQuery query(QString("SELECT ") + ID_FIELD + ", " + NAME_FIELD +
                    " FROM "+ TABLE_NAME, database);
    int idFieldNum = query.record().indexOf(ID_FIELD);
    int nameFieldNum = query.record().indexOf(NAME_FIELD);
    list<Tuple> listOfPlaylists;

    qDebug() << "<PlaylistTable::getAllPlaylists>";
    qDebug() << "Query:" << query.lastQuery();

    while(query.next())
    {
        int id = query.value(idFieldNum).toInt();
        QString name = query.value(nameFieldNum).toString();

        listOfPlaylists.push_back(Tuple(id, name));
    }

    qDebug() << "Query exec result:" << query.lastError();
    qDebug() << "</PlaylistTable::getAllPlaylists>";

    return listOfPlaylists;
}

void PlaylistTable::insert(const QString &title)
{
    QSqlQuery query(database);
    query.prepare(QString("INSERT INTO ") + TABLE_NAME + "(" + NAME_FIELD + ")" + " VALUES (?)");
    query.bindValue(0, title);

    qDebug() << "<PlaylistTable::insert title =" << title << ">";

    if(query.exec())
        emit playlistInserted(title, query.lastInsertId().toInt());
    else
        emit insertionFailed(title);

    qDebug() << "Query:" << query.lastQuery();
    qDebug() << "Query exec result:" << query.lastError();
    qDebug() << "</PlaylistTable::insert>";
}

void PlaylistTable::remove(int id)
{
    QSqlQuery query(database);
    query.prepare(QString("DELETE FROM ") + TABLE_NAME + " WHERE " + ID_FIELD + " = ?");
    query.bindValue(0, id);

    qDebug() << "<PlaylistTable::remove id =" << id << ">";
    qDebug() << "Query:" << query.lastQuery();

    if(query.exec())
        emit playlistRemoved(id);

    qDebug() << "Query exec result:" << query.lastError();
    qDebug() << "</PlaylistTable::remove>";
}

PlaylistTable::Tuple::Tuple(int id, const QString name) :
    id(id),
    name(name)
{
}
