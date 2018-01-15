#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "memory.h"
#include <QMainWindow>
#include "memorylabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Memory memory;

public slots:
    void calculate();
    void on_mLabel_click(MemoryLabel *id);
private slots:
    void on_calcPushButton_clicked();

    void on_clearButton_clicked();

    void loadPrev();
    void loadNext();

    void on_calcLineEdit_textEdited(const QString &arg1);

private:

    Ui::MainWindow *ui;
    QString removeSpaces(QString input);
    void clearLayout(QLayout *layout);
    void setShortcuts();
    QString addSpaces(QString input);
    void addToMemoryLayout(QString input, QString ans);
};

#endif // MAINWINDOW_H
