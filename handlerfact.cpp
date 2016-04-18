#include "handlerfact.h"
#include "chandler.h"
#include "chandlerprinter.h"

CHandler *HandlerFact::MakeHandler(HandlerType t, QJsonObject *config){
    switch (t){
    case DEFHANDLER:
        return new CHandler(config);

    case PRINTERHANDLER:
        return new CHandlerPrinter(config);

    default:
        return NULL;
    }
}

