#pragma once
#include <QPushButton>

class PicButton : public QPushButton
{
    enum Status {
        Normal, Hover, Pressed
    };

public:
    explicit PicButton(QWidget* parent = nullptr);
    void Init(const QString& normal, const QString& hover, const QString& pressed);

protected:
    bool event(QEvent* e) override;

private:
    void SetIcon(Status status);


    QString _normal;
    QString _hover;
    QString _pressed;

};

