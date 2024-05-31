#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include <QDialog>

namespace Ui {
class confirmation;
}

class confirmation : public QDialog
{
    Q_OBJECT

public:
    explicit confirmation(QWidget *parent = nullptr);
    ~confirmation();

private:
    Ui::confirmation *ui;
};

#endif // CONFIRMATION_H
