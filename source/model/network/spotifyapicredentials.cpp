#include "spotifyapicredentials.hpp"

#include <QDebug>
#include <QFile>

SpotifyApiCredentials::SpotifyApiCredentials()
{
    QFile file(":/api/credentials/api_credentials.txt");

    if(file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Credentials resource file opened successfully";

        clientId = file.readLine().trimmed();
        clientSecret = file.readLine().trimmed();
    }
    else
    {
        qDebug() << "Credentials resource file failed to open";
    }
}

const QString &SpotifyApiCredentials::getClientId() const
{
    return clientId;
}

const QString &SpotifyApiCredentials::getClientSecret() const
{
    return clientSecret;
}
