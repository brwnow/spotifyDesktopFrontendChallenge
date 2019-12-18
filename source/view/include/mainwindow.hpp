#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "playlistcontainerview.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    PlaylistContainerView *playlistContainer;

    void setupWidgets();
    void setupLayout();
    void setupWindow();
};
#endif // MAINWINDOW_HPP
