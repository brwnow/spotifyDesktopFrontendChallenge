#include "mainwindow.hpp"

#include <core.hpp>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    return Core::run(app);
}
