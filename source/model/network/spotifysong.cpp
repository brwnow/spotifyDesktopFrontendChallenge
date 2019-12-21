#include "spotifysong.hpp"

SpotifySong::SpotifySong(const QString& id, const QString& name, const QString& uri) :
    id(id),
    name(name),
    uri(uri)
{
}

const QString &SpotifySong::getId() const
{
    return id;
}

const QString &SpotifySong::getName() const
{
    return name;
}

const QString &SpotifySong::getUri() const
{
    return uri;
}
