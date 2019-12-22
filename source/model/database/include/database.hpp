#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QString>

class Database : public QObject
{
    Q_OBJECT

public:
    ~Database();

    static Database& getInstance();

    Database(Database const &) = delete;
    void operator = (Database const &) = delete;

    QSqlDatabase& getDbObject();

    bool open();
    void close();

signals:
    void errorMsgSent(const QString&, const QString&);

private:
    static const QString databaseDriver;
    static const QString databaseName;

    QSqlDatabase database;

    Database();

    bool createSchema();
};

#endif // DATABASE_HPP
