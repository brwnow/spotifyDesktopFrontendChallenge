#include "core.hpp"

#include <QFileInfo>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

QMutex Core::runMutex;

const QString Core::databaseDriver("QSQLITE");
const QString Core::databaseName("db.dat");

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

        bool appInitializationFailed = false;
        Core core(app);

        if(!core.connectToDatabase())
            appInitializationFailed = true;

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
                setErrorDialog(QString("Database query error"),
                               QString("Error while creating database tables"));

                return false;
            }
        }

        return true;
    }
    else
    {
        setErrorDialog(QString("Cannot open database"), QString("Unable to establish a database connection"));

        return false;
    }
}

bool Core::createDatabaseSchema()
{
    QSqlQuery query(database);

    if(!query.exec(QString("CREATE TABLE PLAYLIST(ID INT PRIMARY KEY, NAME VARCHAR(100))")))
        return false;

    if(!query.exec(QString("CREATE TABLE SONG(ID INT PRIMARY KEY, NAME VARCHAR(100))")))
        return false;

    if(!query.exec(QString("CREATE TABLE CREDENTIALS(LOGIN VARCHAR(30), PASSWORD VARCHAR(30))")))
        return false;

    return true;
}
