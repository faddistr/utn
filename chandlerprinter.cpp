#include "chandlerprinter.h"
#include <iostream>

CHandlerPrinter::CHandlerPrinter(QJsonObject *config) :  CHandler(config)
{
    m_terminate = true;
    if (m_config != NULL) {
        if (m_config->contains("Terminate")) {
            m_terminate = m_config->value("Terminate").toBool();
        }
    }
}

bool CHandlerPrinter::ProcessData(bool e)
{
    bool retval = false;
    tpkt *pkt = NULL;

    if (e) {
        QMutexLocker locker(&m_e_mutex);

        if (!m_e_inq.empty()) {
            pkt = m_e_inq.dequeue() ;

            if (!m_terminate) {
                m_e_outq.enqueue(pkt);
            }
        }
    } else {
        QMutexLocker locker(&m_i_mutex);

        if (!m_i_inq.empty()) {
            pkt = m_i_inq.dequeue() ;

            if (!m_terminate) {
                m_i_outq.enqueue(pkt);
            }
        }
    }

    if (pkt != NULL) {

        std::cout<<e<<":"<<pkt->payload->data()<<std::endl;
        if (m_terminate) {
            delete pkt->payload;
            delete pkt;
        } else {
            retval = true;
        }
    }

    return retval;
}
