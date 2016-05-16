#include "handlerfact.h"
#include "chandler.h"
#include "chandlerprinter.h"

static CHandler *HandlerFact::MakeHandler(HandlerType t, QJsonObject *config){
    switch (t){
    case DEFHANDLER:
        return new CHandler(config);

    case PRINTERHANDLER:
        return new CHandlerPrinter(config);

    default:
        return NULL;
    }
}

static HandlerType HandlerFact::GetFactFromString(const QString str) {
    if (str == "PrintHandler") return PRINTERHANDLER;
    if (str == "DefHandler") return DEFHANDLER;
    return INVALIDHANDLER;
}

static CHandler *HandlerFact::MakeHandler(QString str, QJsonObject *config) {
    return MakeHandler(GetFactFromString(str), config);
}
