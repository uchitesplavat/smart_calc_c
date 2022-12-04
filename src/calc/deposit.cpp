#include "deposit.h"

#include <QLabel>
#include <QString>

#include "ui_deposit.h"

deposit::deposit(QWidget *parent) : QWidget(parent), ui(new Ui::deposit) {
  ui->setupUi(this);
  connect(ui->pushButton_result_deposit, SIGNAL(clicked()), this,
          SLOT(deposit_result()));
}

deposit::~deposit() { delete ui; }

void deposit::deposit_result() {
  double amount, term_years;
  int interest_rate, tax_rate;
  deposit_output res = {0};
  deposit_input input = {0};
  int mode = 1;
  if (ui->cap_int_checkBox->isChecked()) {
    mode = 0;
  }
  input.amount = ui->amount->text().toDouble();
  input.term_in_months = ui->term_years->text().toDouble();
  input.interest_rate = ui->interest_rate->text().toDouble();
  input.tax_rate = ui->tax_rate->text().toDouble();

  if (ui->pereodic_pay->currentIndex() == 0) {
    input.add_month = 1;
  } else if (ui->pereodic_pay->currentIndex() == 1) {
    input.add_quater = 1;
  } else if (ui->pereodic_pay->currentIndex() == 2) {
    input.add_day = 1;
  }

  res = calc_deposit(input);

  ui->accures_int->setText(QString::number(res.accrued_interest, 'g', 10));
  ui->tax_amount->setText(QString::number(res.tax_amount, 'g', 10));
  ui->end_deposit->setText(QString::number(res.end_deposit, 'g', 10));
}
