#include "chandler.h"
#include <QMutexLocker>

CHandler::CHandler(QJsonObject *config){
    m_config = config;
    is_stop = false;
}

void CHandler::AddData(tpkt *src, bool e){
    if (src != NULL){
        if (e) {
            QMutexLocker locker(&m_e_mutex);
            m_e_inq.enqueue(src);
        } else {
            QMutexLocker locker(&m_i_mutex);
            m_i_inq.enqueue(src);
        }
    }
}

tpkt *CHandler::GetData(bool e) {
    if (e) {
        QMutexLocker locker(&m_e_mutex);
        if (!m_e_outq.empty()) {
            return m_e_outq.dequeue();
        }
    } else {
        QMutexLocker locker(&m_i_mutex);
        if (!m_i_outq.empty()) {
            return m_i_outq.dequeue();
        }
    }
    return NULL;
}

bool CHandler::ProcessData(bool e) {
   bool retval = false;

   if (e) {
       QMutexLocker locker(&m_e_mutex);
       if (!m_e_inq.empty()) {
           m_e_outq.enqueue(m_e_inq.dequeue());
           retval = true;
       }
   } else {
       QMutexLocker locker(&m_i_mutex);
       if (!m_i_inq.empty()) {
           m_i_outq.enqueue(m_i_inq.dequeue());
           retval = true;
       }
   }

   return retval;
}

void CHandler::doWork() {
    while (!is_stop)
    {
        if (ProcessData(true)) {
            emit resultReady(true);
        }

        if (ProcessData(false)) {
            emit resultReady(false);
        }
    }
}

void CHandler::kill(){
    is_stop = true;
}
