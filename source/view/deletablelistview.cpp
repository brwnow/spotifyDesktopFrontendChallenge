#include "deletablelistview.hpp"

#include <exception>

#include "deletableitem.hpp"

#include <QDebug>

#include <QVBoxLayout>

using std::exception;

DeletableListView::DeletableListView(const QString&listTitle, QWidget *parent) :
    QWidget(parent)
{
    setupWidgets(listTitle);
    setupLayout();
    setupConnections();
}

DeletableListView::~DeletableListView()
{

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

    listOfItems->addItem(item);
    listOfItems->setItemWidget(item, deletableItem);

    qDebug() << "</DeletableListView::createItem>";
}

void DeletableListView::removeItem(int id)
{
    map<int, QListWidgetItem*>::iterator it = itemIdMap.find(id);

    if(it != itemIdMap.end())
    {
        int itemRow = listOfItems->row(it->second);

        // We need to manually delete the item since Qt doesn't handle it anymore when we take it
        delete listOfItems->takeItem(itemRow);
        itemIdMap.erase(it);
    }
}

void DeletableListView::clearItems()
{
    listOfItems->clear();
    itemIdMap.clear();
}

void DeletableListView::setupWidgets(const QString &listTitle)
{
    titleLabel = new QLabel(listTitle);
    listOfItems = new QListWidget();
    listOfItems->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    listOfItems->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
}

void DeletableListView::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(titleLabel, 0);
    layout->addWidget(listOfItems, 1);

    this->setLayout(layout);
}

void DeletableListView::setupConnections()
{
    connect(listOfItems, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onItemSelected(QListWidgetItem*)));
}

void DeletableListView::onItemSelected(QListWidgetItem *item)
{
    qDebug() << "<DeletableListView::onItemSelected>";

    try
    {
        const DeletableItem *deletableItem = dynamic_cast<DeletableItem*>(listOfItems->itemWidget(item));

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
