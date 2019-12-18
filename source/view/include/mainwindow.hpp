#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "playlistcontainerview.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();

    static MainWindow& getInstance();

private:
    PlaylistContainerView *playlistContainer;

    MainWindow(QWidget *parent = nullptr);

    void setupWidgets();
    void setupLayout();
    void setupWindow();

};
#endif // MAINWINDOW_HPP
