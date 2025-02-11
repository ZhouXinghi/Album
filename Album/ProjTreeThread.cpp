#include "ProjTreeThread.h"
#include <QDir>
#include "ProjTreeItem.h"
#include "constants.h"

ProjTreeThread::ProjTreeThread(const QString& srcPath, const QString& distPath, QTreeWidgetItem* parentItem, 
    int fileCount, QTreeWidget* widget, QTreeWidgetItem* rootItem, QObject* parent)
    : QThread(parent)
    , _srcPath(srcPath)
    , _distPath(distPath)
    , _parentItem(parentItem)
    , _fileCount(fileCount)
    , _widget(widget)
    , _rootItem(rootItem)
    , _bStop(false)
{

}

ProjTreeThread::~ProjTreeThread()
{
}

void ProjTreeThread::run()
{
    CreateProjTree(_srcPath, _distPath, _parentItem, &_fileCount, _widget, _rootItem, nullptr);
    if (_bStop) {
        auto index = _widget->indexOfTopLevelItem(_rootItem);
        delete _widget->takeTopLevelItem(index);
        QDir(dynamic_cast<ProjTreeItem*>(_rootItem)->getPath()).removeRecursively();
        return;
    }
    emit SigFinishProgress(_fileCount);
}

void ProjTreeThread::CreateProjTree(const QString& srcPath, const QString& distPath, QTreeWidgetItem* parentItem, int* fileCount,
    QTreeWidget* widget, QTreeWidgetItem* rootItem, QTreeWidgetItem* preItem)
{
    if (_bStop) {
        return;
    }

    bool needCopy = true;
    if (srcPath == distPath) {
        needCopy = false;
    }
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
            QDir distDir(distPath);
            QString newDistDirPath = distDir.absoluteFilePath(fileInfo.fileName());
            QDir newDistDir(newDistDirPath);
            if (!newDistDir.exists()) {
                if (!newDistDir.mkpath(newDistDirPath)) {
                    continue;
                }
            }
            auto* item = new ProjTreeItem(parentItem, fileInfo.fileName(), newDistDirPath, rootItem, TreeItemDir);
            item->setData(0, Qt::DisplayRole, fileInfo.fileName());
            item->setData(0, Qt::DecorationRole, QIcon(""));
            item->setData(0, Qt::ToolTipRole, newDistDirPath);
            CreateProjTree(fileInfo.absoluteFilePath(), newDistDirPath, item, fileCount, widget, rootItem, preItem);
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
            if (!needCopy) {
                continue;
            }
            QDir distDir(distPath);
            QString distFilePath = distDir.absoluteFilePath(fileInfo.fileName());
            if (!QFile::copy(fileInfo.absoluteFilePath(), distFilePath)) {
                continue;
            }
            auto* item = new ProjTreeItem(parentItem, fileInfo.fileName(), distFilePath, rootItem, TreeItemPic);
            item->setData(0, Qt::DisplayRole, fileInfo.fileName());
            item->setData(0, Qt::DecorationRole, QIcon(""));
            item->setData(0, Qt::ToolTipRole, distFilePath);

            if (preItem != nullptr) {
                dynamic_cast<ProjTreeItem*>(preItem)->setNextItem(item);
            }
            item->setPreItem(preItem);
            preItem = item;
        }
    }
}

void ProjTreeThread::SlotCancelProgress()
{
    _bStop = true;
}

