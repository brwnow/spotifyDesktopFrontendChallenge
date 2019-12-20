#ifndef CORE_HPP
#define CORE_HPP

#include "mainwindow.hpp"
#include "playlistcontroller.hpp"
#include "songlistcontroller.hpp"

#include <QApplication>
#include <QMutex>
#include <QObject>
#include <QSqlDatabase>

class Core : public QObject
{
    Q_OBJECT

public:
    static const int CORE_ALREADY_RUNNING = -1;
    static QMutex runMutex;

    ~Core();

    static int run(QApplication &app);

    Core(Core const &) = delete;
    void operator = (Core const &) = delete;

signals:
    void mustLoadAppData();

private:
    static const QString databaseDriver;
    static const QString databaseName;
    static QString errorMsgTitle, errorMsg;

    QApplication &app;
    QSqlDatabase database;

    MainWindow &mainWindow;

    PlaylistController *playlistController;
    SongListController *songListController;

    Core(QApplication &app);

    static void setErrorDialog(const QString &title, const QString &msg);

    int exec();

    bool connectToDatabase();
    bool createDatabaseSchema();
    void initControllers();
    void bindMVC();
    void sendLoadAppSignal();

};

#endif // CORE_HPP
