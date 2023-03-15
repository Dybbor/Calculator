#include "MainApplication.h"

#include <QFont>
#include <cmath>
#include <iostream>

CalculatorGUI::CalculatorGUI(QWidget* parent) : QWidget(parent) {
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
        digitButtons[i] = CreateButton(QString::number(i), SLOT(CasualButtonClicked()));
    }

    setStyleSheet("font-family: Roboto; \
        font-style: normal; \
        font-size: 25px;\
        font-weight: 500; \
        background-color: rgb(240, 240, 240);");

    connect(mathPiBtn, &MyButton::clicked, this, &CalculatorGUI::CasualButtonClicked);
    connect(pointOperatorBtn, &MyButton::clicked, this, &CalculatorGUI::CasualButtonClicked);
    connect(plusOperatorBtn, &MyButton::clicked, this, &CalculatorGUI::OpButtonClicked);
    connect(minusOperatorBtn, &MyButton::clicked, this, &CalculatorGUI::OpButtonClicked);
    connect(multiplyOperatorBtn, &MyButton::clicked, this, &CalculatorGUI::OpButtonClicked);
    connect(divideOperatorBtn, &MyButton::clicked, this, &CalculatorGUI::OpButtonClicked);
    connect(sinOperatorBtn, &MyButton::clicked, this, &CalculatorGUI::TrigonometricButtonClicked);
    connect(cosOperatorBtn, &MyButton::clicked, this, &CalculatorGUI::TrigonometricButtonClicked);
    connect(tgOperatorBtn, &MyButton::clicked, this, &CalculatorGUI::TrigonometricButtonClicked);
    connect(openedBracketBtn, &MyButton::clicked, this, &CalculatorGUI::CasualButtonClicked);
    connect(closedBracketBtn, &MyButton::clicked, this, &CalculatorGUI::CasualButtonClicked);
    connect(deleteLastBtn, &MyButton::clicked, this, &CalculatorGUI::DeleteLastButtonClicked);
    connect(clearAllBtn, &MyButton::clicked, this, &CalculatorGUI::ClearAllButtonClicked);
    connect(equalOperatorBtn, &MyButton::clicked, this, &CalculatorGUI::EqualButtonClicked);

    expressionLineEdit->setAlignment(Qt::AlignRight);
    expressionLineEdit->setReadOnly(true);
    expressionLineEdit->setText("0");
    expressionLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    expressionLineEdit->setStyleSheet("padding-right: 10px");

    resultExpressionLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    resultExpressionLabel->setText("0");
    resultExpressionLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    resultExpressionLabel->setStyleSheet("padding-right: 10px");

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

    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

std::unique_ptr<MyButton> CalculatorGUI::CreateButton(const QString& nameButton, const char* nameSlot) {
    std::unique_ptr<MyButton> newButton = std::make_unique<MyButton>(nameButton, this);
    connect(newButton.get(), SIGNAL(clicked()), this, nameSlot);
    return newButton;
}

void CalculatorGUI::CasualButtonClicked() {
    MyButton* Sender = static_cast<MyButton*>(sender());
    if (needToCleanLabel) {
        needToCleanLabel = false;
        resultExpressionLabel->setText("");
        expressionLineEdit->setText(Sender->text());
    } else {
        QString text = expressionLineEdit->text() == "0" ? "" : expressionLineEdit->text();
        expressionLineEdit->setText(text + Sender->text());
    }
}

void CalculatorGUI::TrigonometricButtonClicked() {
    MyButton* Sender = static_cast<MyButton*>(sender());
    if (needToCleanLabel) {
        needToCleanLabel = false;
        expressionLineEdit->setText(Sender->text() + "(" + resultExpressionLabel->text());
        resultExpressionLabel->setText("");
    } else {
        QString text = expressionLineEdit->text() == "0" ? Sender->text() : expressionLineEdit->text() + Sender->text();
        expressionLineEdit->setText(text + "(");
    }
}

void CalculatorGUI::OpButtonClicked() {
    MyButton* Sender = static_cast<MyButton*>(sender());
    if (needToCleanLabel) {
        needToCleanLabel = false;
        expressionLineEdit->setText(resultExpressionLabel->text() + Sender->text());
        resultExpressionLabel->setText("");
    } else {
        QString text = expressionLineEdit->text() == "0" ? "" : expressionLineEdit->text();
        expressionLineEdit->setText(text + Sender->text());
    }
}

void CalculatorGUI::DeleteLastButtonClicked() {
    QString text = expressionLineEdit->text();
    if (text.size() > 1) {
        text = text.first(text.size() - 1);
    } else if (text.size() == 1 && text != "0") {
        text = "0";
    }
    expressionLineEdit->setText(text);
}

void CalculatorGUI::ClearAllButtonClicked() {
    expressionLineEdit->setText("0");
    resultExpressionLabel->setText("");
}

void CalculatorGUI::EqualButtonClicked() {
    needToCleanLabel = true;
    auto expression = expressionLineEdit->text().replace(QChar(0x03C0), "3.1415926535").toStdString();
    Solver solver(expression);
    try {
        auto res = std::round(solver.Calculate() * 1000000000) / 1000000000;
        resultExpressionLabel->setText(QString::number(res, 'g', 10));
    } catch (std::invalid_argument ex) {
        resultExpressionLabel->setText(ex.what());
    } catch (std::exception ex) {
        std::cout << "What is it : " << ex.what() << std::endl;
    }
}

CalculatorGUI::~CalculatorGUI() {}