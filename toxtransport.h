#ifndef TOXTRANSPORT_H
#define TOXTRANSPORT_H
#include "itransport.h"
#include <QJsonObject>

class ToxTransport : public ITransport
{
public:
    ToxTransport(QJsonObject *config);
    ssize_t send(uint32_t id, void *buf, size_t length);
    ssize_t recv(uint32_t *id, void *buf, size_t length);
};

#endif // TOXTRANSPORT_H
