#ifndef DIFFERSOURCETABLE_H
#define DIFFERSOURCETABLE_H

#include <QMap>
#include "basestation.h"

class DifferSourceTable
{
public:
    DifferSourceTable();
    ~DifferSourceTable();
    bool AddDifferSource(QString sourceType,ptrBaseStation ptr);
    ptrBaseStation FindBaseStationByName(QString &BaseName);
    ptrBaseStation GetSourceBaseStation(QString sourceType);
    QMap<QString,ptrBaseStation> m_SourceMap;
private:
   // QMap<QString,ptrBaseStation> m_SourceMap;
};

typedef QMap<QString,ptrBaseStation> QSourceTableMap;


#endif // DIFFERSOURCETABLE_H
