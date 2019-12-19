#ifndef SONG_VIEW_HPP
#define SONG_VIEW_HPP

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class SongView : public QWidget
{
    Q_OBJECT

public:
    SongView(const QString &title, int songID, QWidget *parent = nullptr);
    ~SongView();

    int getSongID() const;

signals:
    void deleteTriggered(int songID);

private:
    QLabel *songTitle;
    QPushButton *deleteButton;
    int songID;

    void setupWidgets(const QString &title);
    void setupLayout();
    void setupConnections();
};

#endif // SONG_VIEW_HPP
