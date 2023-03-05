#pragma once

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <array>
#include <memory>
#include "MyButton.h"


class CalculatorGUI : public QWidget
{
    Q_OBJECT
public:
    CalculatorGUI(QWidget *parent = nullptr);
    ~CalculatorGUI();
private slots:
    void DigitClicked();
private:
    QGridLayout* mainLayout;
    QLineEdit* expressionLineEdit;
    QLabel* resultExpressionLabel;
    std::array<std::unique_ptr<MyButton>,10> digitButtons;
    MyButton* pointOperatorBtn;
    MyButton* plusOperatorBtn;
    MyButton* minusOperatorBtn;
    MyButton* multiplyOperatorBtn;
    MyButton* divideOperatorBtn;
    MyButton* equalOperatorBtn;
    MyButton* mathPiBtn;
    MyButton* sinOperatorBtn;
    MyButton* cosOperatorBtn;
    MyButton* tgOperatorBtn;
    MyButton* deleteLastBtn;
    MyButton* clearAllBtn;
    MyButton* openedBracketBtn;
    MyButton* closedBracketBtn;


   std::unique_ptr<MyButton> CreateButton(const QString& nameButton, const char* nameSlot);
};
