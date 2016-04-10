#include "toxtransport.h"

ToxTransport::ToxTransport(QJsonObject *config) : ITransport(config)
{
    m_config = config;
}

ssize_t ToxTransport::send(uint32_t id, void *buf, size_t length)
{
    return 0;
}

ssize_t ToxTransport::recv(uint32_t *id, void *buf, size_t length)
{
    return 0;
}
