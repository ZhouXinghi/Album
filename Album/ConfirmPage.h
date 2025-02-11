#pragma once

#include <QWizardPage>
#include "ui_ConfirmPage.h"

//QT_BEGIN_NAMESPACE
//namespace Ui { class Form; };
//QT_END_NAMESPACE

class ConfirmPage  : public QWizardPage
{
    Q_OBJECT

public:
    ConfirmPage(QWidget *parent = nullptr);
    ~ConfirmPage();
private:
    Ui::ConfirmPage* ui;
};
