#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <shlobj.h>
#include <algorithm>
#include <filesystem>
#include <backupsconfirmation.h>
#include <coverconfirmation.h>
#include <io.h>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <iostream>
#include <fstream>
#include <string>
#include "global.h"

using namespace std;

class message;
QString qstr_UserName;      //最终文件路径
QStringList qstrl_FileName;  //定义一个 QStringList 类型的变量,用于存储文件名
int int_FilesNumber = 0;    //记录实际文件数量
QString qstr_UserFiles[300];  //记录 user 文件
int int_UserNumber = 0;     //记录 user 文件数量
QString qstr_CharFiles[300];  //记录 char 文件
int int_CharNumber = 0;     //记录 char 文件数量

/*这里利用的C+自带的fileInfo函数进行遍历，效果不好，改用QT自带函数

void GetFiles(QString qstr_Path) {
    QDir _dir(qstr_Path);
    QFileInfoList fileInfoList = _dir.entryInfoList();
    for (const QFileInfo &fileInfo : fileInfoList) {
        if (fileInfo.isFile() && fileInfo.suffix() == "dat") { // 判断扩展名是否为".dat"
            qstr_FilesName[int_FilesNumber] = fileInfo.fileName(); // 将遍历到的文件的文件名添加到 str_FilesName 数组中
            int_FilesNumber++; // 实际文件数量加1
        }
    }
}
*/

//************************************
// 方法名称:	copyFolder
// 概要:		复制文件夹
// 返回值:		bool
// 参数:		const QString & fromDir 原路径
// 参数:		const QString & toDir 新路径
// 参数:		bool coverFileIfExist 如果存在是否覆盖
//************************************
bool copyFolder(const QString& fromDir, const QString& toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);

    if (!targetDir.exists())
    {    //如果目标目录不存在，则进行创建
        if (!targetDir.mkdir(targetDir.absolutePath())) return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if (fileInfo.fileName() == "." || fileInfo.fileName() == "..") continue;

        if (fileInfo.isDir())
        {    // 当为目录时，递归的进行copy
            if (!copyFolder(fileInfo.filePath(),
                            targetDir.filePath(fileInfo.fileName()),
                            coverFileIfExist))
                return false;
        }
        else
        {   //当允许覆盖操作时，将旧文件进行删除操作
            if (coverFileIfExist && targetDir.exists(fileInfo.fileName()))
            {
                targetDir.remove(fileInfo.fileName());
            }

            // 进行文件拷贝
            if (!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))
            {
                return false;
            }
        }
    }
    return true;
}

void generateLogFile(const string& logContent, const string& fileName) {
    ofstream logFile;
    logFile.open(fileName, ios::app); // 以追加模式打开文件
    if (logFile.is_open()) {
        logFile << logContent << endl; // 将日志内容写入文件
        logFile.close(); // 关闭文件
    } else {
        qDebug() << "无法打开日志文件";
    }
}

void GetFiles(QString qstr_Path){
    QDir _dir(qstr_Path);
    if(!_dir.exists()){
    //检测路径是否存在
        qDebug()<<"路径不存在";
        string logContent = "路径不存在\n";
        string fileName = "log.txt";
        generateLogFile(logContent, fileName); // 调用生成log文件的函数
        return;
    }
    else{
        QStringList qstrl_lastname ;
        qstrl_lastname << "*0.dat"<< "*1.dat"<< "*2.dat"<< "*3.dat"<< "*4.dat"<< "*5.dat"<< "*6.dat"<< "*7.dat"<< "*8.dat"<< "*9.dat";
        //可叠加，可使用通配符筛选,例如 filename << "*.dat"<<"*.jpg";
        qstrl_FileName = _dir.entryList(qstrl_lastname,QDir::Files | QDir::Readable,QDir::Name);
        int_FilesNumber++;
        //qstrl_filename里就是获取的所有文件名了

        /*QStringList 的访问方法：
        for（int i = 0;i < qstrl_filename.size();i ++){
            QString _str = qstrl_filename[i];
        }
        */
    }


}

void FilterFiles(){
    int_UserNumber=0;
    int_CharNumber=0;
    //文件数量清零，不然每点一次按钮列表就会写入一次
    for(int i=0;i<qstrl_FileName.size();i++){
        if(qstrl_FileName[i].contains("core_user_",Qt::CaseSensitive)){
            //如果包含"core_user_"则返回真，该判断语句为包含语句
            qstr_UserFiles[int_UserNumber]=qstrl_FileName[i];
            int_UserNumber++;
        }
        else if(qstrl_FileName[i].contains("core_char_",Qt::CaseSensitive)){
            //如果包含"core_char_"则返回真，该判断语句为包含语句
            qstr_CharFiles[int_CharNumber]=qstrl_FileName[i];
            int_CharNumber++;
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_detectionButton_clicked()
{
    int_FilesNumber = 0;    //记录实际文件数量
    int_UserNumber = 0;     //记录 user 文件数量
    int_CharNumber = 0;     //记录 char 文件数量
    for(int i=0;i<300;i++){
        qstr_CharFiles[i]="\0";
        qstr_UserFiles[i]="\0";
    }

    wchar_t wchar_UserName[255];
    //初始化 wchar_UserName

    SHGetSpecialFolderPath(0, wchar_UserName, CSIDL_LOCAL_APPDATA, false);
    //获取当前用户 AppData 目录

    qstr_UserName=QString::fromWCharArray(wchar_UserName);
    //将 wchar_t 字符串转换为 QString

    QString qstr_nextUserName="\\CCP\\EVE\\d_game_eve_online_tq_tranquility\\settings_Default";
    //创建字符串记录游戏路径

    qstr_UserName=qstr_UserName+qstr_nextUserName;
    //拼接字符串,即 C:\Users\28145\.arg(AppData......) 以实现获取 EVE 文件夹路径

    ui->lineEdit_Path->setText(qstr_UserName);//用 QLineEdit 输出路径
    //显示路径

}


void MainWindow::on_actionChinses_triggered()
{
    message::glo_qstr_Langue="Chinese";
    //翻译
    ui->detectionButton->setText("检测文件夹路径");
    ui->label->setText("你的数据可能在：");
    ui->pushButton_backups->setText("备份");
    ui->pushButton_overwrite->setText("覆盖");
    ui->pushButton_ConfirmPath->setText("我确定在此路径");
    ui->label_tip->setText("使用说明：\n1.选择已经调整好的UI文件（char文件），不用管user文件是什么\n2.点击覆盖，则会将登录器内的全部角色UI变成选的角色的UI\n3.点击备份，会在存放数据路径新建一个备份文件夹，建议覆盖前先备份\n提示：可以通过KB网查询自己角色的char代码，也可以在聊天频道拖入自己的名字，\n复制之后在任意txt文件内粘贴，也可以看到当前角色的char代码");
}


void MainWindow::on_actionEnglish_triggered()
{
    message::glo_qstr_Langue="English";
    //translate
    ui->detectionButton->setText("Detect folder path");
    ui->label->setText("Your data may be in:");
    ui->pushButton_backups->setText("Backups");
    ui->pushButton_overwrite->setText("Overwrite");
    ui->pushButton_ConfirmPath->setText("I am certain that this path");
    ui->label_tip->setText("Instructions:\n1. Select the adjusted UI file (char file), ignore what the user file is.\n2. Click \"Overwrite\", and all character UIs within the login tool will be change\nto the selected character's UI.\n3. Click \"Backup\", a new backup folder will be created in the data storage path,\nit is recommended to backup before overwriting.\nTip: You can check your character's char code through KB website, or drag your\nname into the chat channel,copy it and then paste it in any txt file, you can also\nsee the current character's char code.");
}

void MainWindow::reciveData(QString message){
    bool b_ok;
    //接收到信号后，对文件进行操作
    if(message=="cover"){
        qDebug()<<"已检测到信号";

        int int_index = ui->comboBox_char->currentIndex();
        qDebug()<<"已获得当前QComboBox索引："<<int_index;
        //获得当前QComboBox索引

        QString qstr_LastFilePath=qstr_UserName+"\\"+qstr_CharFiles[int_index];
        qDebug()<<"已编写总UI路径文件"<<qstr_LastFilePath;
        //编写总UI路径文件

        QString qstr_NextFilePath;
        //创建需要被覆盖的文件路径

        //以下开始覆盖文件
        for(int i=0;i<int_CharNumber;i++){
            qstr_NextFilePath=qstr_UserName+"\\"+qstr_CharFiles[i];
            qDebug()<<"已组合需要被覆盖的文件路径"<<qstr_NextFilePath;
            //组合需要被覆盖的文件路径

            if(i==int_index){
                qDebug()<<"当前文件为总UI文件，已跳过";
                continue;
                //如果当前文件为总UI文件，则跳过
            }
            b_ok=QFile::remove(qstr_NextFilePath);
            qDebug()<<"已删除"<<b_ok;
            b_ok=QFile::copy(qstr_LastFilePath,qstr_NextFilePath);
            qDebug()<<"-----已复制"<<b_ok<<"-----";
            //否则进行覆盖
        }
    }
    else if(message=="back"){
        b_ok=copyFolder(qstr_UserName, qstr_UserName+"_backup", 1);
        qDebug()<<"已覆盖"<<b_ok;
        //备份文件
    }
}

void MainWindow::on_pushButton_backups_clicked()
{
    backupsconfirmation *backcon=new backupsconfirmation();
    this->connect(backcon, SIGNAL(sendData(QString)), this, SLOT(reciveData(QString)));
    //连接两个窗口的信号槽
    backcon->show();
}

void MainWindow::on_pushButton_overwrite_clicked()
{
    coverconfirmation *covercon=new coverconfirmation();
    this->connect(covercon, SIGNAL(sendData(QString)), this, SLOT(reciveData(QString)));
    //连接两个窗口的信号槽
    covercon->show();
}

void MainWindow::on_pushButton_ConfirmPath_clicked()
{
    QString qstr_UserName=ui->lineEdit_Path->text();
    //从lineEdit获取正确的路径

    GetFiles(qstr_UserName);
    //记录文件函数

    FilterFiles();
    //分离 user 和 char 文件

    sort(qstr_UserFiles,qstr_UserFiles+int_UserNumber);
    sort(qstr_CharFiles,qstr_CharFiles+int_CharNumber);
    //对 user 和 char 排序

    if(int_UserNumber != 0 && int_CharNumber != 0){
        ui->pushButton_overwrite->setDisabled(false);
        ui->pushButton_backups->setDisabled(false);
        //comboBox存在数据时，覆盖和备份按钮点亮
    }
    else{
        ui->pushButton_overwrite->setDisabled(true);
        ui->pushButton_backups->setDisabled(true);
        //comboBox不存在数据时，覆盖和备份按钮关闭
    }

    ui->comboBox_user->clear();
    ui->comboBox_char->clear();
    //对列表清零
    int int_temporaryUser=int_UserNumber;
    int int_temporaryChar=int_CharNumber;
    //定义临时变量存储文件数量

    for(int i=0;i<int_temporaryUser;i++){
        ui->comboBox_user->addItem(qstr_UserFiles[i]);
        //在 comboBox_user 中添加 str_UserFiles 里的数据,使用 addItem 函数
    }
    for(int i=0;i<int_temporaryChar;i++){
        ui->comboBox_char->addItem(qstr_CharFiles[i]);
        //在 comboBox_char 中添加 str_CharFiles 里的数据,使用 addItem 函数
    }
}

