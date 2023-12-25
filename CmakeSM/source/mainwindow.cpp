#include <QValidator>
#include "mainwindow.h"
#include "../ui_mainwindow.h"
#include "creditcalc.h"
#include "depositcalc.h"
#include "qcustomplot.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //GRAPH
    xBegin = -25;
    xEnd = 25;
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(xBegin, xEnd);
    hideGraph();

    ui->lineEdit_x->setValidator( new QDoubleValidator(-100, 100, 6, this));
    ui->lineEdit_xMax->setValidator(new QIntValidator(-1000000, 1000000, this));
    ui->lineEdit_xMin->setValidator(new QIntValidator(-1000000, 1000000, this));
    ui->lineEdit_yMax->setValidator(new QIntValidator(-1000000, 1000000, this));
    ui->lineEdit_yMin->setValidator(new QIntValidator(-1000000, 1000000, this));

    ui->lineEdit_xMax->setText("25");
    ui->lineEdit_yMax->setText("25");
    ui->lineEdit_xMin->setText("-25");
    ui->lineEdit_yMin->setText("-25");
    // BUTTON DIGIT
    connect(ui->pushButton__0, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton__1, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton__2, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton__3, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton__4, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton__5, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton__6, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton__7, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton__8, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    connect(ui->pushButton__9, SIGNAL(clicked()), this, SLOT(digitNumbers()));
    // BUTTON BRACKET
    connect(ui->pushButton_bracket_left, SIGNAL(clicked()), this, SLOT(bracket()));
    connect(ui->pushButton_bracket_right, SIGNAL(clicked()), this, SLOT(bracket()));
    // BUTTON FUNCTION
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_power, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(function()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(function()));
    // BUTTON SIGN
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(buttonSign()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(buttonSign()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(buttonSign()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(buttonSign()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(buttonSign()));


}

MainWindow::~MainWindow()
{
    delete ui;
}
static bool clickedResult = false;

void MainWindow::cleanLabel() {
    if(clickedResult) {
        clickedResult = false;
        on_pushButton_clean_clicked();
    }
}

void MainWindow::digitNumbers() {
    QPushButton *button = (QPushButton *)sender();
    cleanLabel();

    QString textButton = button->text();
    QString resultText = ui->label_result->text();
    ui->label_result->setText(resultText + textButton);
}

void MainWindow::bracket() {
    QPushButton *button = (QPushButton *)sender();
    cleanLabel();

    QString textButton = button->text();
    QString resultText = ui->label_result->text();
    ui->label_result->setText(resultText + textButton);
}

void MainWindow::function() {
    QPushButton *button = (QPushButton *)sender();
    cleanLabel();
    QString textButton = button->text();
    if(textButton == "mod") textButton = "%";
    QString resultText = ui->label_result->text();
    ui->label_result->setText(resultText + textButton);
}

void MainWindow::buttonSign() {
    QPushButton *button = (QPushButton *)sender();
    cleanLabel();
    QString textButton = button->text();
    QString resultText = ui->label_result->text();
    ui->label_result->setText(resultText + textButton);
}


void MainWindow::on_pushButton_clean_clicked()
{
    ui->label_result->setText("");
    ui->lineEdit_x->setText("");
    ui->widget->clearGraphs();
}


void MainWindow::on_pushButton_result_clicked() {
    hideGraph();
    

    clickedResult = true;
    QString myQString = ui->label_result->text();
    double x = 0.0;
    if(myQString.contains('x',  Qt::CaseInsensitive)){
        x = ui->lineEdit_x->text().toDouble();
    } else
       ui->lineEdit_x->setText("");


    double result = s21_calc(myQString.toUtf8().data(), x);
    if(!isnan(result))
        ui->label_result->setText(QString::number(result));
    else
        ui->label_result->setText((QString)"Invalid input value.");

}

void MainWindow::setSizeGraph() {
    ui->widget->clearGraphs();
    xMax = ui->lineEdit_xMax->text().toInt();
    xMin = ui->lineEdit_xMin->text().toInt();
    yMax = ui->lineEdit_yMax->text().toInt();
    yMin = ui->lineEdit_yMin->text().toInt();

    if(xMax > 1000000) xMax = 1000000;
    if(yMax > 1000000) yMax = 1000000;
    if(xMin < -1000000) xMin = -1000000;
    if(yMin < -1000000) yMin = -1000000;

    xBegin = xMin;
    xEnd = xMax;

    ui->widget->xAxis->setRange(xMin, xMax);
    ui->widget->yAxis->setRange(yMin, yMax);
};

void MainWindow::showGraph() {
     window()->setFixedSize(842, window()->height());
     ui->widget->show();
     ui->lineEdit_xMax->show();
     ui->lineEdit_yMax->show();
     ui->lineEdit_xMin->show();
     ui->lineEdit_yMin->show();

     ui->label_xMax->show();
     ui->label_yMax->show();
     ui->label_xMin->show();
     ui->label_yMin->show();
};
void MainWindow::hideGraph() {
    window()->setFixedSize(420, window()->height());
    ui->widget->hide();
    ui->lineEdit_xMax->hide();
    ui->lineEdit_yMax->hide();
    ui->lineEdit_xMin->hide();
    ui->lineEdit_yMin->hide();

    ui->label_xMax->hide();
    ui->label_yMax->hide();
    ui->label_xMin->hide();
    ui->label_yMin->hide();
};

void MainWindow::on_pushButton_graph_clicked()
{
 setSizeGraph();
 int size = ((xEnd - xBegin) / 0.1);
//  double cord[size];
//  double err = s21_calcGraph(ui->label_result->text().toUtf8().data(), cord, size);
    char input[256] = {""};
    strcpy(input, ui->label_result->text().toUtf8().data());
 if(strlen(input) != 0 && s21_validator(input)) {
    s21_stack *main = NULL;
    main = s21_getStackFromStr(input, main);
    main = s21_getStackOnPolishNotation(main);
    double X = xBegin;
    for(int i = 0; i < size; i++, X+= 0.1) {
        s21_stack *copy = s21_copyStack(main);
        if (s21_checkX(copy)) {
            s21_replacingXforValue(copy, X);
        }
        x.push_back(X);
        y.push_back(s21_NewCalculator(copy));

        if (copy)
            s21_clearStack(copy);
    }
    if (main)
     s21_clearStack(main);
     showGraph();
     ui->widget->clearGraphs();
     ui->widget->addGraph();
     ui->widget->graph(0)->addData(x, y);
     ui->widget->replot();
     x.clear();
     y.clear();
 } else
     QMessageBox::critical(nullptr, "Ошибка", "Invalid input value!");
}


void MainWindow::on_pushButton_x_clicked()
{
    cleanLabel();
    QString resultText = ui->label_result->text();
    ui->label_result->setText(resultText + "x");
}


void MainWindow::on_actionCredit_triggered()
{
    creditcalc window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_actionDeposit_triggered()
{
    depositcalc window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_pushButton_clearSign_clicked() {
    QString text = ui->label_result->text();
    QString newText = "";
    if(text.size() != 0) for(int i = 0; i < text.size() - 1; i++) newText.append(text[i]);
    ui->label_result->setText(newText);
}

