#include "MainApplication.h"
#include <QFont>
#include <iostream>

CalculatorGUI::CalculatorGUI(QWidget* parent)
    : QWidget(parent)
{
    setGeometry(0, 0, 540, 700);
    mainLayout = new QGridLayout(this);
    expressionLineEdit = new QLineEdit(this);
    resultExpressionLabel = new QLabel(this);
    mathPiBtn = new MyButton(QChar(0x03C0));
    pointOperatorBtn = new MyButton(".");
    equalOperatorBtn = new MyButton("=");
    plusOperatorBtn = new MyButton("+");
    minusOperatorBtn = new MyButton("-");
    multiplyOperatorBtn = new MyButton("*");
    divideOperatorBtn = new MyButton("/");
    sinOperatorBtn = new MyButton("sin");
    cosOperatorBtn = new MyButton("cos");
    tgOperatorBtn = new MyButton("tg");
    clearAllBtn = new MyButton("AC");
    deleteLastBtn = new MyButton("x");
    openedBracketBtn = new MyButton("(");
    closedBracketBtn = new MyButton(")");

    for (size_t i = 0; i < 10; ++i) {
        digitButtons[i] = std::move(CreateButton(QString::number(i), SLOT(DigitClicked())));
    }

    expressionLineEdit->setAlignment(Qt::AlignRight);
    expressionLineEdit->setReadOnly(true);
    expressionLineEdit->setText("test");
    expressionLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    resultExpressionLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    resultExpressionLabel->setText("test label");
    resultExpressionLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    mainLayout->addWidget(expressionLineEdit, 0, 0, 1, 4);
    mainLayout->addWidget(resultExpressionLabel, 1, 0, 1, 4);
    mainLayout->addWidget(clearAllBtn, 2, 0);
    mainLayout->addWidget(deleteLastBtn, 2, 1);
    mainLayout->addWidget(openedBracketBtn, 2, 2);
    mainLayout->addWidget(closedBracketBtn, 2, 3);
    mainLayout->addWidget(sinOperatorBtn, 3, 0);
    mainLayout->addWidget(cosOperatorBtn, 3, 1);
    mainLayout->addWidget(tgOperatorBtn, 3, 2);
    mainLayout->addWidget(divideOperatorBtn, 3, 3);
    for (size_t i = 1; i < 10; ++i) {
        int row = ((9 - i) / 3) + 4;
        int column = ((i - 1) % 3);
        mainLayout->addWidget(digitButtons[i].get(), row, column);
    }
    mainLayout->addWidget(digitButtons[0].get(), 7, 1);
    mainLayout->addWidget(multiplyOperatorBtn, 4, 3);
    mainLayout->addWidget(minusOperatorBtn, 5, 3);
    mainLayout->addWidget(plusOperatorBtn, 6, 3);
    mainLayout->addWidget(equalOperatorBtn, 7, 3);
    mainLayout->addWidget(mathPiBtn, 7, 0);
    mainLayout->addWidget(pointOperatorBtn, 7, 2);
    
    QFont font("Roboto");
    font.setPixelSize(20);
    setFont(font);

    setLayout(mainLayout);
}

CalculatorGUI::~CalculatorGUI()
{}

std::unique_ptr<MyButton> CalculatorGUI::CreateButton(const QString& nameButton, const char* nameSlot)
{
    std::unique_ptr<MyButton> newButton = std::make_unique<MyButton>(nameButton, this);
    connect(newButton.get(), SIGNAL(clicked()), this, nameSlot);
    return newButton;
}

void CalculatorGUI::DigitClicked() {
    std::cout << "Hello !" << std::endl;
}
