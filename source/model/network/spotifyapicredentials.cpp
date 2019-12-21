#include "spotifyapicredentials.hpp"

SpotifyApiCredentials::SpotifyApiCredentials() :
    clientId("24d9ba2e4d9d4fc4b783bc459998dcea"),
    clientSecret("5fc67386c7894ae795f20bb325e2cb1e")
{
    // TODO: load credentials from resource files
}

const QString &SpotifyApiCredentials::getClientId() const
{
    return clientId;
}

const QString &SpotifyApiCredentials::getClientSecret() const
{
    return clientSecret;
}
