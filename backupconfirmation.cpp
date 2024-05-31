#include "backupconfirmation.h"
#include "ui_backupconfirmation.h"

backupconfirmation::backupconfirmation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::backupconfirmation)
{
    ui->setupUi(this);
}

backupconfirmation::~backupconfirmation()
{
    delete ui;
}
