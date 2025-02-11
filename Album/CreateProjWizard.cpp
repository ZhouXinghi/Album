#include "CreateProjWizard.h"

CreateProjWizard::CreateProjWizard(QWidget* parent)
    : QWizard(parent)
    , ui(new Ui::CreateProjWizard())
{
    ui->setupUi(this);
}

CreateProjWizard::~CreateProjWizard()
{
    delete ui;
}

void CreateProjWizard::done(int result)
{
    if (result == QDialog::Rejected) {
        QWizard::done(result);
        return;
    }

    QString name, path;
    ui->projSetPage->getProjSettings(&name, &path);
    emit SigProjSettings(name, path);
    QWizard::done(result);
}
