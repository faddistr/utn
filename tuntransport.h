#ifndef TUNTRANSPORT_H
#define TUNTRANSPORT_H
#include "itransport.h"
#include <QJsonObject>

class TunTransport : public ITransport
{
public:
    TunTransport(QJsonObject *config);
    ssize_t send(uint32_t id, void *buf, size_t length);
    ssize_t recv(uint32_t *id, void *buf, size_t length);
};


#endif // TUNTRANSPORT_H
