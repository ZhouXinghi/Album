#include "MainWindow.h"
#include <QMenu>
#include <QAction>
#include "CreateProjWizard.h"
#include "ProjTree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
    , _projTree(new ProjTree())
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
    //CreateProjWizard* wizard = new CreateProjWizard(this);
    //wizard->show();

    // 添加ProjTree
    ui->proLayout->addWidget(_projTree);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _projTree;
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

