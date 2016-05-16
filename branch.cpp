#include "branch.h"
#include <assert.h>
#include <iterator>
#include "transportfact.h"
#include "handlerfact.h"

Branch::Branch(QJsonObject *config) {

    if (config->contains("Transports")) {
        if (config->value("Transports").isArray()) {
            assert(makeTransports(config->value("Transports").toArray()) == 0);
        }
    }

    if (config->contains("Handlers")) {
        if (config->value("Handlers").isArray()) {
            assert(makeHandlers(config->value("Handlers").toArray()) == 0);
        }
    }

    assert(makeConnections() == 0);
}

Branch::~Branch() {
    QList<IConnector>::iterator i;

    for (i = m_parts.begin(); i != m_parts.end(); i++) {
        delete (*i);
    }

    m_parts.clear();
}

void Branch::addPart(IConnector *part) {
    m_parts.append(part);
}


int Branch::makePart(bool isHandler, QJsonArray *arr)
{
    for (int i=0; i < arr->count(); i++) {
        if (arr->at(i).isObject() != true)
            return -1;

        QJsonObject obj = arr->at(i);

        if (obj.value("Type").isString() != true)
           return -1;

        if (obj.value("Options").isObject() != true)
            return -1;

        IConnector *part;
        if (isHandler) {
            part = HandlerFact::MakeHandler(obj.value("Type").toString(), obj.value("Options").toObject());
        } else {
            part = TransportFact::makeTransport(obj.value("Type").toString(), obj.value("Options").toObject());
        }

        if (part == NULL)
            return -1;

        addPart(part);
    }
    return 0;
}

int Branch::makeTransports(QJsonArray *arr)
{
    return makePart(false, arr);
}


int Branch::makeHandlers(QJsonArray *arr)
{
    return makePart(true, arr);
}



void Branch::makeConnections() {


}
