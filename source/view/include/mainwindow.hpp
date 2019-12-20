#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "deletablelistview.hpp"
#include "playerview.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainWindow const &) = delete;
    void operator = (MainWindow const &) = delete;

    ~MainWindow();

    static MainWindow& getInstance();

    DeletableListView* getPlaylistContainer();
    DeletableListView* getSongListView();
    PlayerView * getPlayerView();

private:
    DeletableListView *playlistContainer, *songListView;
    PlayerView *playerView;

    MainWindow(QWidget *parent = nullptr);

    void setupWidgets();
    void setupLayout();
    void setupWindow();

};
#endif // MAINWINDOW_HPP
