#include "songtable.hpp"

SongTable::SongTable(QSqlDatabase &database, QObject *parent) :
    QObject(parent),
    database(database)
{
}
