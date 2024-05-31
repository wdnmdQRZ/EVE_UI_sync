#ifndef COVERCONFIRMATION_H
#define COVERCONFIRMATION_H

#include <QDialog>

namespace Ui {
class coverconfirmation;
}

class coverconfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit coverconfirmation(QWidget *parent = nullptr);
    ~coverconfirmation();

private slots:
    void on_pushButton_coveryes_clicked();

    void on_pushButton_coverno_clicked();

signals:
    void sendData(QString msg);
    //发射信号

private:
    Ui::coverconfirmation *ui;
};

#endif // COVERCONFIRMATION_H
