#include "PicButton.h"
#include <QPixmap>
#include <QEvent>


PicButton::PicButton(QWidget* parent)
    : QPushButton(parent)

{
}

void PicButton::Init(const QString& normal, const QString& hover, const QString& pressed)
{
    _normal = normal;
    _hover = hover;
    _pressed = pressed;
    SetIcon(Normal);
}

bool PicButton::event(QEvent* e)
{
    switch (e->type()) {
    case QEvent::Enter:
        SetIcon(Hover);
        break;
    case QEvent::Leave:
        SetIcon(Normal);
        break;
    case QEvent::MouseButtonPress:
        SetIcon(Pressed);
        break;
    case QEvent::MouseButtonRelease:
        SetIcon(Hover);
        break;
    default:
        break;
    }
    return QPushButton::event(e);
}

void PicButton::SetIcon(Status status)
{
    QPixmap tmpPixmap;
    if (status == Normal) {
        tmpPixmap.load(_normal);
    }
    else if (status == Hover) {
        tmpPixmap.load(_hover);
    }
    else if (status == Pressed) {
        tmpPixmap.load(_pressed);
    }
    //QPixmap scaledPixmap = tmpPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    resize(tmpPixmap.size());
    setIcon(tmpPixmap);
    setIconSize(size());
    //update();
    //repaint();
}
