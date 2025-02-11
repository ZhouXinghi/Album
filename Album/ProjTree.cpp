#include "ProjTree.h"

ProjTree::ProjTree(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ProjTree())
{
    ui->setupUi(this);
    setMinimumWidth(378);
    setMaximumWidth(378);
}

ProjTree::~ProjTree()
{
    delete ui;
}

void ProjTree::AddProjToTree(QString name, QString path)
{
    ui->treeWidget->AddProjToTree(name, path);
}
