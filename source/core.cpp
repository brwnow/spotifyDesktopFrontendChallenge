#include "core.hpp"

QMutex Core::runMutex;

int Core::run(QApplication &app)
{
    static bool isCoreRunning = false;

    runMutex.lock();

    if(!isCoreRunning)
    {
        isCoreRunning = true;
        runMutex.unlock();

        Core core(app);

        return core.exec();
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

int Core::exec()
{
    mainWindow.show();

    return app.exec();
}
