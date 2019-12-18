#ifndef PLAYLIST_VIEW_HPP
#define PLAYLIST_VIEW_HPP

#include <QWidget>

class PlaylistView : public QWidget
{
    Q_OBJECT

public:
    PlaylistView(const QString &title, QWidget *parent = nullptr);
    ~PlaylistView();

private:
};

#endif // PLAYLIST_VIEW_HPP
