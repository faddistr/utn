#ifndef TRANSPORTTHREADER_H
#define TRANSPORTTHREADER_H

#include <QObject>
#include <QMutex>
#include <QQueue>
#include "transportfact.h"
#include "pktstr.h"

class TransportThreader: public QObject
{
    Q_OBJECT

public:
    TransportThreader(uint32_t my_id, TransportFact::transportID id, QJsonObject *config);
    void AddData(tpkt *src, bool e);
    tpkt  *GetData(bool e);
    ~TransportThreader();

public slots:
    void kill();
    void doWork();

private:
    TransportThreader(const TransportThreader &){}
    void OpenTransport();
    bool ProcessDataIn();
    void ProcessDataOut();

    QQueue<tpkt *> m_rxq;
    QQueue<tpkt *> m_txq;
    ITransport *m_Trans;
    uint32_t m_RxPktSize;
    uint32_t m_TxPktSize;
    uint32_t m_ID;
    char *m_RxBuf;
    char *m_TxBuf;
    QMutex m_r_mutex;
    QMutex m_t_mutex;
    bool m_IsStop;
    TransportFact::transportID m_ftid;
    QJsonObject *m_config;

signals:
    void resultReady(bool e);
};

#endif // TRANSPORTTHREADER_H
