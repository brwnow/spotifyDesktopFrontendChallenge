#ifndef PLAYLIST_CONTAINER_VIEW_HPP
#define PLAYLIST_CONTAINER_VIEW_HPP

#include <QWidget>
#include <QLabel>
#include <QListWidget>

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

private:
    QLabel *titleLabel;
    QListWidget *listOfPlaylists;

    void setupWidgets();
    void setupLayout();
    void setupConnections();

private slots:
    void onPlaylistSelected(QListWidgetItem *playlistItem);
};

#endif // PLAYLIST_CONTAINER_VIEW_HPP
