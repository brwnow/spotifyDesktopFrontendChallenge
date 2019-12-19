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
    ~DeletableItem();

    int getID() const;

signals:
    void deleteTriggered(int id);

private:
    QLabel *title;
    QPushButton *deleteButton;
    int id;

    void setupWidgets(const QString &title);
    void setupLayout();
    void setupConnections();

};

#endif // DELETABLE_ITEM_HPP
