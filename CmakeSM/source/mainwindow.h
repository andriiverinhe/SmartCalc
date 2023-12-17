#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#ifdef __cplusplus
extern "C" {
#endif
#include "SmartCalc/s21_smartCalc.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    double xBegin, xEnd;
    int xMin, xMax, yMin, yMax;
    QVector <double> x, y;
private:
    void cleanLabel();

private slots:
    void digitNumbers();
    void bracket();
    void function();
    void buttonSign();
    void on_pushButton_clean_clicked();
    void on_pushButton_result_clicked();
    void on_pushButton_graph_clicked();
    void on_pushButton_x_clicked();
    void on_actionCredit_triggered();
    void on_actionDeposit_triggered();
    void on_pushButton_clearSign_clicked();
};

#endif // MAINWINDOW_H
