#include "MPDevice_emul_remote.h"

MPDevice_emul_remote::MPDevice_emul_remote(QObject *parent):
    MPDevice(parent)
{
    qDebug() << "Emulation Device in the remote mode";

    qDebug() << "remote emul WIP, I am exiting :), lol";
    qApp->exit();
}

void MPDevice_emul_remote::platformWrite(const QByteArray &data)
{
}

void MPDevice_emul_remote::platformRead()
{
    qDebug() << "PlatformRead in the remote mode";
}
