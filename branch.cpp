#include "branch.h"
#include <assert.h>
#include <iterator>

Branch::Branch(QJsonObject *config) {

    if (config->contains("Transports")) {
        if (config->value("Transports").isArray()) {
            assert(makeTransports(config->value("Transports").toArray()) == 0);
        }
    }

    if (config->contains("Handlers")) {
        if (config->value("Handlers").isArray()) {
            assert(makeHandlers(config->value("Transports").toArray()) == 0);
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

int Branch::makeTransports(QJsonArray *arr) {

    return -1;
}


int Branch::makeHandlers(QJsonArray *arr) {

    return -1;
}



void Branch::makeConnections() {


}
