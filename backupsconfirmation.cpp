#include "backupsconfirmation.h"
#include "ui_backupsconfirmation.h"
#include "QDebug"

backupsconfirmation::backupsconfirmation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::backupsconfirmation)
{
    ui->setupUi(this);
}

backupsconfirmation::~backupsconfirmation()
{
    delete ui;
}


void backupsconfirmation::on_pushButton_backyse_clicked()
{
    emit sendData("back");
    this->close();
}


void backupsconfirmation::on_pushButton_backno_clicked()
{
    this->close();
}
