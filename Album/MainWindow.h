#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;
    QWidget* _projTree;
    QWidget* _picShow;

private slots:
    void SlotCreateProj(bool checked);
    void SlotOpenProj(bool checked);

signals:
    void SigOpenProj(const QString& path);
};
