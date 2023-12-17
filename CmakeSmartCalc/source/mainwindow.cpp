#include "mainwindow.h"
#include "../ui_mainwindow.h"
#include "creditcalc.h"
#include "depositcalc.h"
#include "QValidator"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //GRAPH
    xBegin = -100;
    xEnd = 100;
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(xBegin, xEnd);
    ui->widget->hide();
    window()->setFixedSize(420, window()->height());


    ui->lineEdit_x->setValidator( new QDoubleValidator(-100, 100, 6, this));
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
}


void MainWindow::on_pushButton_result_clicked() {
    ui->widget->hide();
    window()->setFixedSize(420, window()->height());

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


//void MainWindow::on_pushButton_unurySign_clicked()
//{

//}


void MainWindow::on_pushButton_graph_clicked()
{
 int size = ((xEnd - xBegin) / 0.1) * 4;
 double cord[size];
 double err = s21_calcGraph(ui->label_result->text().toUtf8().data(), cord);
 if(!isnan(err)){
     for(int i = 0; i < size; i++) {
         x.push_back(cord[i++]);
         y.push_back(cord[i]);
     }
     ui->widget->show();
     window()->setFixedSize(840, window()->height());

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

