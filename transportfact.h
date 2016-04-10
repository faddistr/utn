#ifndef TRANSPORTFACT_H
#define TRANSPORTFACT_H
#include "itransport.h"
#include <QJsonObject>

class TransportFact
{
private:
    TransportFact();
    TransportFact(const TransportFact &);
public:
    enum transportID {
        TOXTRANSPORT,
        TUNTRANSPORT,
        FILETRANSPORT
    };

    static ITransport * makeTransport(transportID id, QJsonObject *config);
};

#endif // TRANSPORTFACT_H
