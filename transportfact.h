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
        FILETRANSPORT,
        INVALIDTRANSPORT
    };

    static ITransport * makeTransport(transportID id, QJsonObject *config);
    static ITransport * makeTransport(const QString id, QJsonObject *config);
private:
    static const transportID GetTransportFromString(const QString str);
};

#endif // TRANSPORTFACT_H
