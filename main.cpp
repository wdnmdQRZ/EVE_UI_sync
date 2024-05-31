#include "mainwindow.h"
#include "backupsconfirmation.h""
#include <QApplication>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    backupsconfirmation b;
    w.show();

    return a.exec();
}
