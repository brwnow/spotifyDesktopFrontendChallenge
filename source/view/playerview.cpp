#include "playerview.hpp"

#include <QGridLayout>

PlayerView::PlayerView(QWidget *parent) :
    QWidget(parent)
{
    isPlaying = false;

    setupWidgets();
    setupLayout();
    setupConnections();
}

PlayerView::~PlayerView()
{

}

bool PlayerView::getIsPlaying() const
{
    return isPlaying;
}

void PlayerView::setPlaying(bool playing)
{
    if(playing != isPlaying)
    {
        isPlaying = playing;

        if(isPlaying)
        {
            playPauseButton->setText(QString("Pause"));
        }
        else
        {
            playPauseButton->setText(QString("Play"));
        }
    }
}

void PlayerView::setupSong(const QString &songName, int resolution)
{
    this->songName->setText(songName);
    this->currentTime->setText(QString("00:00"));
    navigationBar->setRange(0, resolution);
    navigationBar->setValue(0);
}

void PlayerView::updateSongProgress(int songPosition, const QString &currentTime)
{
    navigationBar->setValue(songPosition);
    this->currentTime->setText(currentTime);
}

void PlayerView::setNoSong()
{
    setPlaying(false);
    songName->setText(QString(""));
    currentTime->setText(QString("00:00"));
    navigationBar->setValue(0);
}

void PlayerView::setupWidgets()
{
    songName = new QLabel();
    currentTime = new QLabel(QString("00:00"));
    playPauseButton = new QPushButton(QString("Play"));
    previousSongButton = new QPushButton(QString("<<"));
    nextSongButton = new QPushButton(QString(">>"));

    navigationBar = new QSlider(Qt::Orientation::Horizontal);
    navigationBar->setTracking(false);
}

void PlayerView::setupLayout()
{
    QGridLayout *layout = new QGridLayout();

    layout->addWidget(songName, 0, 0, 1, 5, Qt::AlignHCenter);
    layout->addWidget(playPauseButton, 1, 0);
    layout->addWidget(previousSongButton, 1, 1);
    layout->addWidget(nextSongButton, 1, 2);
    layout->addWidget(navigationBar, 1, 3);
    layout->addWidget(currentTime, 1, 4);

    layout->setColumnStretch(3, 1);

    this->setLayout(layout);
}

void PlayerView::setupConnections()
{
    connect(playPauseButton, SIGNAL(clicked()), this, SLOT(onPlayPauseButtonClicked()));
    connect(previousSongButton, SIGNAL(clicked()), this, SIGNAL(previousClicked()));
    connect(nextSongButton, SIGNAL(clicked()), this, SIGNAL(nextClicked()));
    connect(navigationBar, SIGNAL(sliderMoved(int)), this, SIGNAL(songPositionSearching(int)));
    connect(navigationBar, SIGNAL(valueChanged(int)), this, SIGNAL(songPositionChanged(int)));
}

void PlayerView::onPlayPauseButtonClicked()
{
    if(isPlaying)
    {
        emit pauseClicked();
    }
    else
    {
        emit playClicked();
    }
}
