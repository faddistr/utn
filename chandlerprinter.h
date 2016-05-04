#ifndef CHANDLERPRINTER_H
#define CHANDLERPRINTER_H
#include "chandler.h"

class CHandlerPrinter : public CHandler
{
    Q_OBJECT

public:
    CHandlerPrinter(QJsonObject *config);
private:
    bool m_terminate;

protected:
    bool ProcessData(bool e);



};

#endif // CHANDLERPRINTER_H
