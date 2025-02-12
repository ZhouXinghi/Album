#include "ProjTreeWidget.h"
#include <QDir>
#include "ProjTreeItem.h"
#include "constants.h"
#include <QHeaderView>
#include <QGuiApplication>
#include <QMenu>
#include <QFileDialog>
#include "RmProjDlg.h"

ProjTreeWidget::ProjTreeWidget(QWidget* parent)
    : QTreeWidget(parent) 
    , _actImport(new QAction(QIcon(""), "导入文件", this))
    , _actSetStart(new QAction(QIcon(""), "设置活动项目", this))
    , _actCloseProj(new QAction(QIcon(""), "关闭项目", this))
    , _actShowSlide(new QAction(QIcon(""), "轮播图播放", this))
    , _rightBtnItem(nullptr)
    , _activeItem(nullptr)
    , _progDlg(nullptr)
    , _projTreeThread(nullptr)
    , _openProjThread(nullptr)
{
    header()->hide();
    connect(this, &ProjTreeWidget::itemPressed, this, &ProjTreeWidget::SlotItemPressed);

    connect(_actImport, &QAction::triggered, this, &ProjTreeWidget::SlotImport);
    connect(_actSetStart, &QAction::triggered, this, &ProjTreeWidget::SlotSetActive);
    connect(_actCloseProj, &QAction::triggered, this, &ProjTreeWidget::SlotCloseProj);
}

QTreeWidgetItem* ProjTreeWidget::AddProjToTree(const QString& name, const QString& path)
{
    // 创建项目路径
    QDir dir(path);
    QString projPath = dir.absoluteFilePath(name);
    
    QDir projDir(projPath);
    if (!projDir.exists()) {
        projDir.mkpath(projPath);
    }

    auto* item = new ProjTreeItem(this, name, projPath, TreeItemProj);
    item->setData(0, Qt::DisplayRole, name);
    item->setData(0, Qt::DecorationRole, QIcon(""));
    item->setData(0, Qt::ToolTipRole, projPath);
    addTopLevelItem(item);
    return item;
}

void ProjTreeWidget::SlotImport()
{
    if (_rightBtnItem == nullptr) {
        qDebug() << "_rightBtnItem == nullptr !";
        return;
    }
    QFileDialog fileDlg;
    fileDlg.setFileMode(QFileDialog::Directory);
    fileDlg.setWindowTitle("选择要导入的文件夹");

    QString path = dynamic_cast<ProjTreeItem*>(_rightBtnItem)->getPath();
    fileDlg.setDirectory(path);
    fileDlg.setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (fileDlg.exec()) {
        fileNames = fileDlg.selectedFiles();
    }
    if (fileNames.isEmpty()) {
        qDebug() << "cannot get selected files!";
        return;
    }
    QString importPath = fileNames[0];
    _progDlg = new QProgressDialog(this);

    int fileCount = 0;
    _projTreeThread = std::make_shared<ProjTreeThread>(std::ref(importPath), std::ref(path), _rightBtnItem, fileCount, this, _rightBtnItem, nullptr);
    connect(_projTreeThread.get(), &ProjTreeThread::SigUpdateProgress, this, &ProjTreeWidget::SlotUpdataProgress);
    connect(_projTreeThread.get(), &ProjTreeThread::SigFinishProgress, this, &ProjTreeWidget::SlotFinishProgress);
    connect(_progDlg, &QProgressDialog::canceled, this, &ProjTreeWidget::SlotCancelProgress);
    connect(this, &ProjTreeWidget::SigCancelProgress, _projTreeThread.get(), &ProjTreeThread::SlotCancelProgress);
    _projTreeThread->start();

    _progDlg->setWindowTitle("Loading, please wait...");
    _progDlg->setFixedWidth(PROGRESS_WIDTH);
    _progDlg->setRange(0, PROGRESS_WIDTH);
    _progDlg->exec();
}

void ProjTreeWidget::SlotUpdataProgress(int count)
{
    if (_progDlg == nullptr) {
        return;
    }
    _progDlg->setValue(count % PROGRESS_MAX);
}

void ProjTreeWidget::SlotFinishProgress()
{
    _progDlg->setValue(PROGRESS_MAX);
    _progDlg->deleteLater();
}

void ProjTreeWidget::SlotCancelProgress()
{
    emit SigCancelProgress();
    delete _progDlg;
    _progDlg = nullptr;
}

void ProjTreeWidget::SlotSetActive()
{
    if (_rightBtnItem == nullptr) {
        return;
    }
    QFont font;
    font.setBold(false);
    if (_activeItem != nullptr) {
        _activeItem->setFont(0, font);
    }
    _activeItem = _rightBtnItem;
    font.setBold(true);
    _activeItem->setFont(0, font);
}

void ProjTreeWidget::SlotCloseProj()
{
    if (_rightBtnItem == nullptr) {
        return;
    }
    RmProjDlg rmProjDlg;
    int res = rmProjDlg.exec();
    if (res != QDialog::Accepted) {
        return;
    }
    if (rmProjDlg.IsDeleteLocalFile()) {
        QDir(dynamic_cast<ProjTreeItem*>(_rightBtnItem)->getPath()).removeRecursively();
    }
    if (_rightBtnItem == _activeItem) {
        _activeItem = nullptr;
    }

    delete takeTopLevelItem(indexOfTopLevelItem(_rightBtnItem));
    _rightBtnItem = nullptr;
}

void ProjTreeWidget::SlotOpenProj(const QString& path)
{
    // TODO:判断是否已经打开，若已经打开则不再次打开
    if (IsAlreadyOpen(path)) {
        return;
    }
    QDir dir(path);
    QString name = dir.dirName();
    dir.cdUp();
    QString parentPath = dir.absolutePath();
    QTreeWidgetItem* rootItem = AddProjToTree(name, parentPath);

    //QDir projDir(path);

    int fileCount = 0;
    _openProjThread = std::make_shared<OpenProjThread>(std::ref(path), fileCount, this, rootItem,  nullptr);
    _openProjThread->start();

}

bool ProjTreeWidget::IsAlreadyOpen(const QString& path) const
{
    return false;
}

void ProjTreeWidget::SlotItemPressed(QTreeWidgetItem* item, int column)
{
    if (QGuiApplication::mouseButtons() == Qt::RightButton) {
        _rightBtnItem = item;
        QMenu menu(this);
        if (item->type() == TreeItemProj) {
            menu.addAction(_actImport);
            menu.addAction(_actSetStart);
            menu.addAction(_actCloseProj);
            menu.addAction(_actShowSlide);
            menu.exec(QCursor::pos());
        }
    }
}
