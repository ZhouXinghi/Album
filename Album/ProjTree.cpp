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

QTreeWidget* ProjTree::GetTreeWidget() const
{
    return ui->treeWidget;
}

void ProjTree::AddProjToTree(QString name, QString path)
{
    ui->treeWidget->AddProjToTree(name, path);
}
