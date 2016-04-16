#ifndef CHANDLERCONTROLLER
#define CHANDLERCONTROLLER
#include <QThread>
#include <QObject>
#include "handlerfact.h"
#include "iconnector.h"

class CHandlerController: public IConnector
{
    Q_OBJECT
private:
    QThread m_WorkerThread;
    CHandler *handler;
public:
    CHandlerController(HandlerFact::HandlerType t, QJsonObject *config)
    {
        handler = HandlerFact::MakeHandler(t, config);
        handler->moveToThread(&m_WorkerThread);
        connect(&m_WorkerThread, &QThread::finished, handler, &QObject::deleteLater);
        connect(&m_WorkerThread, &QThread::started, handler, &CHandler::doWork);
        connect(handler, &CHandler::resultReady, this, &CHandlerController::handleResults);
        m_WorkerThread.start();
    }

    ~CHandlerController()
    {
        handler->kill();
        m_WorkerThread.quit();
        m_WorkerThread.wait();
    }

private slots:
    void handleResults(bool e) {
        emit outData(e, handler->GetData(e));
    }

public slots:
    void inData(bool e, tpkt *d){
        handler->AddData(d, e);
    }

signals:
    void outData(bool e, tpkt *d);
};

#endif // CHANDLERCONTROLLER

