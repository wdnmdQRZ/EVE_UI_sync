#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>

class global
{
public:
    global();
};

class message     //新建一个类存放全局变量
{
public:
    static QString glo_qstr_Langue;
    static QString glo_qstr_UserFiles[];
    static QString glo_qstr_CharFiles[];

};

#endif // GLOBAL_H
