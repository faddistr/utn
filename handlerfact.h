#ifndef HANDLERFACT_H
#define HANDLERFACT_H
#include "chandler.h"

class HandlerFact
{
public:
    enum HandlerType{
        DEFHANDLER
    };
    static CHandler *MakeHandler(HandlerType t, QJsonObject *config);
};

#endif // HANDLERFACT_H
