#ifndef PLAYER_VIEW_HPP
#define PLAYER_VIEW_HPP

#include <QWidget>

class PlayerView : public QWidget
{
    Q_OBJECT

public:
    PlayerView(QWidget *parent = nullptr);
    ~PlayerView();

};

#endif // PLAYER_VIEW_HPP
