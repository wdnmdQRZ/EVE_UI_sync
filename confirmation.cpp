#include "confirmation.h"
#include "ui_confirmation.h"

confirmation::confirmation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::confirmation)
{


}

confirmation::~confirmation()
{
    delete ui;
}
