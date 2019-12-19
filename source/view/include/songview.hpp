#ifndef SONG_VIEW_HPP
#define SONG_VIEW_HPP

#include <QWidget>

class SongView : public QWidget
{
    Q_OBJECT

public:
    SongView(QWidget *parent = nullptr);
    ~SongView();

};

#endif // SONG_VIEW_HPP
