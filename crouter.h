#ifndef CROUTER_H
#define CROUTER_H
#include "chandler.h"

class CRouter : public CHandler
{
    Q_OBJECT

public:
    CRouter(QJsonObject *config);

private:
    bool m_terminate;

protected:
    bool ProcessData(bool e);



};
#endif // CROUTER_H
