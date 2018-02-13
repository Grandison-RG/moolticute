#include "MPDevice_emul_remote.h"
#include "MooltipassCmds.h"

MPDevice_emul_remote::MPDevice_emul_remote(QObject *parent):
    MPDevice(parent)
{
    qDebug() << "Emulation Device in the remote mode";
    connect(&ws, &QWebSocket::connected, this, &MPDevice_emul_remote::onConnected);

    qDebug() << "Opening of ws connection with a remote emu";
    ws.open(QUrl(QStringLiteral("ws://localhost:30036")));
}

void MPDevice_emul_remote::platformWrite(const QByteArray &data)
{
    //qDebug() << "Unimplemented emulation command: " << MPCmd::printCmd(data) << data.mid(2);

    QByteArray d = data;
    d.resize(64);
    d[2] = 0; //result is 0

    QTimer::singleShot(0, [=]()
    {
        emit platformDataRead(d);
    });
}

void MPDevice_emul_remote::onConnected()
{
    qDebug() << "Connected to the remote emu";

    ws.sendTextMessage(QStringLiteral("Hello, remote haskell emu!"));
}

void MPDevice_emul_remote::platformRead()
{
    qDebug() << "PlatformRead in the remote mode";
}

MPDevice_emul_remote::~MPDevice_emul_remote()
{

    qDebug() << "Closing of ws connection with a remote emu";
    ws.close();
}
