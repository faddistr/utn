#ifndef BRANCH_H
#define BRANCH_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include "iconnector.h"

class Branch : public QObject
{
    Q_OBJECT

public:
    Branch(QJsonObject *config);
    ~Branch();

private:
    explicit Branch(QObject *parent = 0);

    int makeTransports(QJsonArray *arr);
    int makeHandlers(QJsonArray *arr);
    int makeRouter(QJsonObject *obj);

    void addPart(IConnector *part);
    void makeConnections();

    QList<IConnector *> m_parts;
};
#endif // BRANCH_H
