#ifndef SONG_LIST_CONTROLLER_HPP
#define SONG_LIST_CONTROLLER_HPP

#include <QObject>

class SongListController : public QObject
{
public:
    SongListController(QObject *parent = nullptr);
};

#endif // SONG_LIST_CONTROLLER_HPP
