#ifndef HANDLERFACT_H
#define HANDLERFACT_H
#include "chandler.h"

class HandlerFact
{
public:
    enum HandlerType{
        DEFHANDLER,
        PRINTERHANDLER,
        INVALIDHANDLER
    };
    static CHandler *MakeHandler(HandlerType t, QJsonObject *config);
    static CHandler *MakeHandler(const QString t, QJsonObject *config);
private:
    static HandlerType GetFactFromString(const QString str);
};

#endif // HANDLERFACT_H
