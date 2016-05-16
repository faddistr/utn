#include "transportfact.h"
#include "toxtransport.h"
#include "tuntransport.h"
#include "filetransport.h"

static ITransport * TransportFact::makeTransport(transportID id, QJsonObject *config)
 {
     switch(id)
     {
        case TOXTRANSPORT:
            return new ToxTransport(config);

        case TUNTRANSPORT:
            return new TunTransport(config);

        case FILETRANSPORT:
            return new FileTransport(config);

        default:
            return NULL;
     }
     return NULL;
 }

static const transportID TransportFact::GetTransportFromString(const QString str)
{
    if (str == "ToxTransport") return TOXTRANSPORT;
    if (str == "TunTransport") return TUNTRANSPORT;
    if (str == "FileTransport") return FILETRANSPORT;
    return INVALIDTRANSPORT;
}


static ITranpsort * TransportFact::makeTransport(const QString str, QJsonObject *config)
{
    return makeTransport(GetTransportFromString(str), config);
}
