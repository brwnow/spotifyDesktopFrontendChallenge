#ifndef PLAYER_VIEW_HPP
#define PLAYER_VIEW_HPP

#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

class PlayerView : public QWidget
{
    Q_OBJECT

public:
    PlayerView(QWidget *parent = nullptr);
    ~PlayerView();

    bool getIsPlaying() const;

signals:
    void playClicked();
    void pauseClicked();
    void nextClicked();
    void previousClicked();
    void songPositionSearching(int);
    void songPositionChanged(int);

public slots:
    void setPlaying(bool playing);
    void setupSong(const QString &songName, int resolution);
    void updateSongProgress(int songPosition, const QString &currentTime);
    void setNoSong();

private:
    QLabel *songName, *currentTime;
    QPushButton *playPauseButton, *previousSongButton, *nextSongButton;
    QSlider *navigationBar;
    bool isPlaying;

    void setupWidgets();
    void setupLayout();
    void setupConnections();

private slots:
    void onPlayPauseButtonClicked();

};

#endif // PLAYER_VIEW_HPP
