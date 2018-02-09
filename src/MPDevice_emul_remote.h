#ifndef MPDEVICE_EMUL_REMOTE_H
#define MPDEVICE_EMUL_REMOTE_H
#include "MPDevice.h"

class MPDevice_emul_remote : public MPDevice
{
public:
    MPDevice_emul_remote(QObject *parent);
private:
    virtual void platformRead();
    virtual void platformWrite(const QByteArray &data);
};

#endif // MPDEVICE_EMUL_H
