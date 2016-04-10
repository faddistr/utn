#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <sys/types.h>
#include <stdint.h>
#include <qjsonobject.h>

#define ITRANSPORT_ERROR UINT32_MAX

class ITransport : public QObject
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
private:
    ITransport(const ITransport&){}
protected:
    QJsonObject *m_config;
};


#endif // ITRANSPORT_H

