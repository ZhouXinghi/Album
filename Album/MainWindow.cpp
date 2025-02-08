#include "MainWindow.h"
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotCreateProj(bool checked) const
{
    qDebug() << "slot create pro triggered";
}

