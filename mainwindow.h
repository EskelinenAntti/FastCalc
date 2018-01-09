#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void calculate();
private slots:
    void on_calcPushButton_clicked();

    void on_clearButton_clicked();
private:
    struct Operation{
        QList<double> numbers;
        QStringList operators;
    };

    Ui::MainWindow *ui;
    QString removeSpaces(QString input);
    QList<double> findNumbers(QString input);
    QStringList findOperators(QString input);
    Operation calcProdDiv(QList<double> numbers, QStringList operators);
    Operation calcSumSub(QList<double> numbers, QStringList operators);
    void clearLayout(QLayout *layout);
    void setShortcuts();
    QString addSpaces(QString input);
    void addToMemoryLayout(QString input);
    QString findParentheses(QString input);
    double calcArithmetics(QString input);
    QStringList removeEmpty(QStringList input);
};

#endif // MAINWINDOW_H
