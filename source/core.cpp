#include "core.hpp"

#include <QDebug>

#include <QFileInfo>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

QMutex Core::runMutex;

const QString Core::databaseDriver("QSQLITE");
const QString Core::databaseName("db.dat");

QString Core::errorMsgTitle;
QString Core::errorMsg;

Core::~Core()
{
    database.close();
}

int Core::run(QApplication &app)
{
    static bool isCoreRunning = false;

    runMutex.lock();

    if(!isCoreRunning)
    {
        isCoreRunning = true;
        runMutex.unlock();

        bool appInitializationFailed = false;
        Core core(app);

        if(!core.connectToDatabase())
            appInitializationFailed = true;

        core.initControllers();
        core.bindMVC();
        core.sendLoadAppSignal();

        if(!appInitializationFailed)
        {
            return core.exec();
        }
        else
        {
            QMessageBox::critical(nullptr, errorMsgTitle, errorMsg, QMessageBox::Ok);

            return 0;
        }
    }
    else
    {
        return CORE_ALREADY_RUNNING;
    }
}

Core::Core(QApplication &app) :
    app(app),
    mainWindow(MainWindow::getInstance())
{
}

void Core::setErrorDialog(const QString &title, const QString &msg)
{
    errorMsgTitle = title;
    errorMsg = msg;
}

int Core::exec()
{
    mainWindow.show();

    return app.exec();
}

bool Core::connectToDatabase()
{
    bool mustCreateSchema = !QFileInfo::exists(databaseName);

    database = QSqlDatabase::addDatabase(databaseDriver);
    database.setDatabaseName(databaseName);

    if(database.open())
    {
        if(mustCreateSchema)
        {
            if(!createDatabaseSchema())
            {
                setErrorDialog("Database query error",
                               "Error while creating database tables");

                return false;
            }
        }

        return true;
    }
    else
    {
        qDebug() << "Database error: " << database.lastError();

        setErrorDialog("Cannot open database", "Unable to establish a database connection");

        return false;
    }
}

bool Core::createDatabaseSchema()
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

    if(!query.exec("CREATE TABLE CREDENTIALS("
                    "LOGIN VARCHAR(30) PRIMARY KEY,"
                    "PASSWORD VARCHAR(30))"))
    {
        qDebug() << query.lastError();
        success = false;
    }

    qDebug() << "</Core::dataBaseSchema>";

    return success;
}

void Core::initControllers()
{
    playlistController = new PlaylistController(database, this);
    songListController = new SongListController(database, this);
    spotifWebApiController = new SpotifyWebApiController(this);
}

void Core::bindMVC()
{
    connect(this, SIGNAL(mustLoadAppData()), playlistController, SLOT(loadView()));
    connect(this, SIGNAL(mustStartNetwork()),
            spotifWebApiController, SLOT(obtainAccessToken()));

    connect(playlistController, SIGNAL(playlistCreated(const QString&, int)),
            mainWindow.getPlaylistContainer(), SLOT(createItem(const QString&, int)));
    connect(playlistController, SIGNAL(playlistRemoved(int)),
            mainWindow.getPlaylistContainer(), SLOT(removeItem(int)));

    // SongListController must be notified when a playlist is deleted. If the opened playlist
    // is deleted, SongListController must clean the SongListView
    connect(playlistController, SIGNAL(playlistRemoved(int)),
            songListController, SLOT(clearPlaylist(int)));

    connect(songListController, SIGNAL(songCreated(const QString&, int)),
            mainWindow.getSongListView(), SLOT(createItem(const QString&, int)));
    connect(songListController, SIGNAL(songRemoved(int)),
            mainWindow.getSongListView(), SLOT(removeItem(int)));
    connect(songListController, SIGNAL(playlistCleared()),
            mainWindow.getSongListView(), SLOT(clearItems()));

    connect(spotifWebApiController, SIGNAL(clearSongSearchResults()),
            &mainWindow, SLOT(clearSongSearchResults()));
    connect(spotifWebApiController, SIGNAL(appendSongToSearchResults(const QString&)),
            &mainWindow, SLOT(appendSongSearchResult(const QString&)));

    connect(mainWindow.getPlaylistContainer(), SIGNAL(itemDeleted(int)),
            playlistController, SLOT(removePlaylist(int)));
    connect(mainWindow.getPlaylistContainer(), SIGNAL(itemClicked(int)),
            songListController, SLOT(loadPlaylist(int)));
    connect(mainWindow.getSongListView(), SIGNAL(itemDeleted(int)),
            songListController, SLOT(removeSong(int)));
    connect(&mainWindow, SIGNAL(playlistAddRequested(const QString&)),
            playlistController, SLOT(createPlaylist(const QString&)));
    connect(&mainWindow, SIGNAL(songSearchRequested(const QString&)),
            spotifWebApiController, SLOT(searchSongs(const QString&)));
}

void Core::sendLoadAppSignal()
{
    emit mustLoadAppData();
    emit mustStartNetwork();
}
