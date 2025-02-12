#include "MainWindow.h"
#include <QMenu>
#include <QAction>
#include "CreateProjWizard.h"
#include "ProjTree.h"
#include <QFileDialog>
#include "PicShow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
    , _projTree(new ProjTree())
    , _picShow(new PicShow())
{
    ui->setupUi(this);
    // 文件菜单
    QMenu* menuFile = menuBar()->addMenu("文件(&F)");
    //新建项目
    QAction* actCreateProj = new QAction(QIcon(":/MainWindow/icons/heart (1).png"), "创建项目", this);
    actCreateProj->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    menuFile->addAction(actCreateProj);
    // 打开项目
    QAction* actOpenProj = new QAction(QIcon(""), "打开项目", this);
    actOpenProj->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    menuFile->addAction(actOpenProj);

    // 创建设置菜单
    QMenu* menuSettings = menuBar()->addMenu("设置(&S)");
    // 设置背景音乐
    QAction* actSetMusic = new QAction(QIcon(""), "设置背景音乐", this);
    actSetMusic->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_M));
    menuSettings->addAction(actSetMusic);

    // 连接信号和槽
    connect(actCreateProj, &QAction::triggered, this, &MainWindow::SlotCreateProj);

    connect(actOpenProj, &QAction::triggered, this, &MainWindow::SlotOpenProj);
    ProjTreeWidget* treeWidget = dynamic_cast<ProjTreeWidget*>(dynamic_cast<ProjTree*>(_projTree)->GetTreeWidget());
    connect(this, &MainWindow::SigOpenProj, treeWidget, &ProjTreeWidget::SlotOpenProj);

    // 添加widgets
    ui->proLayout->addWidget(_projTree);
    ui->picLayout->addWidget(_picShow);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _projTree;
}

void MainWindow::SlotOpenProj(bool checked)
{
    QFileDialog fileDlg;
    fileDlg.setFileMode(QFileDialog::Directory);
    fileDlg.setWindowTitle("选择打开的文件夹");
    fileDlg.setDirectory(QDir::currentPath());
    fileDlg.setViewMode(QFileDialog::Detail);
    
    QStringList fileNames;
    if (fileDlg.exec()) {
        fileNames = fileDlg.selectedFiles();
    }
    if (fileNames.isEmpty()) {
        qDebug() << "cannot get selected files!";
        return;
    }
    QString importPath = fileNames[0];
    emit SigOpenProj(importPath);
}

void MainWindow::SlotCreateProj(bool checked)
{
    qDebug() << "slot create pro triggered";
    CreateProjWizard wizard(this);
    wizard.setWindowTitle("创建项目");
    wizard.page(0)->setTitle("设置项目配置");
    
    // TODO: 连接信号和槽
    connect(&wizard, &CreateProjWizard::SigProjSettings, static_cast<ProjTree*>(_projTree), &ProjTree::AddProjToTree);

    wizard.show();
    wizard.exec();

    // TODO: 断开信号
    disconnect();
}

