#ifndef DELETABLE_LIST_VIEW_HPP
#define DELETABLE_LIST_VIEW_HPP

#include <map>

#include <QWidget>
#include <QLabel>
#include <QListWidget>

using std::map;

class DeletableListView : public QWidget
{
    Q_OBJECT

public:
    DeletableListView(const QString &listTitle, QWidget *parent = nullptr);
    ~DeletableListView();

signals:
    void itemClicked(int id);
    void itemDeleted(int id);

public slots:
    void createItem(const QString &title, int id);
    void removeItem(int id);
    void clearItems();

private:
    QLabel *titleLabel;
    QListWidget *listOfItems;
    map<int, QListWidgetItem*> itemIdMap;

    void setupWidgets(const QString &listTitle);
    void setupLayout();
    void setupConnections();

private slots:
    void onItemSelected(QListWidgetItem *item);
};

#endif // DELETABLE_LIST_VIEW_HPP
