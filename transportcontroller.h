#ifndef TRANSPORTCONTROLLER_H
#define TRANSPORTCONTROLLER_H

#include <QObject>
#include <QThread>

#include "iconnector.h"
#include "transportthreader.h"


class TransportController : public IConnector
{
    Q_OBJECT
private:
    QThread m_WorkerThread;
    TransportThreader *m_Transport;
    explicit TransportController(QObject *parent = 0);

public:
    TransportController(uint32_t my_id, TransportFact::transportID id, QJsonObject *config) {
        m_Transport = new TransportThreader(my_id, id, config);
        m_Transport->moveToThread(&m_WorkerThread);
        connect(&m_WorkerThread, &QThread::finished, m_Transport, &QObject::deleteLater);
        connect(&m_WorkerThread, &QThread::started, m_Transport, &TransportThreader::doWork);
        connect(m_Transport, &TransportThreader::resultReady, this, &TransportController::handleResults);
        m_WorkerThread.start();
    }

    ~TransportController()
    {
        m_Transport->kill();
        m_WorkerThread.quit();
        m_WorkerThread.wait();
    }


private slots:
    void handleResults(bool e) {
        emit outData(e, m_Transport->GetData(e));
    }

public slots:
    void inData(bool e, tpkt *d){
        m_Transport->AddData(d, e);
    }

signals:
    void outData(bool e, tpkt *d);

};

#endif // TRANSPORTCONTROLLER_H
