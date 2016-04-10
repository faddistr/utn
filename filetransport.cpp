#include "filetransport.h"
#include <iostream>
#include <iterator>
#include <QJsonArray>
#include <assert.h>


uint32_t FileTransport::Add(QJsonObject *acc){
    uint32_t ret = ITRANSPORT_ERROR;

    if (acc->value("Path").isString()){
        QFile *f = new QFile();
        QFile::OpenMode fOpenMode = QFile::ReadOnly;

        f->setFileName(acc->value("Path").toString());

        if (acc->value("Attr").isDouble()){
            fOpenMode = static_cast<QFile::OpenMode>(acc->value("Attr").toInt());
        }

        if (f->open(fOpenMode)){
            m_flist.append(f);
            ret = m_flist.count()-1;
        }else{
            delete f;
        }
    }

    return ret;
}

FileTransport::FileTransport(QJsonObject *config) : ITransport(config){
    if (m_config->value("FileTransport").isArray()){
       QJsonArray ar = m_config->value("FileTransport").toArray();
       for (uint32_t k=0; k<ar.count(); k++){
         QJsonObject obj = ar[k].toObject();
         assert(Add(&obj) != ITRANSPORT_ERROR);
       }
    }
}

ssize_t FileTransport::send(uint32_t id, void *buf, size_t length){
    return m_flist.at(id)->write((char *)buf, length);
}

ssize_t FileTransport::recv(uint32_t *id, void *buf, size_t length)
{
   *id = 0;
   ssize_t ret = -1;

   for(QList<QFile *>::iterator iter = m_flist.begin(); iter != m_flist.end(); iter++){
       QFile *f = *iter;
       if (f->isReadable()){
        if ((ret = f->read((char *)buf,length)) > 0){
            break;
        }
       }
       (*id)++;
   }

   return ret;
}

FileTransport::~FileTransport(){
   for(QList<QFile *>::iterator iter = m_flist.begin(); iter != m_flist.end(); iter++){
      QFile *f = (*iter);
      f->close();
      delete f;
   }
   m_flist.clear();
}
