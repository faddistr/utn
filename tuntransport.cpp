#include "tuntransport.h"

TunTransport::TunTransport(QJsonObject *config) : ITransport(config)
{

}

ssize_t TunTransport::send(uint32_t id, void *buf, size_t length)
{
    return 0;
}

ssize_t TunTransport::recv(uint32_t *id, void *buf, size_t length)
{
    return 0;
}
