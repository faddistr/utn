#include "iproxyconnector.h"

IProxyConnector::IProxyConnector(ITransport *left, ITransport *right)
{
    m_left = left;
    m_right = right;
}

ssize_t IProxyConnector::do_job(ITransport *src, ITransport *dst)
{
    uint8_t buf[cbuf_size];
    uint32_t id = ~0;
    ssize_t ret = src->recv(&id, buf, cbuf_size);

    if (ret > 0) {
        dst->send(id, buf, ret);
    }

    return ret;
}

void IProxyConnector::process(IProxyProcess prc)
{
    if ((prc & LEFT) == LEFT){
        do_job(m_left, m_right);
    }

    if ((prc & RIGHT) == RIGHT){
        do_job(m_right, m_left);
    }
}
