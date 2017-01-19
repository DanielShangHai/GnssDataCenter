#include "Differsourcetable.h"

DifferSourceTable::DifferSourceTable()
{
  //  m_SourceMap.empty();
}

DifferSourceTable::~DifferSourceTable()
{
    QSourceTableMap::iterator it;//遍历map
    for ( it = m_SourceMap.begin(); it != m_SourceMap.end(); ++it )
    {
        ptrBaseStation lp = it.value();
        delete lp;
    }
    m_SourceMap.empty();
}

bool DifferSourceTable::AddDifferSource(QString sourceType,ptrBaseStation ptr)
{
   if(m_SourceMap.contains(sourceType))
   {
       return false;
   }
   m_SourceMap.insert(sourceType, ptr);  //向MAP中添加内容
   qDebug()  << "sourcetype insert success" ;
   if(m_SourceMap.contains("BHRTCM32"))
   {
      qDebug()<< "GetSourceBaseStation success";
       return m_SourceMap[sourceType];
   }
   return true;
}
ptrBaseStation DifferSourceTable::GetSourceBaseStation(QString sourceType)
{

    if(m_SourceMap.contains("BHRTCM32"))
    {
       qDebug()<< "GetSourceBaseStation success";
        return m_SourceMap[sourceType];
    }
    else
    {
       qDebug()<< "GetSourceBaseStation defeat";
        return NULL;
    }
}
ptrBaseStation DifferSourceTable::FindBaseStationByName(QString &BaseName)
{
    QSourceTableMap::iterator it;//遍历map
    for ( it = m_SourceMap.begin(); it != m_SourceMap.end(); ++it )
    {
        ptrBaseStation lp = it.value();
        if(lp->GetBaseStationName()==BaseName)
        {
            return lp;
        }
    }
    return NULL;
}
