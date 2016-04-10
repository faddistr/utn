#ifndef PKTSTR
#define PKTSTR
#include <QByteArray>
#include <stdint.h>

typedef struct
{
    uint32_t tid;
    uint32_t cid;
    QByteArray *payload;
}tpkt;

#endif // PKTSTR

