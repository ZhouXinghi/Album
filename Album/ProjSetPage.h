#pragma once

#include <QWizardPage>
#include "ui_ProjSetPage.h"


class ProjSetPage  : public QWizardPage
{
    Q_OBJECT

public:
    ProjSetPage(QWidget *parent = nullptr);
    ~ProjSetPage();
private:
    Ui::ProjSetPage* ui;

protected:
    virtual bool isComplete() const override;

private slots:
    void on_pushButton_clicked();

public:
    void getProjSettings(QString* name, QString* path) const;
};
