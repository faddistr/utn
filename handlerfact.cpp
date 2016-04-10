#include "handlerfact.h"


CHandler *HandlerFact::MakeHandler(HandlerType t, QJsonObject *config){
    switch (t){
    case DEFHANDLER:
        return new CHandler(config);

    default:
        return NULL;
    }
}

