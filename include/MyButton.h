#pragma once
#include <QPushButton>

class MyButton : public QPushButton {
    Q_OBJECT
public:
    explicit MyButton(const QString& nameButton, QWidget* parent = nullptr);

};