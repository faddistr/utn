#ifndef IPROXYCONNECTOR_H
#define IPROXYCONNECTOR_H

#include "itransport.h"

class IProxyConnector
{
public:
    enum IProxyProcess {
        LEFT = 1,
        RIGHT = 2,
        FULL = LEFT | RIGHT
    };

    static const uint64_t cbuf_size = 4096;
    IProxyConnector(ITransport *left, ITransport *right);

virtual ssize_t do_job(ITransport *src, ITransport *dst);


private:
    ITransport *m_left;
    ITransport *m_right;
    IProxyConnector(){}
    IProxyConnector(const IProxyConnector&){}
    void process(IProxyProcess prc);
};

#endif // IPROXYCONNECTOR_H
