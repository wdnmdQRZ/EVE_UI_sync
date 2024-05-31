#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_detectionButton_clicked();
    //按钮detectionButton的点击信号槽

    void on_actionChinses_triggered();
    //菜单actionChinses的点击信号槽

    void on_actionEnglish_triggered();
    //菜单actionEnglish的点击信号槽

    void on_pushButton_backups_clicked();

    void on_pushButton_ConfirmPath_clicked();

    void reciveData(QString);//接收信号

    void on_pushButton_overwrite_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
