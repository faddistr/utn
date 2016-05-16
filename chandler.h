#ifndef CHANDLER_H
#define CHANDLER_H

#include <QString>
#include <QObject>
#include <QQueue>
#include <QArrayData>
#include <QMutex>
#include <QJsonObject>
#include "pktstr.h"

class CHandler : public QObject
{
    Q_OBJECT

public:
    virtual ~CHandler() {}
    CHandler(QJsonObject *config);
    void AddData(tpkt *src, bool e);
    tpkt  *GetData(bool e);

public slots:
    void kill();
    void doWork();

private:
    explicit CHandler(QObject *parent = 0) {}
    CHandler(const CHandler &){}

protected:
    QJsonObject *m_config;
    QMutex m_i_mutex;
    QMutex m_e_mutex;
    QQueue<tpkt *> m_i_inq;
    QQueue<tpkt *> m_e_inq;
    QQueue<tpkt *> m_i_outq;
    QQueue<tpkt *> m_e_outq;
    bool is_stop;
    virtual bool ProcessData(bool e);

signals:
    void resultReady(bool e);
};

#endif // CHANDLER_H
