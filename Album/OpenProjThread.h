#pragma once
#include <QThread>
#include <QTreeWidget>

class OpenProjThread : public QThread
{
    Q_OBJECT
public:
    explicit OpenProjThread(const QString& srcPath, int fileCount, QTreeWidget* widget, QTreeWidgetItem* rootItem, QObject* parent = nullptr);

protected:
    virtual void run() override;
private:

    void OpenProj(const QString& srcPath, QTreeWidgetItem* parentItem, int* fileCount,
        QTreeWidget* widget, QTreeWidgetItem* rootItem, QTreeWidgetItem* preItem);

    QString _srcPath;
    int _fileCount;
    QTreeWidget* _widget;
    QTreeWidgetItem* _rootItem;
    bool _bStop;
signals:
    void SigUpdateProgress(int fileCount);
    void SigFinishProgress(int fileCount);
};

