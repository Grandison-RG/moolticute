#include "MPDevice_emul_remote.h"
#include "MooltipassCmds.h"

MPDevice_emul_remote::MPDevice_emul_remote(QObject *parent):
    MPDevice(parent)
{
    qDebug() << "Emulation Device in the remote mode";
}

void MPDevice_emul_remote::platformWrite(const QByteArray &data)
{
    qDebug() << "Unimplemented emulation command: " << MPCmd::printCmd(data) << data.mid(2);

    QByteArray d = data;
    d.resize(64);
    d[2] = 0; //result is 0

    QTimer::singleShot(0, [=]()
    {
        emit platformDataRead(data);
    });
}

void MPDevice_emul_remote::platformRead()
{
    qDebug() << "PlatformRead in the remote mode";
}
