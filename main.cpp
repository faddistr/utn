#include <iostream>
#include "transportcontroller.h"
#include "chandlercontroller.h"
#include <qjsondocument.h>
#include <QSharedPointer>
#include <QObject>

//using namespace std;

int main()
{
    QString t = QString::fromUtf8("{"
    "\"FileTransport\": ["
    "{\"Path\": \"1234\","
    "\"Attr\": 1}"
    "]}");
    uint32_t id;
    char buf[4096];
    QJsonDocument doc = QJsonDocument::fromJson(t.toUtf8());
    std::cout<<doc.toJson().toStdString()<<std::endl;
    QJsonObject obj = doc.object();
    TransportController tcon(0, TransportFact::FILETRANSPORT, &obj);
    CHandlerController hcon(HandlerFact::PRINTERHANDLER, NULL);
  /*  tpkt *test = new tpkt;
    test->cid = 0;
    test->payload = new QByteArray("Hello world!");
    test->tid = 0;
    tcon.inData(false, test);*/
    //        connect(&m_WorkerThread, &QThread::finished, handler, &QObject::deleteLater);
   //  connect(&m_WorkerThread, &QThread::started, handler, &CHandler::doWork);
    QObject::connect(&tcon, SIGNAL(outData(bool, tpkt*)), &hcon, SLOT(inData(bool, tpkt*)), Qt::DirectConnection);


    //QSharedPointer<ITransport> tran(TransportFact::makeTransport(TransportFact::FILETRANSPORT, &obj));
    

   // tran->send(0, const_cast<char *>(t.toStdString().c_str()), t.toStdString().length());
    int i = 0;
   /* do{
        if(tran->recv(&id, buf, 4096) > 0)
        {
           std::cout<<"Recv from: "<<id<<":"<<buf<<std::endl;
           i++;
        }
    }while(i < 128);
    delete tran;*/
   while(1) {
        QThread::sleep(10);
    }
    return 0;
}

