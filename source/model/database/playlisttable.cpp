#include "playlisttable.hpp"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

const QString PlaylistTable::ID_FIELD("ID");
const QString PlaylistTable::NAME_FIELD("NAME");

PlaylistTable::PlaylistTable(QSqlDatabase &database) :
    database(database)
{
}

list<PlaylistTable::Tuple> PlaylistTable::getAllPlaylists()
{
    QSqlQuery query("SELECT ID, NAME FROM PLAYLIST", database);
    int idFieldNum = query.record().indexOf(ID_FIELD);
    int nameFieldNum = query.record().indexOf(NAME_FIELD);
    list<Tuple> listOfPlaylists;

    while(query.next())
    {
        int id = query.value(idFieldNum).toInt();
        QString name = query.value(nameFieldNum).toString();

        listOfPlaylists.push_back(Tuple(id, name));
    }

    return listOfPlaylists;
}

void PlaylistTable::insert(const QString &title)
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO PLAYLIST (NAME) VALUES (?)");
    query.bindValue(0, title);

    if(query.exec())
        emit playlistInserted(query.lastInsertId().toInt());
    else
        emit insertionFailed(title);
}

void PlaylistTable::remove(int id)
{
    QSqlQuery query(database);
    query.prepare("DELETE FROM PLAYLIST WHERE ID = ?");
    query.bindValue(0, id);

    if(query.exec())
        emit playlistRemoved(id);
}

PlaylistTable::Tuple::Tuple(int id, const QString name) :
    id(id),
    name(name)
{
}
