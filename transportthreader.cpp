#include "transportthreader.h"
#include <QMutexLocker>
#include <assert.h>

void TransportThreader::OpenTransport() {
    m_Trans = TransportFact::makeTransport(m_ftid, m_config);
    assert(m_Trans != NULL);

    m_RxPktSize = m_Trans->getRxPktSize();
    m_TxPktSize = m_Trans->getTxPktSize();

    m_RxBuf = new char(m_RxPktSize);
    m_TxBuf = new char(m_TxPktSize);
}

TransportThreader::TransportThreader(uint32_t my_id, TransportFact::transportID id, QJsonObject *config) {
    m_Trans = NULL;
    m_IsStop  = false;
    m_ftid = id;
    m_config = config;
    m_ID = my_id;
}

TransportThreader::~TransportThreader() {
    delete m_Trans;
    delete m_RxBuf;
    delete m_TxBuf;
}

bool TransportThreader::ProcessDataIn() {
    uint32_t cid;
    bool res = false;
    ssize_t size = m_Trans->recv(&cid, m_RxBuf, m_RxPktSize);

    if (size > 0) {
        QMutexLocker locker(&m_r_mutex);
        tpkt *pkt = new tpkt;

        pkt->payload = new QByteArray(m_RxBuf, size);
        pkt->tid = m_ID;
        pkt->cid = cid;
        m_rxq.enqueue(pkt);
        res  = true;
    }

    return res;
}

void TransportThreader::ProcessDataOut() {
    QMutexLocker locker(&m_t_mutex);

    if (!m_txq.empty()) {
        tpkt *out = m_txq.dequeue();

        assert(m_Trans->send(out->cid, out->payload->data(), out->payload->size()) == out->payload->size());
        delete out->payload;
        delete out;
    }
}

void TransportThreader::doWork() {
    OpenTransport();

    while (!m_IsStop) {
        ProcessDataOut();
        if (ProcessDataIn()) {
            emit resultReady(false);
        }
    }
}

void TransportThreader::AddData(tpkt *src, bool e) {
   QMutexLocker locker(&m_t_mutex);

   if (src != NULL)
        m_txq.enqueue(src);
}

tpkt *TransportThreader::GetData(bool e) {
   QMutexLocker locker(&m_r_mutex);

   if (!m_rxq.empty()) {
       return m_rxq.dequeue();
   }

   return NULL;
}

void TransportThreader::kill() {
    m_IsStop  = true;
}
