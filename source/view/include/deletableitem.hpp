#ifndef DELETABLE_ITEM_HPP
#define DELETABLE_ITEM_HPP

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class DeletableItem : public QWidget
{
    Q_OBJECT

public:
    DeletableItem(const QString &title, int id, QWidget *parent = nullptr);

    int getID() const;

    void setTitlePointSize(int pointSize);

signals:
    void deleteTriggered(int id);

private:
    QLabel *title;
    QPushButton *deleteButton;
    int id;

    void setupWidgets(const QString &title);
    void setupLayout();
    void setupConnections();

private slots:
    void onDeleteButtonClicked();

};

#endif // DELETABLE_ITEM_HPP
