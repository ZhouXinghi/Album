#pragma once
#include <QDialog>
#include "ui_PicShow.h"
#include <QPropertyAnimation>

class PicShow : public QDialog
{
    Q_OBJECT
public:
    PicShow(QWidget* parent = nullptr);
    ~PicShow();

protected:
    virtual bool event(QEvent* event) override;

private:
    Ui::PicShow* ui;
    QPropertyAnimation* _prevAni;
    QPropertyAnimation* _nextAni;
    bool _visible;

    void ShowBtns(bool isShow);
};

