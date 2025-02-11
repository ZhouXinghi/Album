#pragma once
#include <QTreeWidget>

class ProjTreeItem : public QTreeWidgetItem
{
public:
    ProjTreeItem(QTreeWidget* view, const QString& name, const QString& path, int type = Type);
    ProjTreeItem(QTreeWidgetItem* parent, const QString& name, const QString& path, QTreeWidgetItem* root, int type = Type);
public:
    const QString& getPath() const;
    QTreeWidgetItem* getRootItem() const;
    void setPreItem(QTreeWidgetItem* item);
    void setNextItem(QTreeWidgetItem* item);
    ProjTreeItem* getPreItem() const;
    ProjTreeItem* getNextItem() const;
    ProjTreeItem* getLastPicChild() const;
    ProjTreeItem* getFirstPicChild() const;

private:
    QString _path;
    QString _name;
    QTreeWidgetItem* _rootItem;
    QTreeWidgetItem* _preItem;
    QTreeWidgetItem* _nextItem;
};

