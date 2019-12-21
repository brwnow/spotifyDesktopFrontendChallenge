#ifndef SPOTIFY_WEB_API_CONTROLLER_HPP
#define SPOTIFY_WEB_API_CONTROLLER_HPP

#include <QObject>

class SpotifyWebApiController : public QObject
{
    Q_OBJECT

public:
    SpotifyWebApiController(QObject *parent = nullptr);

};

#endif // SPOTIFY_WEB_API_CONTROLLER_HPP
