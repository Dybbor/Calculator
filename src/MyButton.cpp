#include "MyButton.h"

MyButton::MyButton(const QString& nameButton, QWidget* parent): QPushButton(parent)
{
    setText(nameButton);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}
