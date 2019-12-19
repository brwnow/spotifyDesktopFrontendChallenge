#ifndef SONG_LIST_VIEW_HPP
#define SONG_LIST_VIEW_HPP

#include <QLabel>
#include <QListWidget>
#include <QWidget>

class SongListView : public QWidget
{
    Q_OBJECT

public:
    SongListView(QWidget *parent = nullptr);
    ~SongListView();

signals:
    void songClicked(int songID);
    void songDeleted(int songID);

public slots:
    void createSong(const QString &songName, int songID);
    void removeSong(int songID);

private:
    QLabel *playlistName;
    QListWidget *listOfSongs;

    void setupWidgets();
    void setupLayout();
    void setupConnections();

private slots:
    void onSongSelected(QListWidgetItem *songItem);

};

#endif // SONG_LIST_VIEW_HPP
