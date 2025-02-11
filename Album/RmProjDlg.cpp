#include "RmProjDlg.h"

RmProjDlg::RmProjDlg(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::RmProjDlg())
{
    ui->setupUi(this);
    connect(ui->okButton, &QPushButton::clicked, this, &RmProjDlg::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &RmProjDlg::reject);
    //connect(ui->okButton, &QPushButton::clicked, this, &RmProjDlg::on_okButton_clicked);
}

RmProjDlg::~RmProjDlg()
{
    delete ui;
}

bool RmProjDlg::IsDeleteLocalFile() const
{
    return ui->checkBox->isChecked();
}

//void RmProjDlg::on_okButton_clicked()
//{
//    accept();
//}