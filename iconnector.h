#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include <QObject>

class IConnector : public QObject
{
    Q_OBJECT

public slots:
    virtual void inData(bool e, tpkt *d) = 0;

signals:
    void outData(bool e, tpkt *d);
};

#endif // ICONNECTOR_H
