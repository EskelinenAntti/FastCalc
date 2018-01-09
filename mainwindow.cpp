#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setShortcuts();
    this->setMinimumSize(130, 130);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setShortcuts(){
    // Set shortcuts for the buttons in the UI.

    QShortcut *shortcut1 = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    QShortcut *shortcut2 = new QShortcut(QKeySequence(Qt::Key_Return),this);
    connect(shortcut1, SIGNAL(activated()), this, SLOT(on_calcPushButton_clicked()));
    connect(shortcut2, SIGNAL(activated()), this, SLOT(on_calcPushButton_clicked()));
    ui->clearButton->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
}

void MainWindow::on_calcPushButton_clicked()
{
    // "="-button or enter was pressed.

    // Check that user has written some input.
    if (ui->calcLineEdit->text() != ""){
        MainWindow::calculate();
    }
}

void MainWindow::calculate()
{
    // Comment.
    QString input = ui->calcLineEdit->text();

    input = MainWindow::removeSpaces(input);

    input = MainWindow::findParentheses(input);


    double answer = MainWindow::calcArithmetics(input);

    ui->calcLineEdit->setText(QString::number(answer));

    input = input + QString("=") + QString::number(answer);

    MainWindow::addToMemoryLayout(input);


    ui->calcLineEdit->setText(QString::number(answer));
    ui->calcLineEdit->selectAll();
}

double MainWindow::calcArithmetics(QString input){

    QList<double> numbers = MainWindow::findNumbers(input);
    QStringList operators = MainWindow::findOperators(input);

    Operation prodDivStruct = MainWindow::calcProdDiv(numbers, operators);
    numbers = prodDivStruct.numbers;
    operators = prodDivStruct.operators;

    Operation subSumStruct = MainWindow::calcSumSub(numbers, operators);
    numbers = subSumStruct.numbers;
    operators = subSumStruct.operators;
    return numbers[0];
}

// 30.12.2017

QString MainWindow::findParentheses(QString input)
{
    QList<int> parenthesesIndexes;
    for (int i=0; i<input.size(); i++){
        if (input[i] == "("){
            parenthesesIndexes.append(i);
        } else if(input[i] == ")"){
            QString subString;
            subString = input.mid(parenthesesIndexes.last() + 1, i-parenthesesIndexes.last()-1);

            double answer = MainWindow::calcArithmetics(subString);
            input.replace(parenthesesIndexes.last(), i - parenthesesIndexes.last()+1, QString::number(answer));
            i = parenthesesIndexes.last();
            parenthesesIndexes.removeLast();

        }
    }
    /*if (parenthesesIndexes.size() != 0){
        QString subString;
        subString = input.mid(parenthesesIndexes[0] + 1, parenthesesIndexes[1] - parenthesesIndexes[0] - 1);

        double answer = MainWindow::calcArithmetics(subString);
        input.replace(parenthesesIndexes[0], parenthesesIndexes[1] - parenthesesIndexes[0]+1, QString::number(answer));
        return input;
    } else{
        return input;
    }*/
    return input;
}

// 30.12.2017


void MainWindow::addToMemoryLayout(QString input)
{
    input = MainWindow::addSpaces(input);

    QLabel *mInput = new QLabel(input);
    mInput->setFont(QFont("Arial", 12));

    QWidget *horizontalLine = new QWidget();
    horizontalLine -> setFixedHeight(2);
    horizontalLine -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    horizontalLine -> setStyleSheet(QString("background-color: #c0c0c0;"));
    ui->memoryLayout->insertWidget(0, horizontalLine);
    ui->memoryLayout->insertWidget(0, mInput);

}

QString MainWindow::addSpaces(QString input){
    // Add spaces to the QString input.
    QString space(" ");
    for (int i = 0; i<input.size(); i++){
        QString m(input[i]);
        if (m == "+" || m == "-" || m == "*"|| m == "/"|| m == "="){
            input.insert(i+1, space);
            input.insert(i, space);
            i += 1;
        }
    }
    return input;
}

MainWindow::Operation MainWindow::calcProdDiv(QList<double> numbers, QStringList operators){
    // Calculate products and divisions. Remove used operators from the list and
    // update the results to numbers-list.
    for (int i = 0; i<operators.size(); i++){

       if(operators[i] == "*"){
            double product = numbers[i] * numbers[i+1];
            numbers[i] = product;
            numbers.removeAt(i+1);
            operators.removeAt(i);
            i -= 1;
        } else if (operators[i] == "/"){
            double product = numbers[i] / numbers[i+1];
            numbers[i] = product;
            numbers.removeAt(i+1);
            operators.removeAt(i);
            i -= 1; }
    }

    MainWindow::Operation results;
    results.numbers = numbers;
    results.operators = operators;

    return results;
}

MainWindow::Operation MainWindow::calcSumSub(QList<double> numbers, QStringList operators){
    // Calculate sums and substractions.
    for (int i = 0; i < operators.size(); i++){
        if (operators[i] == "+"){
            double product = numbers[i] + numbers[i+1];
            numbers[i] = product;
            numbers.removeAt(i+1);
            operators.removeAt(i);
            i -= 1;
        } else if (operators[i] == "-"){
            double product = numbers[i] - numbers[i+1];
            numbers[i] = product;
            numbers.removeAt(i+1);
            operators.removeAt(i);
            i -= 1; }
    }
    MainWindow::Operation results;
    results.numbers = numbers;
    results.operators = operators;

    return results;
}

QString MainWindow::removeSpaces(QString input)
{
    // Return given QString object without spaces.
    QString inputNS;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] != " ")
        {
            inputNS += input[i];
        }
    }
    return inputNS;
}

QList<double> MainWindow::findNumbers(QString input)
{
    // Returns list of numbers found in the input.
    QRegExp separator("(\\+|\\-|\\*|\/)");
    QStringList numbersAsStrings = input.split(separator);
    QList<double> numbers;
    for (int i = 0; i < numbersAsStrings.size(); i++){
        numbers.append(numbersAsStrings[i].toDouble());
    }

    return numbers;
}

QStringList MainWindow::findOperators(QString input)
{
    // Return list of operators found in the input.
    QStringList operators;
    for (int i = 0; i<input.size(); i++){
        if (input[i] == "+"){
            operators.append("+");
        } else if (input[i] == "-"){
            operators.append("-");
        } else if (input[i] == "*"){
            operators.append("*");
        } else if (input[i] == "/"){
            operators.append("/");
        }
    }
    return operators;
}

void MainWindow::on_clearButton_clicked()
{
    MainWindow::clearLayout(ui->memoryLayout);
}

void MainWindow::clearLayout(QLayout *layout){
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            MainWindow::clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

}


