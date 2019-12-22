#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "deletablelistview.hpp"
#include "playerview.hpp"

#include <QLineEdit>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainWindow const &) = delete;
    void operator = (MainWindow const &) = delete;

    static MainWindow& getInstance();

    DeletableListView* getPlaylistContainer();
    DeletableListView* getSongListView();
    PlayerView * getPlayerView();

signals:
    void playlistAddRequested(const QString &title);

private:
    // Percentage of desktop dimensions that MainWindow will assume
    static const double windowPercentageOfDesktop;

    DeletableListView *playlistContainer, *songListView;
    PlayerView *playerView;
    QLineEdit *newPlaylistTextEdit;
    QPushButton *addPlaylistButton;
    QLineEdit *songSearchTextEdit;
    QPushButton *searchButton;
    QListWidget *searchResultList;

    MainWindow(QWidget *parent = nullptr);

    void setupWindow();
    void setupWidgets();
    void setupLayout();
    void setupConnections();

private slots:
    void onAddPlaylistTriggered();

};
#endif // MAINWINDOW_HPP
