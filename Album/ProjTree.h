#pragma once
#include <QDialog>
#include "ui_ProjTree.h"


class ProjTree : public QDialog
{
public:
    explicit ProjTree(QWidget* parent = nullptr);
    virtual ~ProjTree();
private:
    Ui::ProjTree* ui;
public slots:
    void AddProjToTree(QString name, QString path);
};

