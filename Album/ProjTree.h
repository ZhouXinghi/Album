#pragma once
#include <QDialog>
#include "ui_ProjTree.h"
#include <QTreeWidget>


class ProjTree : public QDialog
{
public:
    explicit ProjTree(QWidget* parent = nullptr);
    virtual ~ProjTree();
    QTreeWidget* GetTreeWidget() const;
private:
    Ui::ProjTree* ui;
public slots:
    void AddProjToTree(QString name, QString path);
};

