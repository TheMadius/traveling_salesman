#include <QApplication>
#include <QProcess>

#include <signal.h>
#include <boost/stacktrace.hpp>
#include "forminteractivemap.h"
#include <cstdio>
#include <unistd.h>
#include <sys/utsname.h>
#include <cassert>
#include <QFile>

FormInteractiveMap *win;

void PrintKernelInfo()
{
    utsname kernelInfo;
    const int code = uname(&kernelInfo);
    if (code == 0) {
        qDebug() << QString("--Kernel info --");
        qDebug() << QString("nodename = %1").arg(kernelInfo.nodename);
        qDebug() << QString("machine = %1").arg(kernelInfo.machine);
        qDebug() << QString("sysname = %1").arg(kernelInfo.sysname);
        qDebug() << QString("release = %1").arg(kernelInfo.release);
        qDebug() << QString("version = %1").arg(kernelInfo.version);
    }
    QProcess proc;
    proc.start("lshw", QStringList() << "-short");
    proc.waitForFinished(-1);
    QByteArray output = proc.readAll();
    proc.close();
    QString str(output);
    QStringList list = str.split('\n');
    for (int i = 0; i < list.count(); i++) {
        qDebug() << list[i];
    }

}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    FormInteractiveMap w;

    QFile file(":/qdarkstyle/dark/style.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    a.setAttribute(Qt::AA_DisableWindowContextHelpButton);

    w.show();
    PrintKernelInfo();

    return a.exec();
}
