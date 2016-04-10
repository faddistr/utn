#include "transportfact.h"
#include "toxtransport.h"
#include "tuntransport.h"
#include "filetransport.h"

 ITransport * TransportFact::makeTransport(transportID id, QJsonObject *config)
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
