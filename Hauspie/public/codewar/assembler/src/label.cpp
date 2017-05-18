#include "label.h"
#include <QtDebug>
#include "config.h"


CLabelHandler::CLabelHandler() : _currentAddr(FIRST_ADDRESS)
{
   
}


CLabelHandler &CLabelHandler::get()
{
   static CLabelHandler lh;
   return lh;
}


bool CLabelHandler::absolute(const QString &label, unsigned short &addr) const
{
   qDebug() << QString("CLabelHandler::absolute(): %1").arg(label);
   LabelList::const_iterator it = _labels.find(label);
   if (it == _labels.end())
      return false;
   qDebug() << "found !";
   addr = it->second;
   return true; 
}

bool CLabelHandler::relative(const QString &label, unsigned short PC, short &addr) const
{
   qDebug() << QString("CLabelHandler::relative(): %1 %2").arg(label).arg(PC, 16);
   unsigned short abs_addr;
   if (!absolute(label,abs_addr))
      return false;
   addr = abs_addr - PC;
   return true;
}

bool CLabelHandler::registerLabel(const QString &label)
{
   qDebug() << QString("CLabelHandler::registerLabel(): %1").arg(label);
   LabelList::iterator it = _labels.find(label);
   if (it != _labels.end())
      return false;
   _labels.insert(std::make_pair(label, _currentAddr));
   return true;
}

void CLabelHandler::advanceAddr(int byteCount)
{
   _currentAddr += byteCount;
}
