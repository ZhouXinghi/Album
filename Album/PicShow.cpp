#include "PicShow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

PicShow::PicShow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::PicShow())
    , _prevAni(new QPropertyAnimation(this))
    , _nextAni(new QPropertyAnimation(this))
    , _visible(false)
{
    ui->setupUi(this);
    ui->prevBtn->Init(":/MainWindow/icon/previous.png", ":/MainWindow/icon/previous_hover.png", ":/MainWindow/icon/previous_press.png");
    ui->nextBtn->Init(":/MainWindow/icon/next.png", ":/MainWindow/icon/next_hover.png", ":/MainWindow/icon/next_press.png");
    QGraphicsOpacityEffect* prevEffect = new QGraphicsOpacityEffect(ui->prevBtn);
    prevEffect->setOpacity(0);
    ui->prevBtn->setGraphicsEffect(prevEffect);
    QGraphicsOpacityEffect* nextEffect = new QGraphicsOpacityEffect(ui->nextBtn);
    nextEffect->setOpacity(0);
    ui->nextBtn->setGraphicsEffect(nextEffect);
    
    _prevAni->setTargetObject(prevEffect);
    _prevAni->setPropertyName("opacity");
    _prevAni->setEasingCurve(QEasingCurve::Linear);
    _prevAni->setDuration(500);
    _nextAni->setTargetObject(nextEffect);
    _nextAni->setPropertyName("opacity");
    _nextAni->setEasingCurve(QEasingCurve::Linear);
    _nextAni->setDuration(500);

}

PicShow::~PicShow()
{
    delete ui;
}

bool PicShow::event(QEvent* e)
{
    switch (e->type()) {
    case QEvent::Enter:
        ShowBtns(true);
        break;
    case QEvent::Leave:
        ShowBtns(false);
        break;
    default:
        break;
    }
    return QDialog::event(e);
}

void PicShow::ShowBtns(bool isShow)
{
    // Òþ²Ø°´Å¥
    if (!isShow && _visible) { 
        _prevAni->stop();
        _prevAni->setStartValue(1);
        _prevAni->setEndValue(0);
        _prevAni->start();

        _nextAni->stop();
        _nextAni->setStartValue(1);
        _nextAni->setEndValue(0);
        _nextAni->start();

        _visible = false;
        return;
    }
    // ÏÔÊ¾°´Å¥
    if (isShow && !_visible) {
        _prevAni->stop();
        _prevAni->setStartValue(0);
        _prevAni->setEndValue(1);
        _prevAni->start();

        _nextAni->stop();
        _nextAni->setStartValue(0);
        _nextAni->setEndValue(1);
        _nextAni->start();

        _visible = true;
        return;
    }
}
