#include <iostream>
#include "transportfact.h"
#include <qjsondocument.h>
#include <QSharedPointer>
using namespace std;

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
    cout<<doc.toJson().toStdString()<<endl;
    QJsonObject obj = doc.object();

    QSharedPointer<ITransport> tran(TransportFact::makeTransport(TransportFact::FILETRANSPORT, &obj));

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
    return 0;
}

