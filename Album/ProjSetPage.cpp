#include "ProjSetPage.h"
#include <QDir>
#include <QFileDialog>

ProjSetPage::ProjSetPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ProjSetPage())
{
    ui->setupUi(this);
    registerField("project Path", ui->lineEdit_2);
    registerField("projName", ui->lineEdit);
    connect(ui->lineEdit, &QLineEdit::textEdited, this, &ProjSetPage::completeChanged);
    connect(ui->lineEdit_2, &QLineEdit::textEdited, this, &ProjSetPage::completeChanged);
    QString curPath = QDir::currentPath();
    ui->lineEdit_2->setText(curPath);
    ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().size());
    ui->lineEdit_2->setClearButtonEnabled(true);
    ui->lineEdit->setClearButtonEnabled(true);
}

ProjSetPage::~ProjSetPage()
{
    delete ui;
}

bool ProjSetPage::isComplete() const
{
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()) {
        return false;
    }
    QDir dir(ui->lineEdit_2->text());
    if (!dir.exists()) {
        ui->tips->setText("project path does not exist!");
        return false;
    }

    if (QDir(dir.absoluteFilePath(ui->lineEdit->text())).exists()) {
        ui->tips->setText("Project has exists, change path or name!");
        return false;
    }
    ui->tips->setText("");
    return QWizardPage::isComplete();
}

void ProjSetPage::getProjSettings(QString* name, QString* path) const
{
    *name = ui->lineEdit->text();
    *path = ui->lineEdit_2->text();
}

void ProjSetPage::on_pushButton_clicked()
{
    QFileDialog fileDlg{};
    fileDlg.setFileMode(QFileDialog::Directory);
    fileDlg.setWindowTitle("选择导入的文件夹");
    fileDlg.setDirectory(QDir::currentPath());
    fileDlg.setViewMode(QFileDialog::Detail);

    QStringList fileNames{};
    if (fileDlg.exec()) {
        fileNames = fileDlg.selectedFiles();
    }
    if (fileNames.isEmpty()) {
        return;
    }
    QString importPath = fileNames[0];
    ui->lineEdit_2->setText(importPath);
}
