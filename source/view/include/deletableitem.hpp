#ifndef PLAYLIST_VIEW_HPP
#define PLAYLIST_VIEW_HPP

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class PlaylistView : public QWidget
{
    Q_OBJECT

public:
    PlaylistView(const QString &title, int playlistID, QWidget *parent = nullptr);
    ~PlaylistView();

    int getPlaylistID() const;

signals:
    void deleteTriggered(int playlistID);

private:
    QLabel *playlistName;
    QPushButton *deleteButton;
    int playlistID;

    void setupWidgets(const QString &title);
    void setupLayout();
    void setupConnections();

};

#endif // PLAYLIST_VIEW_HPP
