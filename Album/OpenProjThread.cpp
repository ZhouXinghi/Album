#include "OpenProjThread.h"
#include "ProjTreeItem.h"
#include <QDir>
#include "constants.h"

OpenProjThread::OpenProjThread(const QString& srcPath, int fileCount, QTreeWidget* widget, QTreeWidgetItem* rootItem, QObject* parent)
    : QThread(parent)
    , _srcPath(srcPath)
    , _fileCount(fileCount)
    , _widget(widget)
    , _bStop(false)
    , _rootItem(rootItem)
{

}

void OpenProjThread::run()
{
    OpenProj(_srcPath, _rootItem, &_fileCount, _widget, _rootItem, nullptr);
    emit SigFinishProgress(_fileCount);
}

void OpenProjThread::OpenProj(const QString& srcPath, QTreeWidgetItem* parentItem, int* fileCount, QTreeWidget* widget, QTreeWidgetItem* rootItem, QTreeWidgetItem* preItem)
{
    QDir srcDir(srcPath);
    srcDir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    srcDir.setSorting(QDir::Name);
    for (const QFileInfo& fileInfo : srcDir.entryInfoList()) {
        if (_bStop) {
            return;
        }
        if (fileInfo.isDir()) {
            if (_bStop) {
                return;
            }
            auto* item = new ProjTreeItem(parentItem, fileInfo.fileName(), fileInfo.absoluteFilePath(), _rootItem, TreeItemDir);
            item->setData(0, Qt::DisplayRole, fileInfo.fileName());
            item->setData(0, Qt::DecorationRole, QIcon(""));
            item->setData(0, Qt::ToolTipRole, fileInfo.absoluteFilePath());
            OpenProj(fileInfo.absoluteFilePath(), item, fileCount, _widget, rootItem, preItem);
        }
        else {
            if (_bStop) {
                return;
            }
            QString suffix = fileInfo.completeSuffix();
            if (suffix != "png" && suffix != "jpeg" && suffix != "jpg") {
                continue;
            }
            ++(*fileCount);
            emit SigUpdateProgress(*fileCount);

            auto* item = new ProjTreeItem(parentItem, fileInfo.fileName(), fileInfo.absoluteFilePath(), _rootItem, TreeItemPic);
            item->setData(0, Qt::DisplayRole, fileInfo.fileName());
            item->setData(0, Qt::DecorationRole, QIcon(""));
            item->setData(0, Qt::ToolTipRole, fileInfo.absoluteFilePath());

            if (preItem != nullptr) {
                dynamic_cast<ProjTreeItem*>(preItem)->setNextItem(item);
            }
            dynamic_cast<ProjTreeItem*>(item)->setPreItem(preItem);
            preItem = item;
        }
    }
}

