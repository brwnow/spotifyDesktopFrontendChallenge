#ifndef CORE_HPP
#define CORE_HPP

#include "mainwindow.hpp"
#include "playlistcontroller.hpp"
#include "songlistcontroller.hpp"
#include "spotifywebapicontroller.hpp"

#include "database.hpp"

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
    void mustStartNetwork();

public slots:
    void setErrorDialog(const QString &title, const QString &msg);

private:
    static const QString databaseDriver;
    static const QString databaseName;
    static QString errorMsgTitle, errorMsg;

    QApplication &app;
    Database &database;

    MainWindow &mainWindow;

    PlaylistController *playlistController;
    SongListController *songListController;
    SpotifyWebApiController *spotifWebApiController;

    Core(QApplication &app);

    int exec();

    void initControllers();
    void bindMVC();
    void sendLoadAppSignal();

};

#endif // CORE_HPP
