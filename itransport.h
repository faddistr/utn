#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <sys/types.h>
#include <stdint.h>
#include <qobject.h>
#include <qjsonobject.h>

#define ITRANSPORT_ERROR UINT32_MAX

class ITransport
{


public:
    ITransport(QJsonObject *config){
        m_config = config;
    }
    virtual ~ITransport() {}
    virtual ssize_t send(uint32_t id, void *buf, size_t length) = 0;
    virtual ssize_t recv(uint32_t *id, void *buf, size_t length) = 0;
    virtual uint32_t Add(QJsonObject *acc) {
        return ITRANSPORT_ERROR;
    }
    virtual uint32_t getRxPktSize() {return 4096;}
    virtual uint32_t getTxPktSize() {return 4096;}
private:
    ITransport(const ITransport&){}
    explicit ITransport(QObject *parent = 0) {}
protected:
    QJsonObject *m_config;
};


#endif // ITRANSPORT_H

