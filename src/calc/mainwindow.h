#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "./QCustomPlot-library/lib/qcustomplot.h"
#include "credit.h"
#include "deposit.h"

extern "C" {
#include "calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  credit Credit;
  deposit Deposit;
 private slots:

  void digit_numbers();
  void digit_dot();
  // void digit_div();
  // void digit_left_skobe();
  // void digit_right_skobe();
  // void digit_plus();
  void digit_result();
  void all_operations();
  void del();
  void x_symbol();
  void graph_res();
  //    void unary_pressed();
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
};
#endif  // MAINWINDOW_H
