#include "spotifywebapicontroller.hpp"

#include <QAuthenticator>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>

const qint64 SpotifyWebApiController::TOKEN_EXPIRED = -1;

const QString SpotifyWebApiController::API_URL("https://api.spotify.com");
const QString SpotifyWebApiController::SEARCH_ENDPOINT("/v1/search?q=");
const QString SpotifyWebApiController::SEARCH_TYPE_PARAM("&type=track");

const QString SpotifyWebApiController::ACCOUNT_API_URL("https://accounts.spotify.com");
const QString SpotifyWebApiController::TOKEN_ENDPOINT("/api/token");

const QString SpotifyWebApiController::JSON_TOKEN_FIELD("access_token");
const QString SpotifyWebApiController::JSON_TOKENTYPE_FIELD("token_type");
const QString SpotifyWebApiController::JSON_TOKEN_EXPIRE_FIELD("expires_in");
const QString SpotifyWebApiController::JSON_TOKEN_ERROR("error");
const QString SpotifyWebApiController::JSON_TOKEN_ERROR_STATUS("status");
const QString SpotifyWebApiController::JSON_TOKEN_ERROR_MESSAGE("message");

SpotifyWebApiController::SpotifyWebApiController(QObject *parent) :
    QObject(parent),
    networkAccessManager(this),
    tokenExpireTime(TOKEN_EXPIRED)
{
    connect(&networkAccessManager,
            SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
            this,
            SLOT(networkAccessibilityChanged(QNetworkAccessManager::NetworkAccessibility)));

    connect(&networkAccessManager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(finished(QNetworkReply*)));
}

bool SpotifyWebApiController::isTokenValid() const
{
    return tokenExpireTime > QDateTime::currentMSecsSinceEpoch();
}

void SpotifyWebApiController::obtainAccessToken()
{
    QNetworkRequest request(ACCOUNT_API_URL + TOKEN_ENDPOINT);
    QByteArray encodedCredentials;
    QByteArray postData;

    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader,
                      "application/x-www-form-urlencoded");

    encodedCredentials.append(credentials.getClientId())
                        .append(":")
                        .append(credentials.getClientSecret());

    request.setRawHeader(QByteArray("Authorization"),
                         QByteArray("Basic ") + encodedCredentials.toBase64());

    postData.append("grant_type=client_credentials");

    networkAccessManager.post(request, postData);
}

void SpotifyWebApiController::searchSongs(const QString &query)
{
    QNetworkRequest request(API_URL + SEARCH_ENDPOINT + query + SEARCH_TYPE_PARAM);
/*
    request.setRawHeader(QByteArray("Authorization"),
                         QByteArray("Bearer ").append(token));*/

    request.setRawHeader(QByteArray("Authorization"),
                         QByteArray("Bearer ").append("BQA1wk4_FwJxW2Lfaj6imKxBGFPfV_ww86SLjvmlvVb04w4_vdv8BbPiGGJuJgKfQ-sRyqFKy_xeRD_0qUs"));

    networkAccessManager.get(request);
}

void SpotifyWebApiController::getSong(const QString &songID)
{
    Q_UNUSED(songID);
}

void SpotifyWebApiController::setupToken(QNetworkReply *reply)
{
    QJsonDocument replyBody = QJsonDocument::fromJson(reply->readAll());
    QJsonObject replyJson = replyBody.object();

    if(reply->error() == QNetworkReply::NetworkError::NoError)
    {
        int tokenExpiration;

        qDebug() << "Parsing token reply json...";

        token = replyJson[JSON_TOKEN_FIELD].toString();
        qDebug() << JSON_TOKEN_FIELD << ":" << token;

        tokenType = replyJson[JSON_TOKENTYPE_FIELD].toString();
        qDebug() << JSON_TOKENTYPE_FIELD << ":" << tokenType;

        tokenExpiration = replyJson[JSON_TOKEN_EXPIRE_FIELD].toInt();
        qDebug() << JSON_TOKEN_EXPIRE_FIELD << ":" << tokenExpiration;

        tokenExpireTime = QDateTime::currentSecsSinceEpoch() + tokenExpireTime;
    }
    else
    {
        QString errorMsg = replyJson[JSON_TOKEN_ERROR]
                .toObject()[JSON_TOKEN_ERROR_MESSAGE].toString();
        int errorStatus = replyJson[JSON_TOKEN_ERROR]
                .toObject()[JSON_TOKEN_ERROR_STATUS].toInt();

        qDebug() << errorMsg << "(" << errorStatus << ")";

        emit authFailed();
    }
}

void SpotifyWebApiController::parseSearchResult(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NetworkError::NoError)
    {
        QJsonDocument replyBody = QJsonDocument::fromJson(reply->readAll());
        QJsonObject replyJson = replyBody.object()["tracks"].toObject();
        int songsFound;

        clearSearchCache();

        qDebug() << "Parsing song search result json...";

        songsFound = replyJson["total"].toInt();
        qDebug() << "Songs found: " << songsFound;

        QJsonArray tracks = replyJson["items"].toArray();
        for(QJsonArray::iterator it = tracks.begin(); it != tracks.end(); ++it)
        {
            QJsonObject trackJson = it->toObject();
            QString songID;
            QString songName;
            QString songUri;

            songID = trackJson["id"].toString();
            songName = trackJson["name"].toString();
            songUri = trackJson["uri"].toString();
            qDebug() << "song : {" << songID << ',' << songName << ',' << songUri << "}";

            cacheSearchResult(SpotifySong(songID, songName, songUri));
        }
    }
}

void SpotifyWebApiController::cacheSearchResult(const SpotifySong &song)
{
    qDebug() << "Appending search result to cache at position " << searchCache.size();
    searchCache.push_back(song);

    emit appendSongToSearchResults(song.getName());
}

void SpotifyWebApiController::clearSearchCache()
{
    qDebug() << "Clearing search cache";
    searchCache.clear();

    emit clearSongSearchResults();
}

void SpotifyWebApiController::finished(QNetworkReply *reply)
{
    QString requestedUrl = reply->request().url().toString();

    qDebug() << "<SpotifyWebApiController::finished>";
    qDebug() << "Requested url: " << requestedUrl;
    qDebug() << reply->error();

    if(requestedUrl.contains(ACCOUNT_API_URL))
        setupToken(reply);
    else if(requestedUrl.contains(SEARCH_ENDPOINT))
        parseSearchResult(reply);

    reply->deleteLater();

    qDebug() << "</SpotifyWebApiController::finished>";
}

void SpotifyWebApiController::networkAccessibilityChanged(QNetworkAccessManager::NetworkAccessibility access)
{
    qDebug() << "<SpotifyWebApiController::networkAccessibilityChanged>";

    switch(access)
    {
    case QNetworkAccessManager::Accessible:
        qDebug() << "Network is accessible";

        emit networkIsUp();
        break;

    case QNetworkAccessManager::UnknownAccessibility:
        qDebug() << "Network is in unknown state";

        break;

    case QNetworkAccessManager::NotAccessible:
        qDebug() << "Network is not accessible";

        emit networkIsDown();
        break;
    }

    qDebug() << "</SpotifyWebApiController::networkAccessibilityChanged>";
}
