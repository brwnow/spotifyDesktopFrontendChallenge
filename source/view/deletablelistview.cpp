#include "deletablelistview.hpp"

#include <exception>

#include "deletableitem.hpp"

#include <QDebug>

#include <QVBoxLayout>

using std::exception;

DeletableListView::DeletableListView(QWidget *parent) :
    QListWidget(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);

    connect(this, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onItemSelected(QListWidgetItem*)));
}

void DeletableListView::createItem(const QString &title, int id)
{
    DeletableItem *deletableItem = new DeletableItem(title, id);
    QListWidgetItem *item = new QListWidgetItem();

    qDebug() << "<DeletableListView::createItem title = " << title << " id = " << id << ">";

    item->setSizeHint(deletableItem->sizeHint());

    connect(deletableItem, SIGNAL(deleteTriggered(int)), this, SIGNAL(itemDeleted(int)));

    removeItem(id);

    itemIdMap[id] = item;

    addItem(item);
    setItemWidget(item, deletableItem);

    qDebug() << "</DeletableListView::createItem>";
}

void DeletableListView::removeItem(int id)
{
    map<int, QListWidgetItem*>::iterator it = itemIdMap.find(id);

    if(it != itemIdMap.end())
    {
        int itemRow = row(it->second);

        // We need to manually delete the item since Qt doesn't handle it anymore when we take it
        delete takeItem(itemRow);
        itemIdMap.erase(it);
    }
}

void DeletableListView::clearItems()
{
    clear();
    itemIdMap.clear();
}

void DeletableListView::onItemSelected(QListWidgetItem *item)
{
    qDebug() << "<DeletableListView::onItemSelected>";

    try
    {
        const DeletableItem *deletableItem = dynamic_cast<DeletableItem*>(itemWidget(item));

        if(deletableItem != nullptr)
        {
            emit itemClicked(deletableItem->getID());
        }
    }
    catch(exception &ex)
    {
        qDebug() << "exception msg \"" << ex.what() << "\"";
    }

    qDebug() << "</DeletableListView::onItemSelected>";
}
