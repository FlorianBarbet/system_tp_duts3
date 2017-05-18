#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <QFile>
#include <QCoreApplication>
#include <vector>

class CAssembler
{
      Q_DECLARE_TR_FUNCTIONS(CAssembler);
   public:
      bool assemble(QFile &in, QFile &out);
   protected:
      bool handleLine(QString &line, int lineNumber);

      unsigned short _currentPC;

      QByteArray _assembledProgram;
      bool _firstPass;
};

#endif
