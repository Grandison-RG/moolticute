#include "MPDevice_emul_remote.h"
#include "MooltipassCmds.h"

MPDevice_emul_remote::MPDevice_emul_remote(QObject *parent):
    MPDevice(parent)
{
    qDebug() << "Emulation Device in the remote mode";
    connect(&ws, &QWebSocket::connected, this, &MPDevice_emul_remote::onConnected);

    qDebug() << "Opening of ws connection with a remote emu";
    ws.open(QUrl(QStringLiteral("ws://127.0.0.1:30036")));
}

void MPDevice_emul_remote::platformWrite(const QByteArray &data)
{
    qDebug() << "sending to remote emu";
    ws.sendBinaryMessage(data);
}

void MPDevice_emul_remote::onConnected()
{
    qDebug() << "Connected to the remote emu";

    connect(&ws, &QWebSocket::binaryMessageReceived, this, [=](const QByteArray &msg){
        qDebug() << "Received from a remote emu" << msg; 
        if((MPCmd::Command)msg.size() < 2 && (MPCmd::Command)msg.size() >= 64)
        {
            qDebug() << "Size of cmd should be more then 2 bytes and no more then 64 bytes";
            QByteArray d;
            d.resize(64);
            d[2] = 0;
            emit platformDataRead(d);
        }
        /* else if((MPCmd::Command)msg[1] == 0xff)
        {
            qDebug() << "Unimplemented or unsupported emulation command: " << MPCmd::printCmd(msg) << msg.mid(2);
            QByteArray d;
            d.resize(64);
            d[2] = 0;
            emit platformDataRead(d);
        } */ else {
            QByteArray d;
            d.resize(64);
            d.insert(0, msg);
            emit platformDataRead(d);
        }
    });
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
