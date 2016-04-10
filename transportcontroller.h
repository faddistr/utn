#ifndef TRANSPORTCONTROLLER_H
#define TRANSPORTCONTROLLER_H

#include <QObject>

class TransportController : public IConnector
{
    Q_OBJECT
private:

public:
    explicit TransportController(QObject *parent = 0);

signals:

public slots:
};

#endif // TRANSPORTCONTROLLER_H
