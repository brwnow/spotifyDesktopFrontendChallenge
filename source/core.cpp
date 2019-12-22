#include "core.hpp"

#include <QDebug>

#include <QFileInfo>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

QMutex Core::runMutex;

QString Core::errorMsgTitle;
QString Core::errorMsg;

int Core::run(QApplication &app)
{
    static bool isCoreRunning = false;

    runMutex.lock();

    if(!isCoreRunning)
    {
        isCoreRunning = true;
        runMutex.unlock();

        qDebug() << "Application is starting...";

        bool appInitializationFailed = false;
        Core core(app);

        if(!core.database.open())
            appInitializationFailed = true;

        core.initControllers();
        core.bindMVC();
        core.sendLoadAppSignal();

        if(!appInitializationFailed)
        {
            qDebug() << "Application started successfully";

            return core.exec();
        }
        else
        {
            qDebug() << "Application failed to start";

            QMessageBox::critical(nullptr, errorMsgTitle, errorMsg, QMessageBox::Ok);

            return 0;
        }
    }
    else
    {
        return CORE_ALREADY_RUNNING;
    }
}

void Core::setErrorDialog(const QString &title, const QString &msg)
{
    errorMsgTitle = title;
    errorMsg = msg;
}

Core::Core(QApplication &app) :
    app(app),
    database(Database::getInstance()),
    mainWindow(MainWindow::getInstance())
{
    connect(&database, SIGNAL(errorMsgSent(const QString&, const QString&)),
            this, SLOT(setErrorDialog(const QString&, const QString&)));
}

int Core::exec()
{
    mainWindow.show();

    return app.exec();
}

void Core::initControllers()
{
    qDebug() << "Initializing controllers...";

    playlistController = new PlaylistController(database.getDbObject(), this);
    songListController = new SongListController(database.getDbObject(), this);
    spotifWebApiController = new SpotifyWebApiController(this);
}

void Core::bindMVC()
{
    qDebug() << "Binding Core, Models, Views and Controllers...";

    // Core starting signals
    connect(this, SIGNAL(mustLoadAppData()), playlistController, SLOT(loadView()));
    connect(this, SIGNAL(mustStartNetwork()),
            spotifWebApiController, SLOT(obtainAccessToken()));

    // PlaylistController signals
    connect(playlistController, SIGNAL(playlistSelected(const QString&)),
            &mainWindow, SLOT(setCurrentPlaylistTitle(const QString&)));
    connect(playlistController, SIGNAL(playlistCreated(const QString&, int)),
            mainWindow.getPlaylistContainer(), SLOT(createItem(const QString&, int)));
    connect(playlistController, SIGNAL(playlistRemoved(int)),
            mainWindow.getPlaylistContainer(), SLOT(removeItem(int)));

    // SongListController must be notified when a playlist is deleted. If the opened playlist
    // is deleted, SongListController must clean the SongListView
    connect(playlistController, SIGNAL(playlistRemoved(int)),
            songListController, SLOT(clearPlaylist(int)));

    // Binding SongListController to MainWindow and vice versa
    connect(songListController, SIGNAL(songCreated(const QString&, int)),
            mainWindow.getSongListView(), SLOT(createItem(const QString&, int)));
    connect(songListController, SIGNAL(songRemoved(int)),
            mainWindow.getSongListView(), SLOT(removeItem(int)));
    connect(songListController, SIGNAL(playlistCleared()),
            mainWindow.getSongListView(), SLOT(clearItems()));
    connect(songListController, SIGNAL(playlistCleared()),
            &mainWindow, SLOT(setNoCurrentPlaylist()));

    // Binding SpotifyWebApiController signals to proper slots
    connect(spotifWebApiController,
            SIGNAL(songPersistRequest(const QString&, const QString&, const QString&)),
            songListController,
            SLOT(createSong(const QString &, const QString &, const QString &)));
    connect(spotifWebApiController, SIGNAL(clearSongSearchResults()),
            &mainWindow, SLOT(clearSongSearchResults()));
    connect(spotifWebApiController, SIGNAL(appendSongToSearchResults(const QString&)),
            &mainWindow, SLOT(appendSongSearchResult(const QString&)));

    // Binding MainWindow to proper conntrollers
    connect(mainWindow.getPlaylistContainer(), SIGNAL(itemDeleted(int)),
            playlistController, SLOT(removePlaylist(int)));
    connect(mainWindow.getPlaylistContainer(), SIGNAL(itemClicked(int)),
            songListController, SLOT(loadPlaylist(int)));
    connect(mainWindow.getPlaylistContainer(), SIGNAL(itemClicked(int)),
            playlistController, SLOT(selectPlaylist(int)));
    connect(mainWindow.getSongListView(), SIGNAL(itemDeleted(int)),
            songListController, SLOT(removeSong(int)));
    connect(&mainWindow, SIGNAL(playlistAddRequested(const QString&)),
            playlistController, SLOT(createPlaylist(const QString&)));
    connect(&mainWindow, SIGNAL(songSearchRequested(const QString&)),
            spotifWebApiController, SLOT(searchSongs(const QString&)));
    connect(&mainWindow, SIGNAL(saveSongFromSearch(int)),
            spotifWebApiController, SLOT(songSaveRequested(int)));
}

void Core::sendLoadAppSignal()
{
    emit mustLoadAppData();
    emit mustStartNetwork();
}
