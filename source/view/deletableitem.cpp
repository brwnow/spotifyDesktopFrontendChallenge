#include "deletableitem.hpp"

#include <QVBoxLayout>

DeletableItem::DeletableItem(const QString &title, int id, QWidget *parent) :
    QWidget(parent),
    id(id)
{
    setupWidgets(title);
    setupLayout();
    setupConnections();
}

int DeletableItem::getID() const
{
    return id;
}

void DeletableItem::setupWidgets(const QString &title)
{
    this->title = new QLabel(title);
    deleteButton = new QPushButton(QString("Del"));
}

void DeletableItem::setupLayout()
{
    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(title, 1);
    layout->addWidget(deleteButton, 0);

    this->setLayout(layout);
}

void DeletableItem::setupConnections()
{
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(onDeleteButtonClicked()));
}

void DeletableItem::onDeleteButtonClicked()
{
    emit deleteTriggered(id);
}
