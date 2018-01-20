#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "memorylabel.h"
#include "tinyexpr.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setShortcuts();
    this->setMinimumSize(220, 220);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setShortcuts(){
    /**
     * Set shortcuts for the program.
     */

    // Make a shortcut-object for both enter keys and connect them to the
    // "="-button.
    QShortcut *shortcut1 = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    QShortcut *shortcut2 = new QShortcut(QKeySequence(Qt::Key_Return),this);
    connect(shortcut1, SIGNAL(activated()), this,
            SLOT(on_calcPushButton_clicked()));
    connect(shortcut2, SIGNAL(activated()), this,
            SLOT(on_calcPushButton_clicked()));

    // Set shortcut for "clear"-button.
    ui->clearButton->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));

    // Set key for getting previous calculation from the memory.
    QShortcut *loadPrecSC = new QShortcut(QKeySequence(Qt::Key_Down), this);
    connect(loadPrecSC, SIGNAL(activated()), this, SLOT(loadPrev()));

    // Set key for getting the next answer from the memory.
    QShortcut *loadNextSC = new QShortcut(QKeySequence(Qt::Key_Up), this);
    connect(loadNextSC, SIGNAL(activated()), this, SLOT(loadNext()));
}

void MainWindow::on_calcPushButton_clicked()
{
    /**
     * Try to calculate the input in the calcLineEdit when the "="-button is
     * clicked.
     */

    // Check that user has written some input.
    if (ui->calcLineEdit->text() != ""){
        MainWindow::calculate();
    }

}

void MainWindow::calculate()
{
    /**
     * Try to calculate the input with TinuExpr. Then show the result
     * on the screen.
     */


    // Get user input from calcLineEdit.
    QString input = ui->calcLineEdit->text();

    // Remove spaces from the user input.
    input = MainWindow::removeSpaces(input);

    // QString to constChar.
    std::string inputString = input.toStdString();
    const char *inputChar = inputString.c_str();

    // Parse the calculation and store the answer.
    QString ans = QString::number(te_interp(inputChar, 0),'G',12 );

    // Put the calculation to the memory layout.
    addToMemoryLayout(input, ans);

    // Show the result on the screen.
    ui->calcLineEdit->setText(ans);
    ui->calcLineEdit->selectAll();
}

void MainWindow::addToMemoryLayout(QString input, QString ans)
{
    /**
      * Add the calculation in the memory layout. Also store the answer in the
      * memory-object.
      */

    // Store the answer in memory-object.
    memory.addToMemory(input);

    // Create a line after the widgets.
    QWidget *horizontalLine = new QWidget();
    horizontalLine -> setFixedHeight(2);
    horizontalLine -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    horizontalLine -> setStyleSheet(QString("background-color: #c0c0c0;"));
    ui->memoryLayout->insertWidget(0, horizontalLine);

    MainWindow::addCalcLayout(input, ans);

}

void MainWindow::addCalcLayout(QString input, QString ans)
{
    /**
      * Create a layout containg the calculation and the answer and add them
      * to the memoryLabel.
      */

    // Create layout.
    QHBoxLayout* calcLayout = new QHBoxLayout();

    // Create widgets.
    MemoryLabel* ansLabel = new MemoryLabel();
    MemoryLabel *calcLabel = new MemoryLabel();
    QLabel* equal = new QLabel();

    // Set texts for the labels.
    calcLabel->setText(input);
    ansLabel->setText(ans);
    equal->setText(" = ");

    // Adjust fonts.
    equal->setFont(QFont("Arial", 12));
    calcLabel->setFont(QFont("Arial", 12));
    ansLabel->setFont(QFont("Arial", 12));

    // Connect signals and slots.
    connect(ansLabel, SIGNAL(clicked(MemoryLabel*)), this,
            SLOT(on_mLabel_click(MemoryLabel*)));
    connect(calcLabel, SIGNAL(clicked(MemoryLabel*)), this,
            SLOT(on_mLabel_click(MemoryLabel*)));

    // Add labels to widget.
    calcLayout->addWidget(calcLabel);
    calcLayout->addWidget(equal);
    calcLayout->addWidget(ansLabel);

    calcLayout->addStretch();

    ui->memoryLayout->insertLayout(0, calcLayout);


}

QString MainWindow::addSpaces(QString input){
    /**
     * Add spaces to the QString input. Opposite to removeSpaces(). Add space
     * before and after every "+", "-", "*", "/" and "="-mark.
     * @param input: Calculation without spaces.
     * @return output: Calculation with added spaces.
     */
    QString space(" ");
    QString output = input;
    for (int i = 0; i<output.size(); i++){
        QString m(output[i]);
        if (m == "+" || m == "-" || m == "*"|| m == "/"|| m == "="){
            output.insert(i+1, space);
            output.insert(i, space);
            i += 1;
        }
    }
    return output;
}

QString MainWindow::removeSpaces(QString input)
{
    /**
     * Return given QString object without spaces. Opposite to addSpaces().
     * @param input: A text that may contain spaces.
     * @return output: Same as input, but no spaces.
     */

    QString output;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] != " ")
        {
            output += input[i];
        }
    }
    return output;
}

void MainWindow::on_clearButton_clicked()
{
    /**
     * "Clear"-button was clicked.
     */

    MainWindow::clearLayout(ui->memoryLayout);
}

void MainWindow::clearLayout(QLayout *layout)
{
    /**
     * Clear the memoryLayout and the Memory-object.
     */

    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            MainWindow::clearLayout(item->layout());
            delete item->layout();
        }
        else if (item->widget()) {
            delete item->widget();
        }
    }

    // Clear also the memory-object.
    memory.clearMemory();
}

void MainWindow::loadPrev()
{
    /**
      * Get earlier calculation from the Memory-object and show it in the
      * lineEdit.
      */
    QString previousCalc(memory.loadPrev(ui->calcLineEdit->text()));
    ui->calcLineEdit->setText(previousCalc);
    ui->calcLineEdit->setFocus();
}

void MainWindow::loadNext()
{
    /**
      * Load next calculation from memory if there are any.
      */
    QString nextCalc(memory.loadNext(ui->calcLineEdit->text()));
    ui->calcLineEdit->setText(nextCalc);
    ui->calcLineEdit->setFocus();

}

void MainWindow::on_calcLineEdit_textEdited(const QString &arg1)
{
    /**
      * If calcLineEdit is being edited, tell the memory that the user has
      * stopped browsing the old calculations.
      */
    memory.deactivate();
}

void MainWindow::on_mLabel_click(MemoryLabel *mLabel)
{
    /**
     * If some of the calculations in the memory layout is clicked, show it in
     * the calcLineEdit.
     * @input *mLabel: Label that is clicked.
     */

    QString calc = mLabel->text();


    ui->calcLineEdit->insert(calc);

    memory.deactivate();
}
