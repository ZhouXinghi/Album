#include "ProjTreeItem.h"

ProjTreeItem::ProjTreeItem(QTreeWidget* view, const QString& name, const QString& path, int type)
    : QTreeWidgetItem(view, type)
    , _path(path)
    , _name(name)
    , _rootItem(this)
    , _preItem(nullptr)
    , _nextItem(nullptr)
{
}

ProjTreeItem::ProjTreeItem(QTreeWidgetItem* parent, const QString& name, const QString& path, QTreeWidgetItem* root, int type)
    : QTreeWidgetItem(parent, type)
    , _name(name)
    , _path(path)
    , _rootItem(root)
    , _preItem(nullptr)
    , _nextItem(nullptr)
{
}

const QString& ProjTreeItem::getPath() const
{
    return _path;
}

QTreeWidgetItem* ProjTreeItem::getRootItem() const
{
    return _rootItem;
}

void ProjTreeItem::setPreItem(QTreeWidgetItem* item)
{
    _preItem = item;
}

void ProjTreeItem::setNextItem(QTreeWidgetItem* item)
{
    _nextItem = item;
}

ProjTreeItem* ProjTreeItem::getPreItem() const
{
    return dynamic_cast<ProjTreeItem*>(_preItem);
}

ProjTreeItem* ProjTreeItem::getNextItem() const
{
    return dynamic_cast<ProjTreeItem*>(_nextItem);
}

ProjTreeItem* ProjTreeItem::getLastPicChild() const
{
    return nullptr;
}

ProjTreeItem* ProjTreeItem::getFirstPicChild() const
{
    return nullptr;
}
