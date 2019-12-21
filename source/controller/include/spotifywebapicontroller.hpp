#ifndef SPOTIFY_WEB_API_CONTROLLER_HPP
#define SPOTIFY_WEB_API_CONTROLLER_HPP

#include "spotifyapicredentials.hpp"
#include "spotifysong.hpp"

#include <vector>

#include <QNetworkAccessManager>
#include <QObject>

using std::vector;

class SpotifyWebApiController : public QObject
{
    Q_OBJECT

public:
    SpotifyWebApiController(QObject *parent = nullptr);

    bool isTokenValid() const;

signals:
    void networkIsDown();
    void networkIsUp();
    void authFailed();
    void appendSongToSearchResults(const QString&);
    void clearSongSearchResults();
    void songLoaded();

public slots:
    void obtainAccessToken();
    void searchSongs(const QString &query);
    void getSong(const QString &songID);

private:
    static const qint64 TOKEN_EXPIRED;

    static const QString API_URL;
    static const QString SEARCH_ENDPOINT;
    static const QString SEARCH_TYPE_PARAM;

    static const QString ACCOUNT_API_URL;
    static const QString TOKEN_ENDPOINT;

    static const QString JSON_TOKEN_FIELD;
    static const QString JSON_TOKENTYPE_FIELD;
    static const QString JSON_TOKEN_EXPIRE_FIELD;
    static const QString JSON_TOKEN_ERROR;
    static const QString JSON_TOKEN_ERROR_STATUS;
    static const QString JSON_TOKEN_ERROR_MESSAGE;

    SpotifyApiCredentials credentials;

    vector<SpotifySong> searchCache;

    QNetworkAccessManager networkAccessManager;
    QString token;
    QString tokenType;
    qint64 tokenExpireTime;

    void setupToken(QNetworkReply *reply);
    void parseSearchResult(QNetworkReply *reply);
    void cacheSearchResult(const SpotifySong &song);
    void clearSearchCache();

private slots:
    void finished(QNetworkReply *reply);
    void networkAccessibilityChanged(QNetworkAccessManager::NetworkAccessibility access);

};

#endif // SPOTIFY_WEB_API_CONTROLLER_HPP
