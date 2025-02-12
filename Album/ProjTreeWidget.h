#pragma once
#include <QTreeWidget>
#include <QProgressDialog>
#include "ProjTreeThread.h"
#include "OpenProjThread.h"

class ProjTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ProjTreeWidget(QWidget* parent = nullptr);

    QTreeWidgetItem* AddProjToTree(const QString& name, const QString& path);

private:
    QAction* _actImport;
    QAction* _actSetStart;
    QAction* _actCloseProj;
    QAction* _actShowSlide;

    QTreeWidgetItem* _rightBtnItem;
    QProgressDialog* _progDlg;

    std::shared_ptr<ProjTreeThread> _projTreeThread;
    std::shared_ptr<OpenProjThread> _openProjThread;

    QTreeWidgetItem* _activeItem;

    bool IsAlreadyOpen(const QString& path) const;

private slots:
    void SlotItemPressed(QTreeWidgetItem* item, int column);
    void SlotImport();
    void SlotUpdataProgress(int count);
    void SlotFinishProgress();
    void SlotCancelProgress();
    void SlotSetActive();
    void SlotCloseProj();
public slots:
    void SlotOpenProj(const QString& path);
signals:
    void SigCancelProgress();
};

