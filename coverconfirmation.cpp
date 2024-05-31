#include "coverconfirmation.h"
#include "ui_coverconfirmation.h"

coverconfirmation::coverconfirmation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::coverconfirmation)
{
    ui->setupUi(this);
}

coverconfirmation::~coverconfirmation()
{
    delete ui;
}

void coverconfirmation::on_pushButton_coveryes_clicked()
{
    emit sendData("cover");
    this->close();
}


void coverconfirmation::on_pushButton_coverno_clicked()
{
    this->close();
}

