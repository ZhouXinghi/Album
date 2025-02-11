#pragma once
#include <QThread>
#include <QTreeWidget>

class ProjTreeThread : public QThread
{
    Q_OBJECT
public:
    ProjTreeThread(const QString& srcPath, const QString& distPath, QTreeWidgetItem* parentItem, int fileCount,
        QTreeWidget* widget, QTreeWidgetItem* rootItem, QObject* parent = nullptr);
    virtual ~ProjTreeThread();
protected:
    virtual void run() override;
private:
    void CreateProjTree(const QString& srcPath, const QString& distPath, QTreeWidgetItem* parentItem, int* fileCount, 
        QTreeWidget* widget, QTreeWidgetItem* rootItem, QTreeWidgetItem* preItem);

private:
    QString _srcPath;
    QString _distPath;
    int _fileCount;
    QTreeWidgetItem* _parentItem;
    QTreeWidget* _widget;
    QTreeWidgetItem* _rootItem;
    bool _bStop;

public slots:
    void SlotCancelProgress();

signals:
    void SigUpdateProgress(int fileCount);
    void SigFinishProgress(int fileCount);

};

