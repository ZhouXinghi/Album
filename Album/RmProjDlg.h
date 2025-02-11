#pragma once
#include <QDialog>
#include "ui_RmProDlg.h"

class RmProjDlg : public QDialog
{
public:
    explicit RmProjDlg(QWidget* parent = nullptr);
    ~RmProjDlg();
    
    bool IsDeleteLocalFile() const;
private:
    Ui::RmProjDlg* ui;
private slots:
    void on_okButton_clicked();
};

