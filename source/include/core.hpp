#ifndef CORE_HPP
#define CORE_HPP

#include "mainwindow.hpp"

#include <QApplication>
#include <QMutex>
#include <QObject>

class Core : public QObject
{
    Q_OBJECT

public:
    static const int CORE_ALREADY_RUNNING = -1;
    static QMutex runMutex;

    static int run(QApplication &app);

    Core(Core const &) = delete;
    void operator = (Core const &) = delete;

private:
    QApplication &app;
    MainWindow &mainWindow;

    Core(QApplication &app);

    int exec();

};

#endif // CORE_HPP
