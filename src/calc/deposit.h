#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>

extern "C" {
#include "calc.h"
}

namespace Ui {
class deposit;
}

class deposit : public QWidget {
  Q_OBJECT

 public:
  explicit deposit(QWidget *parent = nullptr);
  ~deposit();

 private:
  Ui::deposit *ui;
 private slots:
  void deposit_result();
};

#endif  // DEPOSIT_H
