#pragma once
#include <QTreeWidget>
#include <QProgressDialog>
#include "ProjTreeThread.h"

class ProjTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ProjTreeWidget(QWidget* parent = nullptr);

    void AddProjToTree(const QString& name, const QString& path);

private:
    QAction* _actImport;
    QAction* _actSetStart;
    QAction* _actCloseProj;
    QAction* _actShowSlide;

    QTreeWidgetItem* _rightBtnItem;
    QProgressDialog* _progDlg;

    std::shared_ptr<ProjTreeThread> _projTreeThread;

    QTreeWidgetItem* _activeItem;

private slots:
    void SlotItemPressed(QTreeWidgetItem* item, int column);
    void SlotImport();
    void SlotUpdataProgress(int count);
    void SlotFinishProgress();
    void SlotCancelProgress();
    void SlotSetActive();
    void SlotCloseProj();
signals:
    void SigCancelProgress();
};

