#ifndef SPOTIFY_SONG_HPP
#define SPOTIFY_SONG_HPP

#include <QString>


class SpotifySong
{
public:
    SpotifySong(const QString& id, const QString& name, const QString& uri);

    const QString& getId() const;
    const QString& getName() const;
    const QString& getUri() const;

private:
    const QString id;
    const QString name;
    const QString uri;

};

#endif // SPOTIFY_SONG_HPP
