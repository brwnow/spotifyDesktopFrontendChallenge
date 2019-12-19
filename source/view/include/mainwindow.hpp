#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "playlistcontainerview.hpp"
#include "playerview.hpp"
#include "songlistview.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainWindow const &) = delete;
    void operator = (MainWindow const &) = delete;

    ~MainWindow();

    static MainWindow& getInstance();

private:
    PlaylistContainerView *playlistContainer;
    SongListView *songListView;
    PlayerView *playerView;

    MainWindow(QWidget *parent = nullptr);

    void setupWidgets();
    void setupLayout();
    void setupWindow();

};
#endif // MAINWINDOW_HPP
