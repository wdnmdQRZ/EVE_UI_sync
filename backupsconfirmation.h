#ifndef BACKUPSCONFIRMATION_H
#define BACKUPSCONFIRMATION_H

#include <QDialog>

namespace Ui {
class backupsconfirmation;
}

class backupsconfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit backupsconfirmation(QWidget *parent = nullptr);
    ~backupsconfirmation();

private slots:
    void on_pushButton_backyse_clicked();

    void on_pushButton_backno_clicked();


signals:
    void sendData(QString msg);
    //发射信号

private:
    Ui::backupsconfirmation *ui;
};

#endif // BACKUPSCONFIRMATION_H
