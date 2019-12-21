#ifndef DELETABLE_LIST_VIEW_HPP
#define DELETABLE_LIST_VIEW_HPP

#include <map>

#include <QLabel>
#include <QListWidget>

using std::map;

class DeletableListView : public QListWidget
{
    Q_OBJECT

public:
    DeletableListView(QWidget *parent = nullptr);

signals:
    void itemClicked(int id);
    void itemDeleted(int id);

public slots:
    void createItem(const QString &title, int id);
    void removeItem(int id);
    void clearItems();

private:
    map<int, QListWidgetItem*> itemIdMap;

private slots:
    void onItemSelected(QListWidgetItem *item);
};

#endif // DELETABLE_LIST_VIEW_HPP
