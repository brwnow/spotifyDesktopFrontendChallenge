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
            playPauseButton->setText("Pause");
        }
        else
        {
            playPauseButton->setText("Play");
        }
    }
}

void PlayerView::setupSong(const QString &songName, int resolution)
{
    const QSignalBlocker signalBlocker(this);

    this->songName->setText(songName);
    this->currentTime->setText("00:00");
    navigationBar->setRange(0, resolution);
    navigationBar->setValue(0);
}

void PlayerView::updateSongProgress(int songPosition, int currentTimeSeconds)
{
    const QSignalBlocker signalBlocker(this);

    int minutes = currentTimeSeconds / 60;
    int seconds = currentTimeSeconds % 60;
    QString time = QString("%1:%2").
            arg(minutes, 2, 10, QLatin1Char('0')).
            arg(seconds, 2, 10, QLatin1Char('0'));

    navigationBar->setValue(songPosition);
    this->currentTime->setText(time);
}

void PlayerView::setNoSong()
{
    setPlaying(false);
    songName->setText("");
    currentTime->setText("00:00");
    navigationBar->setValue(0);
}

void PlayerView::setupWidgets()
{
    songName = new QLabel();
    currentTime = new QLabel("00:00");
    playPauseButton = new QPushButton("Play");
    previousSongButton = new QPushButton("<<");
    nextSongButton = new QPushButton(">>");

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
