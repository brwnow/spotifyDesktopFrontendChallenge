#ifndef PLAYLIST_CONTAINER_VIEW_HPP
#define PLAYLIST_CONTAINER_VIEW_HPP

#include <map>

#include <QWidget>
#include <QLabel>
#include <QListWidget>

using std::map;

class PlaylistContainerView : public QWidget
{
    Q_OBJECT

public:
    PlaylistContainerView(QWidget *parent = nullptr);
    ~PlaylistContainerView();

signals:
    void playlistClicked(int playlistID);
    void playlistDeleted(int playlistID);

public slots:
    void createPlaylist(const QString &title, int playlistID);
    void removePlaylist(int playlistID);

private:
    QLabel *titleLabel;
    QListWidget *listOfPlaylists;
    map<int, QListWidgetItem*> playlistIdMap;

    void setupWidgets();
    void setupLayout();
    void setupConnections();

private slots:
    void onPlaylistSelected(QListWidgetItem *playlistItem);
};

#endif // PLAYLIST_CONTAINER_VIEW_HPP
