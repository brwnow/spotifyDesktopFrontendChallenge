#ifndef SPOTIFY_API_CREDENTIALS_HPP
#define SPOTIFY_API_CREDENTIALS_HPP

#include <QString>

class SpotifyApiCredentials
{
public:
    SpotifyApiCredentials();

    const QString& getClientId() const;
    const QString& getClientSecret() const;

private:
    QString clientId, clientSecret;

};

#endif // SPOTIFY_API_CREDENTIALS_HPP
