#ifndef MPDEVICE_EMUL_REMOTE_H
#define MPDEVICE_EMUL_REMOTE_H
#include <QtWebSockets/QWebSocket>
#include "MPDevice.h"

class MPDevice_emul_remote : public MPDevice
{
public:
    explicit MPDevice_emul_remote(QObject *parent);
    virtual ~MPDevice_emul_remote(); 
private:
    QWebSocket ws;
    virtual void platformRead();
    virtual void platformWrite(const QByteArray &data);

private Q_SLOTS:
    void onConnected();
};

#endif // MPDEVICE_EMUL_H
