#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include <QObject>

class PlayerController : public QObject
{
    Q_OBJECT

public:
    PlayerController(QObject *parent = nullptr);

private:
    QMediaPlayer player;

};

#endif // PLAYER_CONTROLLER_HPP
