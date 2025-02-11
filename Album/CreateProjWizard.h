#pragma once
#include <QWizard>
#include "ui_CreateProjWizard.h"

//QT_BEGIN_NAMESPACE
//namespace Ui { class WizardClass; };
//QT_END_NAMESPACE

class CreateProjWizard : public QWizard
{
    Q_OBJECT;
public:
    CreateProjWizard(QWidget* parent = nullptr);
    ~CreateProjWizard();

private:
    Ui::CreateProjWizard* ui;

protected:
    virtual void done(int result) override;

signals:
    void SigProjSettings(QString name, QString path);
};

