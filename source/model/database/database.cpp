#include "database.hpp"

#include <QDebug>
#include <QFileInfo>
#include <QSqlError>
#include <QSqlQuery>

const QString Database::databaseDriver("QSQLITE");
const QString Database::databaseName("db.dat");

Database::~Database()
{
    database.close();
}

Database &Database::getInstance()
{
    static Database instance;

    return instance;
}

QSqlDatabase &Database::getDbObject()
{
    return database;
}

bool Database::open()
{
    bool mustCreateSchema = !QFileInfo::exists(databaseName);

    database = QSqlDatabase::addDatabase(databaseDriver);
    database.setDatabaseName(databaseName);

    if(database.open())
    {
        if(mustCreateSchema)
        {
            if(!createSchema())
            {
                emit errorMsgSent("Database query error",
                                  "Error while creating database tables");

                return false;
            }
        }

        return true;
    }
    else
    {
        qDebug() << "Database error: " << database.lastError();

        emit errorMsgSent("Cannot open database",
                          "Unable to establish a database connection");

        return false;
    }
}

void Database::close()
{
    database.close();
}

Database::Database()
{
}

bool Database::createSchema()
{
    QSqlQuery query(database);
    bool success = true;

    qDebug() << "<Core::createDatabaseSchema>";

    if(!query.exec("CREATE TABLE PLAYLIST("
                    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "NAME VARCHAR(100) UNIQUE)"))
    {
        qDebug() << query.lastError();
        success = false;
    }

    if(!query.exec("CREATE TABLE SONG("
                    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "NAME VARCHAR(100),"
                    "PLAYLIST_ID INTEGER,"
                    "SPOTIFY_ID VARCHAR(100),"
                    "SPOTIFY_URI VARCHAR(100),"
                    "FOREIGN KEY(PLAYLIST_ID) REFERENCES PLAYLIST(ID))"))
    {
        qDebug() << query.lastError();
        success = false;
    }

    qDebug() << "</Core::dataBaseSchema>";

    return success;
}
