#include "ConfirmPage.h"

ConfirmPage::ConfirmPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ConfirmPage())
{
    ui->setupUi(this);
}

ConfirmPage::~ConfirmPage()
{
    delete ui;
}
