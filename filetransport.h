#ifndef FILETRANSPORT_H
#define FILETRANSPORT_H
#include "itransport.h"
#include <QFile>

class FileTransport : public ITransport
{
public:
    FileTransport(QJsonObject *config);
    ~FileTransport();
    ssize_t send(uint32_t id, void *buf, size_t length);
    ssize_t recv(uint32_t *id, void *buf, size_t length);
    uint32_t Add(QJsonObject *acc);
private:
   QList<QFile *> m_flist;
};

#endif // FILETRANSPORT_H
