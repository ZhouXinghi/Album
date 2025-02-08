#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile qssFile(":/MainWindow/style/style.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        qDebug("Open qss file sucess!");
        QString styleString = QLatin1String(qssFile.readAll());
        app.setStyleSheet(styleString);
        qssFile.close();
    }
    else {
        qDebug("Open qss file failed!");
        return 0;
    }
    MainWindow w;
    w.setWindowTitle("爱心相册");
    //w.showMaximized();
    w.show();
    return app.exec();
}
