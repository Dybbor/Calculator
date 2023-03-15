#include "MyButton.h"

MyButton::MyButton(const QString& nameButton, QWidget* parent) : QPushButton(parent) {
    setText(nameButton);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setStyleSheet("QPushButton{\
	    background-color: rgb(255, 255, 255); \
	    border-color: rgb(0, 0, 0);\
        border-width: 1px;        \
        border-style: dashed;\
        } \
        QPushButton:hover {\
        background:  qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, \
        stop:0 rgba(0, 0, 0,20), stop:1 rgba(255, 255, 255, 255));\
        }");
}
